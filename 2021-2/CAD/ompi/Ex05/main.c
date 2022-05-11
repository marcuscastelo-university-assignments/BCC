/**
 * 11218963 - Ana Luisa Teixeira Costa
 * 11219154 - Lucas de Medeiros França Romero
 * 11219237 - Marcus Vinicius Castelo Branco Martins
 **/

#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3
#define NUMTHREADS 8

#define DEBUG 0
#if DEBUG == 1
#define DEBUG_CODE(x) x
#else
#define DEBUG_CODE(x) 
#endif

void print_matrix(int *matrix, int size) {
    for (int i = 0; i < size*size; i++) {
        printf("%10d ", matrix[i]);
        if ((i+1)%(size) == 0) printf("\n");
    }
}

int main(int argc, char *argv[])
{
    srand(2021);
    int rank, size, root = 0, provided;
    
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype dtColumn;
    MPI_Type_vector(N, 1, N, MPI_INT, &dtColumn);
    MPI_Type_create_resized(dtColumn, 0, sizeof(int), &dtColumn);
    MPI_Type_commit(&dtColumn);
    
    int *column = (int *) malloc(sizeof(int) * (10*N));
    
    int* A = (int*) malloc(N*N * sizeof(int));

    if (rank == root) {
        // Alocando e inicializando as matrizes
        int* B = (int*) malloc(N*N * sizeof(int));

        for (int i = 0; i < N*N; i++) {
            A[i] = rand() DEBUG_CODE(%10);
            B[i] = rand() DEBUG_CODE(%10);
        }
        
        printf("A:\n");
        print_matrix(A, N);
        printf("B:\n");
        print_matrix(B, N);

        // Broadcast A
        MPI_Bcast(A, N*N, MPI_INT, root, MPI_COMM_WORLD);   
        
        // Scatter B column-wise
        MPI_Scatter(B, 1, dtColumn, column, N, MPI_INT, root, MPI_COMM_WORLD);
        free(B);
    }
    else {
        // Receive A
        MPI_Bcast(A, N*N, MPI_INT, root, MPI_COMM_WORLD);

        // Receive column from B
        MPI_Scatter(NULL, 1, dtColumn, column, N, MPI_INT, root, MPI_COMM_WORLD);
    }

    // Multiply A and column 
    int *Cj = (int *) calloc(N, sizeof(int));
    
    // Parallelize this loop with OpenMP with NUMTHREADS threads
    #pragma omp parallel for
    for (int line = 0; line < N; line++) {
        # pragma omp parallel for reduction(+:Cj[line])
        for (int j = 0; j < N; j++) {
            Cj[line] += column[j]*A[line*N+j];
        }
    }

    if (rank == root) {
        int* C = (int*) calloc(N*N, sizeof(int));
        MPI_Gather(Cj, N, MPI_INT, C, 1, dtColumn, root, MPI_COMM_WORLD);

        printf("C:\n");
        print_matrix(C, N);
        
        free(C);
    }
    else {
        MPI_Gather(Cj, N, MPI_INT, NULL, 1, dtColumn, root, MPI_COMM_WORLD);
    }
    
    free(A);
    free(column);
    free(Cj);
    
    MPI_Finalize();
    
    return 0;
}
