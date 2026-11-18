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
    struct NO * ant;
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
    novo->ant = NULL;

    if( inicio == NULL){
        inicio = novo;
        fim = novo;
    } else{
        if( novo->codigo < inicio->codigo){ // Se a insercao for no inicio da lista
            novo->prox = inicio;
            inicio->ant = novo;
            inicio = novo;
        } else if( novo->codigo > fim->codigo ){ // Se a insercao for no fim da lista
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
        } else{
            NO *aux = inicio;

            while (aux->prox != NULL && aux->prox->codigo < novo->codigo) {
                aux = aux->prox;
            }

            novo->prox = aux->prox;
            novo->ant = aux;

            if (novo->prox != NULL) {
                novo->prox->ant = novo;
            }

            aux->prox = novo;
        }
    }

        tam++;
}

void buscarProduto (int codigo) {
	int ultimoProduto = fim->codigo;
	int primeiroProduto = inicio->codigo;
	
	NO *aux = inicio;
	if (tam % 2 == 0) {
		for (int i = 0; i < tam/2; i++) {
		aux = aux->prox;
		}
	} else {
		for (int i = 0; i <= tam/2; i++) {
		aux = aux->prox;
		}
	}
	
	int produtomeio = aux->codigo;
	
	if (codigo > ultimoProduto || codigo < primeiroProduto) {
		printf("Codigo invalido!");
		return;
	} else if (codigo <= produtomeio) {
		aux = inicio;
		for (int i = 0; i <= produtomeio; i++) {
			if (aux->codigo == codigo) {
				printf("Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", aux->nome, aux->preco, aux->quantidade);
				return;
			} else {
				aux = aux->prox;
			}
		}
	} else {
		
	}
}

int main(){
    adicionarProduto(1, "Arroz", 12.90, 3);
    adicionarProduto(2, "Feijao", 8.00, 4);
    adicionarProduto(5, "Macarrao", 1.90, 2);
    adicionarProduto(8, "Miojo", 2.90, 3);
    adicionarProduto(6, "Biscoito", 5.60, 5);
    
    buscarProduto(1);
    buscarProduto(2);
    buscarProduto(5);
    buscarProduto(8);
    buscarProduto(6);

    return 0;
}
