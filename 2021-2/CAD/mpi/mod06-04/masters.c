#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int _; // dummy variable to avoid code pollution
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Get_processor_name(processor_name, &_);

    printf("I'm the process master %d on processor %s.\n", world_rank, processor_name);
    fflush(0);

    int matrix_order = (int)sqrt(world_size); // Assuming square matrix
    int matrix_linear_size = matrix_order * matrix_order;

    if (matrix_linear_size != world_size)
    {
        printf("Error: The number of processes must be a perfect square.\n");
        MPI_Finalize();
        exit(0); //TODO: check if it is possible to exit with an error code
    }

    int *matrix_linear = (int **)malloc(matrix_linear_size * sizeof(int));

    // Communicators for the rows and columns
    MPI_Comm *row_comms = (MPI_Comm *)malloc(matrix_order * sizeof(MPI_Comm));
    MPI_Comm *col_comms = (MPI_Comm *)malloc(matrix_order * sizeof(MPI_Comm));

    int row_comms_color = world_rank / matrix_order;
    int col_comms_color = world_rank % matrix_order;

    int *row_array = (int *)malloc(matrix_order * sizeof(int));
    int *col_array = (int *)malloc(matrix_order * sizeof(int));

    int root = 0;

    if (world_rank == root)
    {
        int *matrix_a = (int *)malloc(matrix_linear_size * sizeof(int));
        int *matrix_b = (int *)malloc(matrix_linear_size * sizeof(int));

        for (int i = 0; i < matrix_linear_size; i++)
            matrix_a[i] = matrix_b[i] = i;

        for (int i = 0; i < matrix_order; i++)
            row_array[i] = col_array[i] = i;

        int key = world_rank; // In this case, root (0)
        for (int color = 0; color < matrix_order; color++)
        {
            MPI_Comm_split(MPI_COMM_WORLD, color, color, &row_comms[color]);
            MPI_Comm_split(MPI_COMM_WORLD, color, color, &col_comms[color]);
        }

        for (int row = 0; row < matrix_order; row++)
        {
            MPI_Bcast(&matrix_a[row * matrix_order], matrix_order, MPI_INT, root, row_comms[row]);
        }
    }
    else
    {
        for (int color = 0; color < matrix_order; color++)
        {
            if (color == row_comms_color)
                MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &row_comms[color]);
            else
                MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, world_rank, &row_comms[color]);

            if (color == col_comms_color)
                MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &col_comms[color]);
            else
                MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, world_rank, &col_comms[color]);
        }

        MPI_Bcast(row_array, matrix_order, MPI_INT, root, row_comms[row_comms_color]);
        MPI_Bcast(col_array, matrix_order, MPI_INT, root, col_comms[col_comms_color]);
    }

    MPI_Comm *master_slave_spawn_comm;
    {
        int color = world_rank;
        int key = world_rank;
        MPI_Comm_split(MPI_COMM_WORLD, world_rank, world_rank, &master_slave_spawn_comm);
    }

    //Spawning slaves
    MPI_Comm *master_slave_intercomm;
    {
        MPI_Info spawn_info;
        MPI_Info_create(&spawn_info);
        MPI_Info_set(spawn_info, "hostfile", "./halley.txt");
        const char *command = "./01-mmatrix-slave";
        char **argv_slave = NULL;
        int max_procs = matrix_order - 1;

        // MPI_Comm_spawn(command, argv_slave, max_procs, spawn_info)

        int *errcodes = NULL;
        MPI_Comm_spawn(command, argv_slave, max_procs, MPI_INFO_NULL, root, master_slave_spawn_comm, &master_slave_intercomm, &errcodes);
        if (errcodes != NULL)
        {
            printf("Error spawning slaves.\n");
            MPI_Finalize();
            free(errcodes);
            exit(0); //TODO: check if it is possible to exit with an error code
        }
    }
    
    // Useless messages (keeping to not break the code)
    {
        MPI_Request *mpirequest_mr, *mpirequest_rc, *mpirequest_cc;
        // these three non-blocking messages are not necessary indeed. They are here just for debugging processes in multiply_pair code.
        // we are also using them to exemplify non-blocking (standard) sends.
        int tag = 0;
        for (int i = 0; i < matrix_order - 1; i++)
        {
            MPI_Isend(&world_rank, 1, MPI_INT, i, tag, master_slave_intercomm, &mpirequest_mr[i]);
            MPI_Isend(&row_comms_color, 1, MPI_INT, i, tag, master_slave_intercomm, &mpirequest_rc[i]);
            MPI_Isend(&col_comms_color, 1, MPI_INT, i, tag, master_slave_intercomm, &mpirequest_cc[i]);
        } //end-for-i

        // here we could have started other computing or communication

        MPI_Status status;
        for (int i = 0; i < matrix_order - 1; i++)
        {
            MPI_Wait(&mpirequest_mr[i], &status);
            MPI_Wait(&mpirequest_rc[i], &status);
            MPI_Wait(&mpirequest_cc[i], &status);
        } //end-for-i
    }

    int master_result;
    {
        MPI_Scatter(&row_array[1], 1, MPI_INT, &_, 1, MPI_INT, MPI_ROOT, master_slave_intercomm);
        MPI_Scatter(&col_array[1], 1, MPI_INT, &_, 1, MPI_INT, MPI_ROOT, master_slave_intercomm);
        
        int master_calc = row_array[0] * col_array[0];

        MPI_Reduce(&master_calc, &master_result, 1, MPI_INT, MPI_SUM, MPI_ROOT, master_slave_intercomm);

        master_result += master_calc;
    }

    // Gather all masters to root
    int *matrix_c;
    {
        if (world_rank == root)
            matrix_c = (int *)malloc(matrix_linear_size * sizeof(int));

        MPI_Gather(&master_result, 1, MPI_INT, matrix_c, 1, MPI_INT, root, MPI_COMM_WORLD);
    }

    // just process with rank 0, in MPI_COMM_WORLD will print the resulting C matrix
    if (world_rank == 0)
    {
        for (int i = 0; i < matrix_order; i++)
        {
            for (int j = 0; j < matrix_order; j++)
            {
                printf("c[%d][%d]= %d \n", i, j, matrix_c[i * matrix_order + j]);
                fflush(0);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
