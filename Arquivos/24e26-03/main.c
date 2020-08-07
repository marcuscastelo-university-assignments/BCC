#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef char bool;
#define FALSE 0
#define TRUE 1

#define LEN_NOME 27
#define LEN_MARCA 20
#define LEN_EAN13 13


typedef struct
{
    char NOME[LEN_NOME];
    char MARCA[LEN_MARCA];
    char EAN13[LEN_EAN13];
    float VALOR;
} Produto;

bool stdin_has_waiting() {
    return stdin->_IO_read_ptr != stdin->_IO_read_end;
}

void stdin_clear() {
    stdin->_IO_read_ptr = stdin->_IO_read_end;
}

void stdin_flush() {
    while (stdin->_IO_read_ptr != stdin->_IO_read_end &&
         stdin->_IO_read_ptr != NULL && (
        *stdin->_IO_read_ptr == ' ' ||
        *stdin->_IO_read_ptr == '\r' ||
        *stdin->_IO_read_ptr == '\n'
    ))   { stdin->_IO_read_ptr++; }
}

//Escreve no fim do arquivo
void efetuarEscrita(FILE *fp, Produto *produto) {
    fseek(fp, 0, SEEK_END);
    fwrite(produto->NOME, sizeof(char), LEN_NOME, fp);
    fwrite(produto->MARCA, sizeof(char), LEN_MARCA, fp);
    fwrite(produto->EAN13, sizeof(char), LEN_EAN13, fp);
    fwrite(&produto->VALOR, sizeof(fnloat), 1, fp);
}

void solicitarString(char *perguntaString, char *string_buffer, int tamanhoMax) {
    printf("%s\n", perguntaString);

    char *fgetsBuffer = malloc(100);
    fgets(fgetsBuffer, 100, stdin);
    int inputLen = strlen(fgetsBuffer); // Acabando e contando com \n, sem contar o \0
    if (inputLen > tamanhoMax) {
        printf("O tamanho máximo é %d. Digite novamente.\n", tamanhoMax);
        stdin_clear();
        solicitarString(perguntaString, string_buffer, tamanhoMax);
        free(fgetsBuffer);
        return;
    }

    //Se os critérios foram atendidos
    fgetsBuffer[inputLen-1] = '\0'; //Remove o \n e coloca nullbyte
    strncpy(string_buffer, fgetsBuffer, tamanhoMax); // Já sem o \n e com tamanho max <= tamanhoMax (contando o \0)
    free(fgetsBuffer);
}

float solicitarFloat(char *perguntaString) {
    char *strValorBuffer = malloc(100);
    float valor = 0.f;
    bool valorValido;
    do {
        valorValido = TRUE;
        solicitarString(perguntaString, strValorBuffer, 100);
        valor = strtof(strValorBuffer, NULL); // Converte desse jeito para 
        if (valor == 0) {
            printf("O valor digitado é inválido! digite um valor real maior que zero.\n");
            valorValido = FALSE;
        } else if (errno == ERANGE) {
            errno = 0;  
            printf("O valor é muito grande para ser armazenado, tente um valor menor.\n");
            valorValido = FALSE;
        }
    } while (!valorValido); //Caso de valor ter estourado

    free(strValorBuffer);
    return valor;
}

void escreverProdutos(FILE *fp) {
    // Tratamento genérico em caso de mal uso
    if (fp == NULL) {
        printf("Invalid FILE pointer @escreverProdutos");
        exit(1);
    }

    // Variável static da função (acumula entre chamadas)
    static int produtoIndex = 1;

    char continuarOpt;
    Produto p;
    do {
        printf("Cadastrando %dº produto:\n", produtoIndex++);
        solicitarString("Nome do produto (Max: 27): ", p.NOME, LEN_NOME);
        solicitarString("Marca do produto (Max: 20): ", p.MARCA, LEN_MARCA);
        solicitarString("Código de barras (Max: 13): ", p.EAN13, LEN_EAN13);
        p.VALOR = solicitarFloat("Valor do produto (Número real): ");
        
        stdin_flush();

        efetuarEscrita(fp, &p);

        printf("\nDeseja cadastrar mais produtos (Y/n): ");
        
        stdin_flush();
        scanf("%c", &continuarOpt);
        stdin_flush();

    } while (continuarOpt != 'n' && continuarOpt != 'N'); // Para somente se n ou N for digitado, qualquer outro caractere prossegue
}

void onReadError() {
    printf("An error has occurred while reading some field!\n");
    exit(2);
}

void printProduto(Produto *p) {
    printf("NOME: %s\n", p->NOME);
    printf("MARCA: %s\n", p->MARCA);
    printf("CODIGO DE BARRAS: %s\n", p->EAN13);
    printf("VALOR: %f\n", p->VALOR);
    printf("\n");
}

void lerProdutosEscritos(FILE *fp) {
    // Tratamento genérico em caso de mal uso
    if (fp == NULL) {
        printf("Invalid FILE pointer @lerProdutosEscritos");
        exit(1);
    }
    
    // Lê o arquivo do começo
    fseek(fp, 0, SEEK_SET);

    Produto p;
    while (fread(p.NOME, sizeof(char), LEN_NOME, fp) == LEN_NOME) { // Enquanto não chegar no fim do arquivo (supondo que não houveram falhas de gravação)
        // As 3 próximas linhas checam se struct não foi salva por completo
        if (fread(p.MARCA, sizeof(char), LEN_MARCA, fp) != LEN_MARCA) onReadError(); 
        if (fread(p.EAN13, sizeof(char), LEN_EAN13, fp) != LEN_EAN13) onReadError();
        if (fread(&p.VALOR, sizeof(float), 1, fp) != 1) onReadError();
        printProduto(&p);
    }
}

void handleChosenOption(FILE *fp, char opt) {
    if (opt == '1') escreverProdutos(fp);
    else if (opt == '2') lerProdutosEscritos(fp);
}

void printMenuPrincipal() {
    printf("Menu principal\n");
    printf("\tOpção 1: Gravar produtos\n");
    printf("\tOpção 2: Mostrar produtos gravados\n");
    printf("\n");
    printf("\tOpção 0: Sair do programa\n");
    printf("\n");
    printf("Selecione a opção desejada: ");
}

// Opções válidas são 0, 1 e 2
bool isOptionValid(char option) {
    return (option >= '0' && option <= '2');
}

char menuPrincipal() {
    char option;
    bool try_again;
    do {
        printMenuPrincipal();

        stdin_flush();
        scanf("%c", &option);
        stdin_flush();

        if (stdin_has_waiting()) {
            try_again = TRUE;
            printf("Digite apenas um caractere!\n\n");
            stdin_clear();
        } else if (!isOptionValid(option)) {
            try_again = TRUE;
            printf("Opção inválida! selecione 0, 1 ou 2\n\n");
        } else try_again = FALSE;

    } while (try_again);
    return option;
}


int main(int argc, char const *argv[])
{
    // Como solicitado na página do coteia: a cada inicilaização, apaga o arquivo produtos.bin e começa do zero
    FILE *fp = fopen("produtos.bin", "w+b");

    // Verifica a existência de erros na abertura do arquivo
    if (fp == NULL) {
        printf("Erro ao ao abrir o arquivo:\n");
        printf("[errno %d]: %s\n", errno, strerror(errno));
        return errno;
    }

    // Exibe o menu e lê a opção selecionada (Gravar, Ler produto ou sair do programa)
    char chosenOption;
    do {
        chosenOption = menuPrincipal();
        handleChosenOption(fp, chosenOption);
    } while (chosenOption != '0');

    fclose(fp);
    return 0;
}
