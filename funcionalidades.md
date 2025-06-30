# 📘 Documentação de Funcionalidades do Sistema de E-Commerce

Segue abaixo os meus métodos, descrevendo seus parâmetros e suas devidas funcionalidades no sistema..

---

## 🔧 Produtos

### `void cadastrarProduto(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e` – ponteiro para o sistema principal.
- **Descrição**: Solicita ao usuário o nome, quantidade em estoque e preço de um novo produto. Gera um código automático e adiciona à lista de produtos.

---

### `void consultarProdutos(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Lista todos os produtos cadastrados, com nome, código, estoque e preço.

---

### `int buscarProdutoPorCodigo(Ecomerce *e, int codigo)`
- **Parâmetros**:
  - `Ecomerce *e`
  - `int codigo` – código do produto a ser procurado.
- **Retorno**: Posição do produto no array, ou `-1` se não encontrado.
- **Descrição**: Busca o índice de um produto pelo código.

---

### `void alterarProduto(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Permite alterar o nome, estoque e preço de um produto com base no código informado.

---

### `void excluirProduto(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Remove um produto da lista com base no código. Reorganiza o array após exclusão.

---

## 👨‍💼 Vendedores

### `void inserirVendedor(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Cadastra um novo vendedor com nome e salário fixo. O número é gerado automaticamente.

---

### `void alterarVendedor(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Altera nome e salário fixo de um vendedor com base no número informado.

---

### `void excluirVendedor(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Exclui um vendedor da lista com base no número.

---

### `void atualizarComissaoVendedor(Ecomerce *e, int numero, float valorVenda)`
- **Parâmetros**:
  - `Ecomerce *e`
  - `int numero` – número do vendedor.
  - `float valorVenda` – valor da venda.
- **Descrição**: Calcula 3% do valor da venda e soma à comissão do vendedor correspondente.

---

## 👤 Compradores

### `void inserirComprador(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Cadastra um novo comprador, incluindo dados pessoais e endereço de entrega.

---

### `void alterarComprador(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Altera as informações do comprador com base no CPF.

---

### `void excluirComprador(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Remove um comprador da lista com base no CPF informado.

---

## 💰 Vendas

### `void inserirVenda(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**:
  - Solicita dados do vendedor e comprador.
  - Permite adicionar produtos à venda.
  - Calcula o total e reduz o estoque.
  - Aplica comissão ao vendedor.

---

### `void alterarVenda(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Permite alterar o código do vendedor e o CPF do comprador em uma venda.

---

### `void excluirVenda(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Remove uma venda com base no código.

---

### `void consultarVendas(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**: Exibe a lista de vendas realizadas, com detalhes de cada item vendido.

---

## 📄 Nota Fiscal

### `void emitirNotaFiscal(Ecomerce *e)`
- **Parâmetro**: `Ecomerce *e`
- **Descrição**:
  - Exibe informações da venda, comprador e itens comprados.
  - Aplica valor de frete:
    - Até R$100 → R$30
    - Até R$300 → R$20
    - Acima de R$300 → R$0
  - Mostra total final.

---

## 🧩 Utilitários

### `void limparBuffer()`
- **Descrição**: Limpa o buffer do teclado após uso de `scanf()` para evitar leituras erradas.

---

## 🗂️ Persistência

Cada entidade possui:
- `salvarEntidade()` – salva no arquivo `.txt` com `;` como separador.
- `carregarEntidade()` – carrega os dados do arquivo no início da execução.

---

## 📦 Arquivos utilizados

| Tipo        | Nome do Arquivo      |
|-------------|----------------------|
| Produtos    | `produtos.txt`       |
| Vendedores  | `vendedores.txt`     |
| Compradores | `compradores.txt`    |
| Vendas      | `vendas.txt`         |

---