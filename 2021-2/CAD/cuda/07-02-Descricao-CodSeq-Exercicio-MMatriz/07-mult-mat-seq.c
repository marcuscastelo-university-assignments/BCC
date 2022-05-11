#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
    //Declara as matrizes
    double *matrizA,*matrizB,*matrizC; 
    //Declara as variáveis de tamanho e índice
    int tam,i,j,k; 

    //Lê a dimensão da matriz
    fscanf(stdin,"%d\n",&tam); 

    //Aloca as matrizes
    matrizA=(double*)malloc(tam*tam*sizeof(double));
    matrizB=(double*)malloc(tam*tam*sizeof(double));
    matrizC=(double*)malloc(tam*tam*sizeof(double));

    //Lê as matrizes A e B
    for(i=0;i<tam;i++)
        for(j=0;j<tam;j++)
            fscanf(stdin, "%lf ", &matrizA[i * tam + j]);
    for(i=0;i<tam;i++)
        for(j=0;j<tam;j++)
            fscanf(stdin,"%lf ",&matrizB[i*tam+j]);

    //Calcula C=A*B
    for(i=0;i<tam;i++)
        for(j=0;j<tam;j++)
            for(k=0;k<tam;k++)
                matrizC[i*tam+j]+=matrizA[i*tam+k]*matrizB[k*tam+j];

    
    //Imprime o resultado    
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++)
            printf("%.1lf ",matrizC[i*tam+j]);
        printf("\n");
    }
    
    //Desaloca as matrizes
    free(matrizA);
    free(matrizB);
    free(matrizC);

    return 0;
}
