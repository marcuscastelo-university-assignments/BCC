#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    const int SIZE = world_size;

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int *initial_data = (int *)malloc(SIZE * sizeof(int));

    // Initialize the array
    if (world_rank == 0)
        for (int i = 0; i < world_size; i++)
            initial_data[i] = 10 * i;

    int scatter_count = SIZE / world_size;
    int *scatter_data = (int *)malloc(scatter_count * sizeof(int));
    // Send the array to each process
    MPI_Scatter(initial_data, scatter_count, MPI_INT, scatter_data, scatter_count, MPI_INT, 0, MPI_COMM_WORLD);

    // Print out the data
    printf("Process %d has data %d\n", world_rank, scatter_data[0]);

    for (int i = 0; i < scatter_count; i++)
        scatter_data[i] = scatter_data[i] + world_rank;

    int receive_count = SIZE;
    int *receive_data = (int *)malloc(receive_count * sizeof(int));
    // Receive the array from each process
    MPI_Gather(scatter_data, scatter_count, MPI_INT, receive_data, scatter_count, MPI_INT, 0, MPI_COMM_WORLD);

    // Print out the data
    if (world_rank == 0) {
        printf("Process %d has data: [ ");
        for (int i = 0; i < world_size; i++)
            printf("%d ", receive_data[i]);
        printf("]\n");
    }

    // Also print the data of other processes, just to show that it is not complete
    // if (world_rank != 0) {
    //     printf("Process %d has data: [ ");
    //     for (int i = 0; i < world_size; i++)
    //         printf("%d ", receive_data[i]);
    //     printf("]\n");
    // }


    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
