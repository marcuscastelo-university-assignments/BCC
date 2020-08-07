#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct DadosPessoais {
    //Supondo tamanho arbitrário
    char *nome;
    char *endereco;
    int numero;
    char *cidade;
} DadosPessoais;

void fillDadosPessoais(DadosPessoais *dp, const char *nome, const char *endereco, int numero, const char* cidade) {
    dp->nome = strdup(nome);
    dp->endereco = strdup(endereco);
    dp->numero = numero;
    dp->cidade = strdup(cidade);
}

//Não guarda o \0 final das strings.
void writeDP(DadosPessoais *dp, FILE *fp) {
    int nomeSize = strlen(dp->nome) * sizeof(char);
    fwrite(&nomeSize, sizeof(int), 1, fp);
    if (nomeSize > 0)
        fwrite(dp->nome, sizeof(char), nomeSize, fp);

    int enderecoSize = strlen(dp->endereco) * sizeof(char);
    fwrite(&enderecoSize, sizeof(int), 1, fp);
    if (enderecoSize > 0)
        fwrite(dp->endereco, sizeof(char), enderecoSize, fp);

    int numeroSize = sizeof(dp->numero);
    if (dp->numero == -1) 
        numeroSize = 0;
        
    fwrite(&numeroSize, sizeof(int), 1, fp);
    if (numeroSize > 0)
        fwrite(&dp->numero, numeroSize, 1, fp);

    int cidadeSize = strlen(dp->cidade) * sizeof(char);
    fwrite(&cidadeSize, sizeof(int), 1, fp);
    if (cidadeSize > 0)
        fwrite(dp->cidade, sizeof(char), cidadeSize, fp);
}

int main(int argc, char const *argv[])
{
    DadosPessoais dadosPessoaisVetor[3];

    fillDadosPessoais(&dadosPessoaisVetor[0], "Rafael", "", 1, "Campinas");
    fillDadosPessoais(&dadosPessoaisVetor[1], "Samantha", "", -1, "Matao");
    fillDadosPessoais(&dadosPessoaisVetor[2], "Tatiana", "Rua Trabalhador Sao-carlense", 400, "Sao Carlos");

    FILE *fp = fopen("ou02","wb");

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
