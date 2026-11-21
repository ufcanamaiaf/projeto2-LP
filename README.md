
# Variáveis e ponteiros da struct NO

- `NO` -> Indica um nó da lista.
- `codigo` -> Código identificador único do produto.
- `nome` -> Nome do produto.
- `preco` -> Valor, em reais, do produto.
- `quantidade` -> Quantidade em estoque do produto.
- `prox` -> Ponteiro que armazena o próximo nó da lista.
- `ant` -> Ponteiro que armazena o nó anterior da lista.
- `inicio` -> Ponteiro que indica onde a lista se inicia.
- `fim` -> Ponteiro que indica onde a lista termina.
- `tam` -> Variável que indica o tamanho atual da lista.
- `novo` -> Ponteiro para o novo nó alocado durante o cadastro.
- `aux` -> Ponteiro auxiliar utilizado para percorrer a lista.
- `inventario` -> Ponteiro do tipo `FILE`, utilizado para manipular o arquivo `inventario.txt`.
- `opcao` -> Variável que armazena a opção escolhida pelo usuário no menu principal.
- `preco` -> Variável que armazena o preço informado durante o cadastro.
- `codigo` -> Variável que recebe o código do produto informado pelo usuário.
- `quantidade` -> Variável que recebe a quantidade de produtos informada pelo usuário.
- `nome` -> Vetor de caracteres utilizado para armazenar o nome do produto durante o cadastro.
- `ultimoProduto` -> Armazena o código do último produto da lista.
- `primeiroProduto` -> Armazena o código do primeiro produto da lista.
- `produtomeio` -> Armazena o código do produto localizado na posição central da lista.

---

# Função adicionarProduto()

A função `adicionarProduto()` é responsável por cadastrar novos produtos em uma lista duplamente encadeada, mantendo os produtos organizados em ordem crescente de código.

Antes de realizar a inserção, verifica se já existe um produto com o mesmo código. Caso exista, exibe uma mensagem informando que o código já está cadastrado e encerra a execução da função, evitando duplicidades.

Se o código ainda não estiver cadastrado, a função aloca dinamicamente um novo nó com `malloc`, armazena os dados do produto e utiliza `strcpy()` para copiar o nome informado para o espaço de memória alocado dinamicamente.

A inserção pode ocorrer em três posições: no início, quando o código é menor que o primeiro elemento; no final, quando é maior que o último elemento; ou no meio, quando está entre dois códigos existentes.

Para inserir no meio, utiliza um ponteiro auxiliar para percorrer a lista e encontrar a posição adequada, atualizando os ponteiros `prox` e `ant` dos nós envolvidos.

Ao finalizar a inserção, incrementa a variável `tam` e atualiza o arquivo `inventario.txt`, sobrescrevendo seu conteúdo com os dados de todos os produtos cadastrados na lista.

---

# Função entradaDeProduto()

A função `entradaDeProduto()` é responsável por registrar a entrada de novas unidades de um produto já cadastrado no estoque.

Recebe como parâmetros o código do produto e a quantidade que será adicionada.

Inicialmente, utiliza um ponteiro auxiliar `aux`, que começa apontando para o primeiro nó da lista (`inicio`). Em seguida, percorre a lista utilizando o ponteiro `prox`, verificando se o código de algum produto corresponde ao código informado pelo usuário.

Quando encontra o produto, verifica se a quantidade informada é válida, impedindo a entrada de valores menores ou iguais a zero.

Se a quantidade for válida, realiza a soma entre a quantidade existente no estoque e a quantidade recebida, atualizando o campo `quantidade` do nó correspondente.

Após a atualização, exibe uma mensagem confirmando a entrada do produto e informa a nova quantidade disponível em estoque.

Caso percorra toda a lista sem encontrar o código informado, exibe uma mensagem informando que o produto não foi encontrado.

---

# Função buscarProduto()

A função `buscarProduto()` é responsável por localizar um produto cadastrado na lista por meio de seu código identificador.

Recebe como parâmetro o código informado pelo usuário e utiliza os ponteiros `inicio` e `fim` para obter os códigos do primeiro e do último produto da lista.

Em seguida, utiliza um ponteiro auxiliar para percorrer a lista e identificar o produto localizado na posição central, considerando a quantidade de elementos armazenados na variável `tam`.

A partir dessas informações, verifica se o código informado está dentro do intervalo de códigos cadastrados e compara seu valor com o código do produto central.

Com base nessa comparação, direciona a busca para a região correspondente da lista.

Quando encontra o produto, exibe seu nome, preço unitário e quantidade disponível em estoque.

**Observação:** A implementação atual dessa função ainda precisa ser finalizada, pois a busca na segunda metade da lista não foi implementada completamente.

---

# Função main()

A função `main()` é responsável pela execução principal do sistema de controle de estoque.

Inicialmente, declara as variáveis utilizadas para armazenar a opção escolhida pelo usuário, o código, o nome, o preço e a quantidade dos produtos.

Em seguida, apresenta um menu interativo que permanece em execução por meio de uma estrutura de repetição `while`, permitindo que o usuário escolha entre as funcionalidades disponíveis.

As opções do menu são:

- **Opção 1 — Cadastrar produto:** solicita os dados do produto e chama a função `adicionarProduto()`.
- **Opção 2 — Buscar produto:** solicita o código do produto e chama a função `buscarProduto()`.
- **Opção 3 — Registrar entrada de produto:** solicita o código e a quantidade de entrada, chamando a função `entradaDeProduto()`.
- **Opção 4 — Registrar saída de produto:** solicita o código e a quantidade de saída. A implementação da função ainda será adicionada.
- **Opção 5 — Imprimir relatório de estoque:** opção reservada para a implementação da função de relatório.
- **Opção 6 — Sair:** encerra a execução do sistema.

A estrutura `switch` é utilizada para direcionar a execução de acordo com a opção selecionada pelo usuário. Caso seja digitada uma opção inexistente, o sistema exibe uma mensagem informando que a opção é inválida.