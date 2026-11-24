#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
    novo->nome = malloc(strlen(nome) + 1);
	strcpy(novo->nome, nome);
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
        FILE *inventario;
        inventario = fopen("inventario.txt","w");
        if(inventario == NULL){
            printf("Erro ao abrir o inventario/n");
            system("pause");
            exit(1);
        }
        NO * aux = inicio;
        for(int i = 0;i<tam;i++){
            fprintf(inventario,"Codigo: %d \t Nome: %s \t Preco Unitario: %.2f \t Quantidade Disponivel: %d\n", aux->codigo, aux->nome, aux->preco, aux->quantidade);
            aux = aux->prox;
        }
        fclose(inventario);
}

void entradaDeProduto(int codigo, int quantidade) {

    NO *aux = inicio;

    while (aux != NULL) {

        if (aux->codigo == codigo) {

            if (quantidade <= 0) {
                printf("Quantidade invalida!\n");
                return;
            }

            aux->quantidade += quantidade;

            printf("\nEntrada realizada com sucesso no produto %s\n", aux->nome);
            printf("Nova quantidade: %d\n", aux->quantidade);

            return;
        }

        aux = aux->prox;
    }

    printf("Produto nao encontrado!\n");
}

void buscarProduto (int codigo) {
	int ultimoProduto = fim->codigo;
	int primeiroProduto = inicio->codigo;
	NO *produtomeio = NULL;

	if (inicio->codigo == codigo) {
		printf("Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", inicio->nome, inicio->preco, inicio->quantidade);
		return;
	} else if (codigo == fim->codigo) {
		printf("Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", fim->nome, fim->preco, fim->quantidade);
		return;
	}
	
	NO *aux = inicio;
	int contMeio = 0;
	if (tam > 2) {
		if (tam % 2 == 0) {
			for (int i = 0; i < tam/2; i++) {
				aux = aux->prox;
				contMeio ++;
			}
		} else {
			for (int i = 0; i <= tam/2; i++) {
			aux = aux->prox;
			contMeio ++;
			}
		}
		produtomeio = aux;
	} else {
		produtomeio = aux;
	}


	if (codigo > ultimoProduto || codigo < primeiroProduto) {
		printf("Codigo invalido!");
		return;
		
	} else if (codigo == produtomeio->codigo) {
		printf("Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", produtomeio->nome, produtomeio->preco, produtomeio->quantidade);
		
	} else if (codigo <= produtomeio->codigo) {
		aux = inicio;
		
		for (int i = 0; i <= contMeio; i++) {
			
			if (aux->codigo == codigo) {
				printf("Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", aux->nome, aux->preco, aux->quantidade);
				return;
				
			} else {
				aux = aux->prox;
			}
		}
	} else {
		aux = fim;
		
		for (int i = tam; i >= contMeio; i--) {
			
			if (aux->codigo == codigo) {
				printf("Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", aux->nome, aux->preco, aux->quantidade);
				return;
				
			} else {
				aux = aux->ant;
			}
		}
	}
}

void gerarRelatorio () {
	printf("---------------------------- PRODUTOS NO ESTOQUE ----------------------------\n");
	NO *aux = inicio;
	
	while (aux != NULL) {
		
		printf("-------------------------------------------------------------------------------------\n");
		printf("Codigo: %d | Nome: %s | Preco Unitario: %.2f | Quantidade Disponivel: %d\n", aux->codigo, aux->nome, aux->preco, aux->quantidade);
		printf("-------------------------------------------------------------------------------------\n");
		
		aux = aux->prox;
	}
}

void saidaDeProduto(int codigo, int quantidade){
    NO *aux = inicio;

    if(quantidade <= 0){
        printf("Quantidade invalida\n");
        return;
    }
    
    while(aux != NULL){
        if(aux->codigo == codigo){
            if(quantidade > aux->quantidade){
                printf("Quantidade invalida\n");
                return;
            }

            aux->quantidade -= quantidade;

            printf("Saida realizada com sucesso em: %s\n", aux->nome);
            printf("Nova quantidade: %d\n", aux->quantidade);

            return;
            
        }

        aux = aux->prox;

    }
    printf("O Produto nao foi encontrado\n");

}

void notificacaoReabastecimento(NO * inicio){
    NO *aux = inicio;
    int tam_min = 3;
    
    if(inicio == NULL){ // lista vazia
        printf("Nao ha nenhum produto cadastrado.\n");
        
   }else{// lista nao vazia
        while(aux != NULL){
            if(aux->quantidade == 0){
            printf("[ALERTA - Em Falta] Código %d - %s| Estoque atual: %d unidades (Mínimo exigido: %d).\n Reabastecimento urgente!\n", aux->codigo, aux->nome, aux->quantidade, tam_min);
            
            }else if(aux->quantidade <= tam_min){// Estoque abaixo ou no limite
                printf("[ALERTA - Estoque Baixo] Código %d - %s | Estoque atual: %d unidades (Mínimo exigido: %d).\n Necessário reabastecer.\n", aux->codigo, aux->nome, aux->quantidade, tam_min);    
          }
         aux = aux->prox;
        }
   }
    
}

int main(){
    int opcao = 0, codigo, quantidade;
    char nome[50];
    float preco;

    notificacaoReabastecimento(inicio);

    while (opcao != 6) {
        printf("\n----- SISTEMA DE CONTROLE DE ESTOQUE -----\n");
        printf("[1] Cadastrar produto\n");
        printf("[2] Buscar produto\n");
        printf("[3] Registrar entrada de produto\n");
        printf("[4] Registrar saida de produto\n");
        printf("[5] Imprimir relatorio de estoque\n");
        printf("[6] Sair\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:// funcao add
                printf("Codigo: ");
                scanf("%d", &codigo);

                printf("Nome: ");
                scanf(" %[^\n]", nome);

                printf("Preco: ");
                scanf("%f", &preco);

                printf("Quantidade: ");
                scanf("%d", &quantidade);

                adicionarProduto(codigo, nome, preco, quantidade);

                printf("\nProduto adicionado com sucesso.\n");
                break;

            case 2:// Funcao buscar produto
            	
            	if (inicio == NULL) {
            		
					printf("\nNao ha produtos em estoque!\n");
					
				} else {
					
					printf("Digite o codigo do produto: ");
	                scanf("%d", &codigo);
	
	                buscarProduto(codigo);
				}
                break;

            case 3://funcao de entrada
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);

                printf("Quantidade de entrada: ");
                scanf("%d", &quantidade);

                entradaDeProduto(codigo, quantidade);

                break;

            case 4://Funcao de saida
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);

                printf("Quantidade de saida: ");
                scanf("%d", &quantidade);

                saidaDeProduto(codigo, quantidade);

                break;

            case 5://funcao relatorio
            	if (inicio == NULL) {
            		
					printf("\nNao ha produtos em estoque!\n");
					
				} else {
                	gerarRelatorio ();
                
				}
                break;

            case 6:
                printf("Encerrando o sistema.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }


    return 0;
}
