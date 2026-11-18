# Variáveis e ponteiros da struct NO
NO -> Indica um nó da lista \
codigo -> Código identificador único do produto \
nome -> Nome do produto \
preco -> Valor, em reais, do produto \
quantidade -> Quantidade em estoque do produto \
prox -> Ponteiro que armazena o próximo nó da lista \ 
ant -> Ponteiro que armazena o nó anterior da lista \
inicio -> Ponteiro que indica onde a lista se inicia \
fim -> Ponteiro que indica onde a lista termina \
tam -> Variável que indica o tamanho atual da lista \
novo -> Ponteiro para o novo nó alocado durante o cadastro \
aux -> Ponteiro auxiliar utilizado para percorrer a lista 

# Função adicionarProduto()
A função adicionarProduto é responsável por cadastrar novos produtos em uma lista, mantendo os produtos organizados em ordem crescente de código. 

Antes de realizar a inserção, verifica se já existe um produto com o mesmo código. Caso exista, exibe uma mensagem informando que o código já está cadastrado e encerra a execução da função, evitando duplicidades.

Se o código ainda não estiver cadastrado, a função aloca dinamicamente um novo nó com malloc, armazena os dados do produto e inicializa seu ponteiro de conexão (prox) com NULL.

A inserção pode ocorrer em três posições: no início, quando o código é menor que o primeiro elemento; no final, quando é maior que o último elemento; ou no meio, quando está entre dois códigos existentes. Para inserir no meio, utiliza um ponteiro auxiliar para percorrer a lista e encontrar a posição adequada. Ao finalizar a inserção, atualiza a quantidade de elementos da lista.
