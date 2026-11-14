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

NO * inicio = NULL;
NO * fim = NULL;
int tam = 0;

void adicionarProduto(int codigo, char * nome, float preco, int quantidade){
    // Buscando por itens com o mesmo codigo
    if( inicio != NULL){
        NO *aux = inicio;
        while (aux != NULL) {
            if (aux->codigo == codigo) {
                printf("Codigo ja cadastrado!\n");
                return;
            }
    
            aux = aux->prox;
        }
    }

    NO * novo = malloc(sizeof(NO));
    novo->codigo = codigo;
    novo->nome = nome;
    novo->preco = preco;
    novo->quantidade = quantidade;
    novo->prox = NULL;

    if( inicio == NULL){
        inicio = novo;
        fim = novo;
    } else{
        if( novo->codigo < inicio->codigo){ // Se a insercao for no inicio da lista
            novo->prox = inicio;
            inicio = novo;
        } else if( novo->codigo > fim->codigo ){ // Se a insercao for no fim da lista
            fim->prox = novo;
            fim = novo;
        } else{
            NO * aux = inicio;

            while (aux->prox != NULL && aux->prox->codigo < novo->codigo) {
                aux = aux->prox;
            }

            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
    tam++;
}

int main(){
    adicionarProduto(1, "Arroz", 12.90, 3);

    return 0;
}