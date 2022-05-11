#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define DEBUG_ACTIVE 0
#define debugCode(code)   \
    do                    \
    {                     \
        if (DEBUG_ACTIVE) \
        {                 \
            code;         \
        }                 \
    } while (0)

#define gpuErrchk(ans)                        \
    do                                        \
    {                                         \
        gpuAssert((ans), __FILE__, __LINE__); \
    } while (0)

inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
    if (code != cudaSuccess)
    {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if (abort)
            exit(code);
    }
}

__global__ void multiplica_matriz_passo1(double *devA, double *devB, double *devHC, size_t tam)
{
    size_t i, j, k;
    i = blockIdx.y;
    j = blockIdx.x;
    k = threadIdx.x;

    if (k != 1)
        return;

    devHC[k * (tam * tam) + i * tam + j] = devA[i * tam + k] * devB[k * tam + j];
    printf("C[%llu][%llu] = A[%llu][%llu] * B[%llu][%llu] = %f\n", i, j, i, k, k, j, devHC[k * (tam * tam) + i * tam + j]);
    __syncthreads();
}

__global__ void multiplica_matriz_passo2(double *devA, double *devB, double *devHC, size_t tam)
{
    size_t i = blockIdx.y;
    size_t j = blockIdx.x;
    size_t k = threadIdx.x;

    int activeThreads = blockDim.x;
    size_t step = 1;

    size_t matrixSize = tam * tam;

#define hc(i, j, k) devHC[(i)*tam + (j) + (k)*matrixSize]

    while (k < activeThreads)
    {
        size_t first = k * step * 2;
        size_t second = first + step;
        if (second >= tam || first >= tam)
            break;

        hc(i, j, first) += hc(i, j, second);

        step *= 2;
        activeThreads /= 2;

        __syncthreads();
    }

#undef hc
}

__global__ void checkMultOk(double *devA, double *devB, double *devHC, size_t tam)
{
    int i,j,k;
    for (k = 0; k < tam; k++)
    {
        for (i = 0; i < tam; i++)
        {
            for (j = 0; j < tam; j++)
            {
                if (devHC[k * tam * tam + i * tam + j] != devA[i * tam + k] * devB[k * tam + j])
                {
                    printf("Erro na multiplicação de matrizes!\n");
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    // Declara as matrizes
    double *hostA, *hostB, *hostC;
    double *devA, *devB, *devHC;
    // Declara as variáveis de tamanho e índice
    size_t tam, i, j, k;

    // Lê a dimensão da matriz
    fscanf(stdin, "%d\n", &tam);

    // Aloca as matrizes no host
    hostA = (double *)calloc(tam * tam, sizeof(double));
    hostB = (double *)calloc(tam * tam, sizeof(double));
    hostC = (double *)calloc(tam * tam, sizeof(double));

    // Aloca as matrizes no device
    gpuErrchk(cudaMalloc((void **)&devA, tam * tam * sizeof(double)));
    gpuErrchk(cudaMalloc((void **)&devB, tam * tam * sizeof(double)));
    gpuErrchk(cudaMalloc((void **)&devHC, tam * tam * tam * sizeof(double)));

    // Lê as matrizes A e B do stdin
    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            fscanf(stdin, "%lf ", &hostA[i * tam + j]);
    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            fscanf(stdin, "%lf ", &hostB[i * tam + j]);

    debugCode({
        printf("Matriz A:\n");
        for (i = 0; i < tam; i++)
        {
            for (j = 0; j < tam; j++)
                printf("%.1lf ", hostA[i * tam + j]);
            printf("\n");
        }

        printf("Matriz B:\n");
        for (i = 0; i < tam; i++)
        {
            for (j = 0; j < tam; j++)
                printf("%.1lf ", hostB[i * tam + j]);
            printf("\n");
        }
    });

    // Copia as matrizes para o device
    gpuErrchk(cudaMemcpy(devA, hostA, tam * tam * sizeof(double), cudaMemcpyHostToDevice));
    gpuErrchk(cudaMemcpy(devB, hostB, tam * tam * sizeof(double), cudaMemcpyHostToDevice));

    dim3 blocks(tam, tam, 1);
    int threads = tam;

    // Executa o código CUDA (kernel multiplica_matriz)
    multiplica_matriz_passo1<<<blocks, threads>>>(devA, devB, devHC, tam);
    gpuErrchk(cudaDeviceSynchronize());
    checkMultOk<<<1,1>>>(devA, devB, devHC, tam);

    

    // multiplica_matriz_passo2<<<blocks, (threads+1)/2>>>(devA, devB, devHC, tam);

    // --------------------------------------------------
    // Código antigo (sequencial)
    // //Calcula C=A*B
    // for (i = 0; i < tam; i++)
    //     for (j = 0; j < tam; j++)
    //         for (k = 0; k < tam; k++)
    //             hostC[i * tam + j] += hostA[i * tam + k] * hostB[k * tam + j];
    // --------------------------------------------------

    // gpuErrchk(cudaDeviceSynchronize()); // Desnecessário, porque o cudaMemcpy já tem uma barreira implicita
    gpuErrchk(cudaMemcpy(hostC, devHC, tam * tam * sizeof(double), cudaMemcpyDeviceToHost));

    // Imprime o resultado
    debugCode({
        printf("Matriz C:\n");
    });
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
            printf("%.1lf ", hostC[i * tam + j]);
        printf("\n");
    }

    // Desaloca as matrizes do device
    gpuErrchk(cudaFree(devA));
    gpuErrchk(cudaFree(devB));
    gpuErrchk(cudaFree(devHC));

    // Desaloca as matrizes do host
    free(hostA);
    free(hostB);
    free(hostC);

    return 0;
}
