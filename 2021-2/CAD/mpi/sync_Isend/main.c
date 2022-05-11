#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    assert (size == 2);

    const char *message = "0 OK";
    if (rank == 0) {
        MPI_Ssend(message, strlen(message), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Status status;

        int flag;
        
        while (1){
            int tag = status.MPI_TAG;
            int source = status.MPI_SOURCE;
            int error = status.MPI_ERROR;
            printf("rank %d: ( tag: %d, source: %d, error: %d)\n", rank, tag, source, error);
            printf("rank %d: (flag: %d)\n", rank, flag);
            if (flag) break;
            usleep(1e6);
        }

    } else {
        printf("rank %d: Waiting 10s\n", rank);
        usleep(10e6);
        MPI_Status status;
        char *recvBuf[100];
        MPI_Recv(recvBuf, strlen(message), MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        int tag = status.MPI_TAG;
        int source = status.MPI_SOURCE;
        int error = status.MPI_ERROR;
        printf("rank %d: ( tag: %d, source: %d, error: %d)\n", rank, tag, source, error);
    }
    

    MPI_Finalize();

    return 0;
}
