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

void editarInventario(){
        FILE *inventario;
        inventario = fopen("inventario.txt","w");
        if(inventario == NULL){
            printf("Erro ao abrir o inventario/n");
            system("pause");
            exit(1);
        }
        NO * aux = inicio;
        for(int i = 0;i<tam;i++){
            fprintf(inventario,"\nCodigo: %d \t Nome: %s \t Preco Unitario: %.2f \t Quantidade Disponivel: %d\n", aux->codigo, aux->nome, aux->preco, aux->quantidade);
            aux = aux->prox;
        }
        fclose(inventario);

}

void adicionarProduto(int codigo, char * nome, float preco, int quantidade){

    // Validando o codigo
    if(codigo <= 0){
        printf("O codigo deve ser maior que zero!\n");
        return;
    }

    // Validando o preco
    if(preco < 0){
        printf("O preco nao pode ser negativo!\n");
        return;
    }

    // Buscando por itens com o mesmo codigo
    if(inicio != NULL){
        NO *aux = inicio;

        while(aux != NULL){
            if(aux->codigo == codigo){
                printf("Codigo ja cadastrado!\n");
                return;
            }

            aux = aux->prox;
        }
    }

    // Alocando memoria para o novo no
    NO *novo = malloc(sizeof(NO));

    if(novo == NULL){
        printf("Falha ao alocar memoria!\n");
        return;
    }

    novo->nome = malloc(strlen(nome) + 1);

    if(novo->nome == NULL){
        printf("Falha ao alocar memoria para o nome!\n");
        free(novo);
        return;
    }

    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    novo->preco = preco;
    novo->quantidade = quantidade;
    novo->prox = NULL;
    novo->ant = NULL;

    // Inserindo o novo no na lista ordenada
    if(inicio == NULL){
        inicio = novo;
        fim = novo;

    } else{
        if(novo->codigo < inicio->codigo){
            novo->prox = inicio;
            inicio->ant = novo;
            inicio = novo;

        } else if(novo->codigo > fim->codigo){
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;

        } else{
            NO *aux = inicio;

            while(aux->prox != NULL && aux->prox->codigo < novo->codigo){
                aux = aux->prox;
            }

            novo->prox = aux->prox;
            novo->ant = aux;

            if(novo->prox != NULL){
                novo->prox->ant = novo;
            }

            aux->prox = novo;
        }
    }

    tam++;

    editarInventario();

    printf("Produto cadastrado com sucesso!\n");
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
            editarInventario();
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
    FILE *inventario = fopen("inventario.txt", "r");
    if (inventario == NULL) {
        printf("Erro ao abrir o inventario ou nenhum produto cadastrado.\n");
        return;
    }

    printf("---------------------------- PRODUTOS NO ESTOQUE ----------------------------\n");

    char linha[256];
    //passa por cada linha até não ter mais nada
    while (fgets(linha, sizeof(linha), inventario) != NULL) {
        printf("%s", linha);
    }

    fclose(inventario);
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
            editarInventario();
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
            printf("\n[ALERTA - Em Falta]\n Codigo %d - %s | Estoque atual: %d unidades (Minimo exigido: %d).\n Reabastecimento urgente!\n", aux->codigo, aux->nome, aux->quantidade, tam_min);

            }else if(aux->quantidade <= tam_min){// Estoque abaixo ou no limite
                printf("[ALERTA - Estoque Baixo] Codigo %d - %s | Estoque atual: %d unidades (Minimo exigido: %d).\n Necessario reabastecer.\n", aux->codigo, aux->nome, aux->quantidade, tam_min);
          }
         aux = aux->prox;
        }
   }

}

void carregarInventario() {
    //abre o arquivo e lê o inventário
    FILE *inventario = fopen("inventario.txt", "r");

    if (inventario == NULL) {
        return;
    }

    char linha[300];
    int codigo, quantidade;
    char nome[50];
    float preco;

    // loop de leitura em cada linha até o fim do inventario
    while (fgets(linha, sizeof(linha), inventario) != NULL) {

        // extração e validação dos dados da linha
        if (sscanf(linha, "Codigo: %d \t Nome: %49[^\t] \t Preco Unitario: %f \t Quantidade Disponivel: %d",
                   &codigo, nome, &preco, &quantidade) == 4) {

            // limpeza de espaços extras no final do nome
            int len = strlen(nome);
            while (len > 0 && nome[len - 1] == ' ') {
                nome[len - 1] = '\0';
                len--;
            }

            // Reconstrução do nó na lista encadeada
            adicionarProduto(codigo, nome, preco, quantidade);
        }
    }

    fclose(inventario);
}

int main(){
    int opcao = 0, codigo, quantidade;
    char nome[50];
    float preco;
    carregarInventario();
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
