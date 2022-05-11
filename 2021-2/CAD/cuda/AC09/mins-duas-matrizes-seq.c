#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
    //Declara as matrizes
    int *A,*B;
    //Declara as variáveis de índice
    int i,j, dimA_lin, dimA_col, dimB_lin, dimB_col;
    //Declara os minimos para as duas matrizes
    int minA, minB;


    fscanf(stdin, "%d\n", &dimA_lin); //Lê a dimensão linha matriz A
    fscanf(stdin, "%d\n", &dimA_col); //Lê a dimensão coluna matriz A
    fscanf(stdin, "%d\n", &dimB_lin); //Lê a dimensão linha matriz B
    fscanf(stdin, "%d\n", &dimB_col); //Lê a dimensão coluna matriz B
    
//	printf("%d %d %d %d \n", dimA_lin, dimA_col, dimB_lin, dimB_col);
	
    //Aloca as matrizes A e B
    A = (int *)malloc(dimA_lin * dimA_col * sizeof(int));
    B = (int *)malloc(dimB_lin * dimB_col * sizeof(int)); 

     //Lê a matriz A
    for(i=0;i<dimA_lin;i++)
	{
        for(j=0;j<dimA_col;j++)
		{
            fscanf(stdin, "%d ",&(A[i*dimA_lin+j]));
        }
    }

    //Lê a matriz B
    for(i=0;i<dimB_lin;i++)
	{
        for(j=0;j<dimB_col;j++)
		{
            fscanf(stdin, "%d ",&(B[i*dimB_lin+j])); 
        }
    }
	
    //encontra o mínimo da matriz A
	minA = A[0];
    for(i=0;i<dimA_lin;i++)
	{
        for(j=0;j<dimA_col;j++)
		{
			if (A[i*dimA_lin+j]< minA) 
			{
				minA = A[i*dimA_lin+j];
			}
        }
    }

    //encontra o mínimo da matriz B
	minB = B[0];
    for(i=0;i<dimB_lin;i++)
	{
        for(j=0;j<dimB_col;j++)
		{
			if (B[i*dimB_lin+j]< minB) 
			{
				minB = B[i*dimB_lin+j];
			}
        }
    }
	
    //Imprime o resultado
    printf("%d\n%d\n", minA, minB); 
}
