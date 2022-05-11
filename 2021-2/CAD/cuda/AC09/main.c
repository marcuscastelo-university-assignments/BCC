/**
 * 11218963 - Ana Luisa Teixeira Costa
 * 11219154 - Lucas de Medeiros França Romero
 * 11219237 - Marcus Vinicius Castelo Branco Martins
 */

#include <stdio.h>
#include <stdlib.h>
// #include <cuda.h>

// __global__ void kernel(int *matriz_d, int *min, int tam) {
//     int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
//     if (idx < tam) {
//         atomicMin(min, matriz_d[idx]);
//     }
// }

int main(int argc, char const *argv[]) {
    //Declara as matrizes
    int *A,*B;
    int *A_d,*B_d;
    //Declara as variáveis de índice
    int i,j, dimA_lin, dimA_col, dimB_lin, dimB_col;
    //Declara os minimos para as duas matrizes
    int minA, minB;
    int *minA_d, *minB_d;

    fscanf(stdin, "%d\n", &dimA_lin); //Lê a dimensão linha matriz A
    fscanf(stdin, "%d\n", &dimA_col); //Lê a dimensão coluna matriz A
    fscanf(stdin, "%d\n", &dimB_lin); //Lê a dimensão linha matriz B
    fscanf(stdin, "%d\n", &dimB_col); //Lê a dimensão coluna matriz B
    
    // printf("%d %d %d %d \n", dimA_lin, dimA_col, dimB_lin, dimB_col);
	
    //Aloca as matrizes A e B
    A = (int *)malloc(dimA_lin * dimA_col * sizeof(int));
    B = (int *)malloc(dimB_lin * dimB_col * sizeof(int));
    
    // cudaMalloc((void**)&A_d, dimA_lin * dimA_col * sizeof(int)); 
    // cudaMalloc((void**)&B_d, dimB_lin * dimB_col * sizeof(int));

    // cudaMalloc((void**) &minA_d, sizeof(int)); 
    // cudaMalloc((void**) &minB_d, sizeof(int)); 

    // cudaStream_t streamA;
    // cudaStream_t streamB;
    // cudaStreamCreate(&streamA);
    // cudaStreamCreate(&streamB);

     //Lê a matriz A
    for(i=0;i<dimA_lin;i++) {
        for(j=0;j<dimA_col;j++) {
            fscanf(stdin, "%d ",&(A[i*dimA_lin+j]));
        }
    }

    //Lê a matriz B
    for(i=0;i<dimB_lin;i++) {
        for(j=0;j<dimB_col;j++) {
            fscanf(stdin, "%d ",&(B[i*dimB_lin+j])); 
        }
    }

    printf("Matriz A:\n");
    for (i = 0; i < dimA_lin; i++) {
        for (j = 0; j < dimA_col; j++)
            printf("%d ", A[i * dimA_lin + j]);
        printf("\n");
    }

    printf("Matriz B:\n");
    for (i = 0; i < dimB_lin; i++) {
        for (j = 0; j < dimB_col; j++)
            printf("%d ", B[i * dimB_lin + j]);
        printf("\n");
    }

	minA = A[0];
	minB = B[0];
    
    // cudaMemcpy(minA_d, &minA, sizeof(int), cudaMemcpyHostToDevice);
    // cudaMemcpy(minB_d, &minB, sizeof(int), cudaMemcpyHostToDevice);
    // cudaMemcpy(A_d, A, dimA_lin * dimA_col * sizeof(int), cudaMemcpyHostToDevice);
    // cudaMemcpy(B_d, B, dimB_lin * dimB_col * sizeof(int), cudaMemcpyHostToDevice);
    
    //Encontra o mínimo da matriz A
    // kernel<<<1,dimA_lin*dimA_col, 1>>>(A_d, minA_d, dimA_lin*dimA_col);
    // cudaDeviceSynchronize();
    //Encontra o mínimo da matriz B
    // kernel<<<1,dimB_lin*dimB_col, 1>>>(B_d, minB_d, dimB_lin*dimB_col);
    
    // cudaMemcpy(&minA, minA_d, sizeof(int), cudaMemcpyDeviceToHost);
    // cudaMemcpy(&minB, minB_d, sizeof(int), cudaMemcpyDeviceToHost);

    //Imprime o resultado
    // printf("%d\n%d\n", minA, minB);

    // //Libera a memória
    // cudaStreamDestroy(streamA);
    // cudaStreamDestroy(streamB);

    // cudaFree(minA_d);
    // cudaFree(minB_d);
    // cudaFree(A_d);
    // cudaFree(B_d);

    free(A);
    free(B); 
}
