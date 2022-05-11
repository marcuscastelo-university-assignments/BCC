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

__global__ void multiplica_matriz(double *devA, double *devB, double *devC, int tam)
{
    extern __shared__ double parcialMults[];

    int i, j, k;
    i = blockIdx.x;
    j = blockIdx.y;
    k = threadIdx.x;

    parcialMults[k] = devA[i * tam + k] * devB[k * tam + j];
    __syncthreads();

    if (k == 0)
    {
        for (int s = 0; s < tam; s++)
            devC[i * tam + j] += parcialMults[s];
    }
}

int main(int argc, char **argv)
{
    // Declara as matrizes
    double *hostA, *hostB, *hostC;
    double *devA, *devB, *devC;
    // Declara as variáveis de tamanho e índice
    int tam, i, j;

    // Lê a dimensão da matriz
    fscanf(stdin, "%d\n", &tam);

    // Aloca as matrizes no host
    hostA = (double *)calloc(tam * tam, sizeof(double));
    hostB = (double *)calloc(tam * tam, sizeof(double));
    hostC = (double *)calloc(tam * tam, sizeof(double));

    // Aloca as matrizes no device
    gpuErrchk(cudaMalloc((void **)&devA, tam * tam * sizeof(double)));
    gpuErrchk(cudaMalloc((void **)&devB, tam * tam * sizeof(double)));
    gpuErrchk(cudaMalloc((void **)&devC, tam * tam * sizeof(double)));

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

    dim3 dimBlock(tam, tam);
    dim3 tpb(tam);

    // Executa o código CUDA (kernel multiplica_matriz)
    multiplica_matriz<<<dimBlock, tpb, tam>>>(devA, devB, devC, tam);

    // --------------------------------------------------
    // Código antigo (sequencial)
    // //Calcula C=A*B
    // for (i = 0; i < tam; i++)
    //     for (j = 0; j < tam; j++)
    //         for (k = 0; k < tam; k++)
    //             hostC[i * tam + j] += hostA[i * tam + k] * hostB[k * tam + j];
    // --------------------------------------------------

    // gpuErrchk(cudaDeviceSynchronize()); // Desnecessário, porque o cudaMemcpy já tem uma barreira implicita
    gpuErrchk(cudaMemcpy(hostC, devC, tam * tam * sizeof(double), cudaMemcpyDeviceToHost));

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
    gpuErrchk(cudaFree(devC));

    // Desaloca as matrizes do host
    free(hostA);
    free(hostB);
    free(hostC);

    return 0;
}
