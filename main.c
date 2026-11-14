#include<stdio.h>
#include<stdlib.h>

typedef struct NO{
    // Dados da aplicacao
    int codigo;
    char * nome;
    float preco;
    int quantidade;

    // Estrutura de conexao do NO
    struct NO * prox;
}NO;

int main(){

    return 0;
}