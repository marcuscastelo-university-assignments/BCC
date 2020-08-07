#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct DadosPessoais {
    //Supondo tamanho arbitrário
    char nome[41];
    char endereco[51];
    int numero;
    char cidade[35];
} DadosPessoais;

void fillDadosPessoais(DadosPessoais *dp, const char *nome, const char *endereco, int numero, const char* cidade) {
    strncpy(dp->nome, nome, strlen(nome) + 1);
    strncpy(dp->endereco, endereco, strlen(endereco) + 1);
    strncpy(dp->cidade, cidade, strlen(cidade) + 1);
    dp->numero = numero;
}

void writeDP(DadosPessoais *dp, FILE *fp) {
    //Não guarda o \0 final das strings, mas guarda lixo que pode existir no caminho.
    fwrite(dp->nome, sizeof(char), sizeof(dp->nome) - 1, fp);
    fwrite(dp->endereco, sizeof(char), sizeof(dp->endereco) - 1, fp);
    fwrite(&dp->numero, sizeof(dp->numero), 1, fp);
    fwrite(dp->cidade, sizeof(char), sizeof(dp->nome) - 1, fp);
}

int main(int argc, char const *argv[])
{
    DadosPessoais dadosPessoaisVetor[3];

    fillDadosPessoais(&dadosPessoaisVetor[0], "Rafael", "", 1, "Campinas");
    fillDadosPessoais(&dadosPessoaisVetor[1], "Samantha", "", -1, "Matao");
    fillDadosPessoais(&dadosPessoaisVetor[2], "Tatiana", "Rua Trabalhador Sao-carlense", 400, "Sao Carlos");

    FILE *fp = fopen("ue","wb");

    if (fp == NULL) {
        printf("%s\n", strerror(errno));
        printf("ERRNO: %d\n", errno);
        return 1;
    }   

    for (int i = 0; i < 3; i++)
        writeDP(&dadosPessoaisVetor[i], fp);

    fclose(fp);
    return 0;
}
