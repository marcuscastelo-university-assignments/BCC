#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int token;
    if (rank == 0)
    {
        token = -1;
    }
    else
    {
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", rank, token, rank - 1);
    }

    token++;    
    MPI_Send(&token, 1, MPI_INT, (rank + 1)%size, 0, MPI_COMM_WORLD);

    if (rank == 0) 
    {
        MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", rank, token, size - 1);
        printf("Final token: %d\n", token);
    }


    MPI_Finalize();    
    return 0;
}
