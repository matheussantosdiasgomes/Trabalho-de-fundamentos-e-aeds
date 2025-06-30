#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char rua[100];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[10];
} Endereco;

typedef struct {
    char nome[100];
    int codigo;
    int quantidade_estoque;
    float preco_venda;
} Produto;

typedef struct {
    char nome[100];
    int numero;
    float salario_fixo;
    float comissoes;
} Vendedor;

typedef struct {
    char nome[100];
    char cpf[15];
    char email[100];
    Endereco endereco_entrega;
} Comprador;

typedef struct {
    char nome_produto[100];
    int codigo_produto;
    int quantidade_vendida;
    float preco_unitario;
    float preco_total;
} ItemVenda;

typedef struct {
    int codigo_venda;
    ItemVenda itens[100];
    int quantidade_itens;
    float valor_total;
    int codigo_vendedor;
    char cpf_comprador[15];
} Venda;

typedef struct {
    Produto pro[100];
    int totProd;

    Comprador comp[100];
    int totCom;

    Venda venda[100];
    int totVenda;

    Vendedor vendedor[100];
    int totVendedor;
} Ecomerce;

// PARTE DOS PRODUTOS

int gerarCodigoProduto(Ecomerce *e) {
    int maior_codigo = 0;
    for (int i = 0; i < e->totProd; i++) {
        if (e->pro[i].codigo > maior_codigo) {
            maior_codigo = e->pro[i].codigo;
        }
    }
    return maior_codigo + 1;
}

void cadastrarProduto(Ecomerce *e) {
    if (e->totProd >= 100) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto p;
    p.codigo = gerarCodigoProduto(e);
    
    printf("Nome: ");
    scanf(" %[^\n]", p.nome);
    printf("Quantidade em estoque: ");
    scanf("%d", &p.quantidade_estoque);
    printf("Preco de venda: ");
    scanf("%f", &p.preco_venda);

    e->pro[e->totProd++] = p;
    printf("Produto inserido com sucesso!\n");
}

void consultarProdutos(Ecomerce *e) {
    if (e->totProd == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    printf("\nLISTA DE PRODUTOS:\n");
    for (int i = 0; i < e->totProd; i++) {
        printf("[%d] %s - Cod: %d - Estoque: %d - R$ %.2f\n",  i+1, e->pro[i].nome, e->pro[i].codigo,                e->pro[i].quantidade_estoque, e->pro[i].preco_venda);
    }
}

void alterarProduto(Ecomerce *e) {
    int cod;
    printf("Digite o codigo do produto: ");
    scanf("%d", &cod);

    for (int i = 0; i < e->totProd; i++) {
        if (e->pro[i].codigo == cod) {
            printf("Novo nome [atual: %s]: ", e->pro[i].nome);
            scanf(" %[^\n]", e->pro[i].nome);
            printf("Nova quantidade [atual: %d]: ", e->pro[i].quantidade_estoque);
            scanf("%d", &e->pro[i].quantidade_estoque);
            printf("Novo preco [atual: %.2f]: ", e->pro[i].preco_venda);
            scanf("%f", &e->pro[i].preco_venda);
            printf("Produto alterado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

void excluirProduto(Ecomerce *e) {
    int cod;
    printf("Digite o codigo do produto: ");
    scanf("%d", &cod);

    for (int i = 0; i < e->totProd; i++) {
        if (e->pro[i].codigo == cod) {
            for (int j = i; j < e->totProd-1; j++) {
                e->pro[j] = e->pro[j+1];
            }
            e->totProd--;
            printf("Produto excluido com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

int buscarProdutoPorCodigo(Ecomerce *e, int codigo) {
    for(int i = 0; i < e->totProd; i++) {
        if(e->pro[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void menuProdutos(Ecomerce *e) {
    int opcao;
    do {
        printf("\n=== MENU DE PRODUTOS ===\n");
        printf("1. Cadastrar novo produto\n");
        printf("2. Listar todos produtos\n");
        printf("3. Buscar produto por codigo\n");
        printf("4. Alterar produto\n");
        printf("5. Excluir produto\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarProduto(e);
                break;
            case 2:
                consultarProdutos(e);
                break;
            case 3: {
                int cod;
                printf("Digite o codigo do produto: ");
                scanf("%d", &cod);
                int pos = buscarProdutoPorCodigo(e, cod);
                if(pos != -1) {
                    printf("\nProduto encontrado:\n");
                    printf("Nome: %s\n", e->pro[pos].nome);
                    printf("Codigo: %d\n", e->pro[pos].codigo);
                    printf("Estoque: %d\n", e->pro[pos].quantidade_estoque);
                    printf("Preco: R$ %.2f\n", e->pro[pos].preco_venda);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
            case 4:
                alterarProduto(e);
                break;
            case 5:
                excluirProduto(e);
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}


// PARTE DE VENDEDORESSSS


int gerarNumeroVendedor(Ecomerce *e) {
    int maior_numero = 0;
    
    for(int i = 0; i < e->totVendedor; i++) {
        if(e->vendedor[i].numero > maior_numero) {
            maior_numero = e->vendedor[i].numero;
        }
    }
    
    return maior_numero + 1;
}

void inserirVendedor(Ecomerce *e) {
    if(e->totVendedor >= 100) {
        printf("Limite de vendedores atingido!\n");
        return;
    }

    Vendedor v;
    v.numero = gerarNumeroVendedor(e);
    
    printf("Nome: ");
    scanf(" %[^\n]", v.nome);
    printf("Salario fixo: ");
    scanf("%f", &v.salario_fixo);
    v.comissoes = 0;

    e->vendedor[e->totVendedor++] = v;
    printf("Vendedor cadastrado com sucesso! Numero: %d\n", v.numero);
}

void consultarVendedores(Ecomerce *e) {
    if(e->totVendedor == 0) {
        printf("Nenhum vendedor cadastrado!\n");
        return;
    }

    printf("\nLISTA DE VENDEDORES:\n");
    for(int i = 0; i < e->totVendedor; i++) {
        printf("[%d] %s - Num: %d - Salario: R$ %.2f - Comissoes: R$ %.2f\n",  i+1, e->vendedor[i].nome, e->vendedor[i].numero, e->vendedor[i].salario_fixo, e->vendedor[i].comissoes);
    }
}

void alterarVendedor(Ecomerce *e) {
    int num;
    printf("Digite o numero do vendedor: ");
    scanf("%d", &num);

    for(int i = 0; i < e->totVendedor; i++) {
        if(e->vendedor[i].numero == num) {
            printf("Novo nome [atual: %s]: ", e->vendedor[i].nome);
            scanf(" %[^\n]", e->vendedor[i].nome);
            printf("Novo salario [atual: %.2f]: ", e->vendedor[i].salario_fixo);
            scanf("%f", &e->vendedor[i].salario_fixo);
            printf("Vendedor alterado com sucesso!\n");
            return;
        }
    }
    printf("Vendedor nao encontrado!\n");
}

void excluirVendedor(Ecomerce *e) {
    int num;
    printf("Digite o numero do vendedor: ");
    scanf("%d", &num);

    for(int i = 0; i < e->totVendedor; i++) {
        if(e->vendedor[i].numero == num) {
            for(int j = i; j < e->totVendedor-1; j++) {
                e->vendedor[j] = e->vendedor[j+1];
            }
            e->totVendedor--;
            printf("Vendedor excluido com sucesso!\n");
            return;
        }
    }
    printf("Vendedor nao encontrado!\n");
}

void menuVendedores(Ecomerce *e) {
    int opcao;
    do {
        printf("\n=== MENU VENDEDORES ===\n");
        printf("1. Inserir\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: inserirVendedor(e); break;
            case 2: consultarVendedores(e); break;
            case 3: alterarVendedor(e); break;
            case 4: excluirVendedor(e); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

// parte compradores 

void inserirComprador(Ecomerce *e) {
    if(e->totCom >= 100) {
        printf("Limite de compradores atingido!\n");
        return;
    }

    Comprador c;
    
    printf("Nome: ");
    scanf(" %[^\n]", c.nome);
    printf("CPF: ");
    scanf(" %[^\n]", c.cpf);
    printf("Email: ");
    scanf(" %[^\n]", c.email);
    
    printf("\nEndereco de Entrega:\n");
    printf("Rua: ");
    scanf(" %[^\n]", c.endereco_entrega.rua);
    printf("Bairro: ");
    scanf(" %[^\n]", c.endereco_entrega.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", c.endereco_entrega.cidade);
    printf("Estado (sigla): ");
    scanf(" %[^\n]", c.endereco_entrega.estado);
    printf("CEP: ");
    scanf(" %[^\n]", c.endereco_entrega.cep);

    e->comp[e->totCom++] = c;
    printf("Comprador cadastrado com sucesso!\n");
}

void consultarCompradores(Ecomerce *e) {
    if(e->totCom == 0) {
        printf("Nenhum comprador cadastrado!\n");
        return;
    }

    printf("\nLISTA DE COMPRADORES:\n");
    for(int i = 0; i < e->totCom; i++) {
        printf("[%d] %s - CPF: %s\n", i+1, e->comp[i].nome, e->comp[i].cpf);
        printf("   Email: %s\n", e->comp[i].email);
        printf("   Endereco: %s, %s - %s/%s - CEP: %s\n\n",
               e->comp[i].endereco_entrega.rua,
               e->comp[i].endereco_entrega.bairro,
               e->comp[i].endereco_entrega.cidade,
               e->comp[i].endereco_entrega.estado,
               e->comp[i].endereco_entrega.cep);
    }
}

void alterarComprador(Ecomerce *e) {
    char cpf[15];
    printf("Digite o CPF do comprador: ");
    scanf(" %[^\n]", cpf);

    for(int i = 0; i < e->totCom; i++) {
        if(strcmp(e->comp[i].cpf, cpf) == 0) {
            printf("Novo nome [atual: %s]: ", e->comp[i].nome);
            scanf(" %[^\n]", e->comp[i].nome);
            printf("Novo email [atual: %s]: ", e->comp[i].email);
            scanf(" %[^\n]", e->comp[i].email);
            
            printf("\nNovo endereco:\n");
            printf("Rua [atual: %s]: ", e->comp[i].endereco_entrega.rua);
            scanf(" %[^\n]", e->comp[i].endereco_entrega.rua);
            printf("Bairro [atual: %s]: ", e->comp[i].endereco_entrega.bairro);
            scanf(" %[^\n]", e->comp[i].endereco_entrega.bairro);
            printf("Cidade [atual: %s]: ", e->comp[i].endereco_entrega.cidade);
            scanf(" %[^\n]", e->comp[i].endereco_entrega.cidade);
            printf("Estado [atual: %s]: ", e->comp[i].endereco_entrega.estado);
            scanf(" %[^\n]", e->comp[i].endereco_entrega.estado);
            printf("CEP [atual: %s]: ", e->comp[i].endereco_entrega.cep);
            scanf(" %[^\n]", e->comp[i].endereco_entrega.cep);

            printf("Comprador alterado com sucesso!\n");
            return;
        }
    }
    printf("Comprador nao encontrado!\n");
}

void excluirComprador(Ecomerce *e) {
    char cpf[15];
    printf("Digite o CPF do comprador: ");
    scanf(" %[^\n]", cpf);

    for(int i = 0; i < e->totCom; i++) {
        if(strcmp(e->comp[i].cpf, cpf) == 0) {
            for(int j = i; j < e->totCom-1; j++) {
                e->comp[j] = e->comp[j+1];
            }
            e->totCom--;
            printf("Comprador excluido com sucesso!\n");
            return;
        }
    }
    printf("Comprador nao encontrado!\n");
}

void menuCompradores(Ecomerce *e) {
    int opcao;
    do {
        printf("\n=== MENU COMPRADORES ===\n");
        printf("1. Inserir\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: inserirComprador(e); break;
            case 2: consultarCompradores(e); break;
            case 3: alterarComprador(e); break;
            case 4: excluirComprador(e); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

// parte de vendas 

void atualizarComissaoVendedor(Ecomerce *e, int codigo_vendedor, float valor_venda) {
    for (int i = 0; i < e->totVendedor; i++) {
        if (e->vendedor[i].numero == codigo_vendedor) {
            float comissao = valor_venda * 0.03f;
            e->vendedor[i].comissoes += comissao;
            return;
        }
    }
    printf("Vendedor com codigo %d nao encontrado para atualizar comissao.\n", codigo_vendedor);
}


void inserirVenda(Ecomerce *e) {
    if(e->totVenda >= 100) {
        printf("Limite de vendas atingido!\n");
        return;
    }

    Venda v;
    v.quantidade_itens = 0;
    v.valor_total = 0;

    printf("Codigo da venda: ");
    scanf("%d", &v.codigo_venda);
    printf("Codigo do vendedor: ");
    scanf("%d", &v.codigo_vendedor);
    printf("CPF do comprador: ");
    scanf(" %[^\n]", v.cpf_comprador);

    int continuar = 1;
    while(continuar && v.quantidade_itens < 100) {
        ItemVenda item;
        printf("\nProduto %d:\n", v.quantidade_itens+1);
        printf("Codigo do produto: ");
        scanf("%d", &item.codigo_produto);

        int encontrado = 0;
        for(int i = 0; i < e->totProd; i++) {
            if(e->pro[i].codigo == item.codigo_produto) {
                encontrado = 1;
                strcpy(item.nome_produto, e->pro[i].nome);
                item.preco_unitario = e->pro[i].preco_venda;

                printf("Quantidade: ");
                scanf("%d", &item.quantidade_vendida);

                if(item.quantidade_vendida > e->pro[i].quantidade_estoque) {
                    printf("Estoque insuficiente! Disponivel: %d\n", e->pro[i].quantidade_estoque);
                    break;
                }

                item.preco_total = item.quantidade_vendida * item.preco_unitario;
                v.itens[v.quantidade_itens++] = item;
                v.valor_total += item.preco_total;
                e->pro[i].quantidade_estoque -= item.quantidade_vendida;

                printf("Produto adicionado: %s - R$ %.2f\n", item.nome_produto, item.preco_total);
                break;
            }
        }

        if(!encontrado) {
            printf("Produto nao encontrado!\n");
        }

        printf("Adicionar outro produto? (1-Sim / 0-Nao): ");
        scanf("%d", &continuar);
    }

    if(v.quantidade_itens > 0) {
        e->venda[e->totVenda++] = v;
        atualizarComissaoVendedor(e, v.codigo_vendedor, v.valor_total);
        printf("Venda registrada com sucesso! Total: R$ %.2f\n", v.valor_total);
    } else {
        printf("Venda cancelada (nenhum produto adicionado)\n");
    }
}

void consultarVendas(Ecomerce *e) {
    if(e->totVenda == 0) {
        printf("Nenhuma venda registrada!\n");
        return;
    }

    printf("\nLISTA DE VENDAS:\n");
    for(int i = 0; i < e->totVenda; i++) {
        printf("\nVenda %d - Vendedor: %d - Comprador: %s\n", 
               e->venda[i].codigo_venda, e->venda[i].codigo_vendedor, e->venda[i].cpf_comprador);
        printf("Total: R$ %.2f\n", e->venda[i].valor_total);
        
        for(int j = 0; j < e->venda[i].quantidade_itens; j++) {
            printf("  %s (Cod: %d) - %d x R$ %.2f = R$ %.2f\n",
                   e->venda[i].itens[j].nome_produto,
                   e->venda[i].itens[j].codigo_produto,
                   e->venda[i].itens[j].quantidade_vendida,
                   e->venda[i].itens[j].preco_unitario,
                   e->venda[i].itens[j].preco_total);
        }
    }
}

void alterarVenda(Ecomerce *e) {
    int cod;
    printf("Digite o codigo da venda: ");
    scanf("%d", &cod);

    for(int i = 0; i < e->totVenda; i++) {
        if(e->venda[i].codigo_venda == cod) {
            printf("Novo codigo do vendedor [atual: %d]: ", e->venda[i].codigo_vendedor);
            scanf("%d", &e->venda[i].codigo_vendedor);
            printf("Novo CPF do comprador [atual: %s]: ", e->venda[i].cpf_comprador);
            scanf(" %[^\n]", e->venda[i].cpf_comprador);
            printf("Venda alterada com sucesso!\n");
            return;
        }
    }
    printf("Venda nao encontrada!\n");
}

void excluirVenda(Ecomerce *e) {
    int cod;
    printf("Digite o codigo da venda: ");
    scanf("%d", &cod);

    for(int i = 0; i < e->totVenda; i++) {
        if(e->venda[i].codigo_venda == cod) {
            for(int j = i; j < e->totVenda-1; j++) {
                e->venda[j] = e->venda[j+1];
            }
            e->totVenda--;
            printf("Venda excluida com sucesso!\n");
            return;
        }
    }
    printf("Venda nao encontrada!\n");
}

void menuVendas(Ecomerce *e) {
    int opcao;
    do {
        printf("\n=== MENU VENDAS ===\n");
        printf("1. Inserir\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: inserirVenda(e); break;
            case 2: consultarVendas(e); break;
            case 3: alterarVenda(e); break;
            case 4: excluirVenda(e); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

void emitirNotaFiscal(Ecomerce *e) {
    int cod_venda;
    printf("Digite o codigo da venda: ");
    scanf("%d", &cod_venda);

    for(int i = 0; i < e->totVenda; i++) {
        if(e->venda[i].codigo_venda == cod_venda) {
            float frete = 0;
            if(e->venda[i].valor_total <= 100) {
                frete = 30;
            } else if(e->venda[i].valor_total <= 300) {
                frete = 20;
            }

            printf("\n=== NOTA FISCAL ===\n");
            printf("Codigo da venda: %d\n", e->venda[i].codigo_venda);
            
            for(int j = 0; j < e->totCom; j++) {
                if(strcmp(e->comp[j].cpf, e->venda[i].cpf_comprador) == 0) {
                    printf("\nDADOS DO COMPRADOR:\n");
                    printf("Nome: %s\n", e->comp[j].nome);
                    printf("CPF: %s\n", e->comp[j].cpf);
                    printf("Email: %s\n", e->comp[j].email);
                    printf("Endereco de entrega: %s, %s - %s/%s - CEP: %s\n",
                           e->comp[j].endereco_entrega.rua,
                           e->comp[j].endereco_entrega.bairro,
                           e->comp[j].endereco_entrega.cidade,
                           e->comp[j].endereco_entrega.estado,
                           e->comp[j].endereco_entrega.cep);
                    break;
                }
            }

            printf("\nITENS DA VENDA:\n");
            for(int k = 0; k < e->venda[i].quantidade_itens; k++) {
                printf("%s (Cod: %d) - %d x R$ %.2f = R$ %.2f\n",
                       e->venda[i].itens[k].nome_produto,
                       e->venda[i].itens[k].codigo_produto,
                       e->venda[i].itens[k].quantidade_vendida,
                       e->venda[i].itens[k].preco_unitario,
                       e->venda[i].itens[k].preco_total);
            }

            printf("\nTOTAL DOS PRODUTOS: R$ %.2f\n", e->venda[i].valor_total);
            printf("FRETE: R$ %.2f\n", frete);
            printf("TOTAL DA NOTA: R$ %.2f\n", e->venda[i].valor_total + frete);
            printf("\n=== FIM DA NOTA ===\n");
            return;
        }
    }
    printf("Venda nao encontrada!\n");
}

void salvarVendedores(Ecomerce *e) {
    FILE *f = fopen("vendedores.txt", "w");
    if (!f) return;

    for (int i = 0; i < e->totVendedor; i++) {
        fprintf(f, "%s;%d;%.2f;%.2f\n",
                e->vendedor[i].nome,
                e->vendedor[i].numero,
                e->vendedor[i].salario_fixo,
                e->vendedor[i].comissoes);
    }

    fclose(f);
}

void carregarVendedores(Ecomerce *e) {
    FILE *f = fopen("vendedores.txt", "r");
    if (!f) return;

    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        Vendedor v;
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        strcpy(v.nome, token);

        token = strtok(NULL, ";");
        v.numero = atoi(token);

        token = strtok(NULL, ";");
        v.salario_fixo = strtod(token, NULL);

        token = strtok(NULL, ";");
        v.comissoes = strtod(token, NULL); 

        e->vendedor[e->totVendedor++] = v;
    }

    fclose(f);
}

void salvarCompradores(Ecomerce *e) {
    FILE *f = fopen("compradores.txt", "w");
    if (!f) return;

    for (int i = 0; i < e->totCom; i++) {
        fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%s\n",
                e->comp[i].nome,
                e->comp[i].cpf,
                e->comp[i].email,
                e->comp[i].endereco_entrega.rua,
                e->comp[i].endereco_entrega.bairro,
                e->comp[i].endereco_entrega.cidade,
                e->comp[i].endereco_entrega.estado,
                e->comp[i].endereco_entrega.cep);
    }

    fclose(f);
}

void carregarCompradores(Ecomerce *e) {
    FILE *f = fopen("compradores.txt", "r");
    if (!f) return;

    char linha[300];
    while (fgets(linha, sizeof(linha), f)) {
        Comprador c;
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        strcpy(c.nome, token);

        token = strtok(NULL, ";");
        strcpy(c.cpf, token);

        token = strtok(NULL, ";");
        strcpy(c.email, token);

        token = strtok(NULL, ";");
        strcpy(c.endereco_entrega.rua, token);

        token = strtok(NULL, ";");
        strcpy(c.endereco_entrega.bairro, token);

        token = strtok(NULL, ";");
        strcpy(c.endereco_entrega.cidade, token);

        token = strtok(NULL, ";");
        strcpy(c.endereco_entrega.estado, token);

        token = strtok(NULL, ";");
        strcpy(c.endereco_entrega.cep, token);

        e->comp[e->totCom++] = c;
    }

    fclose(f);
}

void salvarProdutos(Ecomerce *e) {
    FILE *f = fopen("produtos.txt", "w");
    if (!f) return;

    for (int i = 0; i < e->totProd; i++) {
        fprintf(f, "%s;%d;%d;%.2f\n",
                e->pro[i].nome,
                e->pro[i].codigo,
                e->pro[i].quantidade_estoque,
                e->pro[i].preco_venda);
    }

    fclose(f);
}

void carregarProdutos(Ecomerce *e) {
    FILE *f = fopen("produtos.txt", "r");
    if (!f) return;

    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        Produto p;
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        strcpy(p.nome, token);

        token = strtok(NULL, ";");
        p.codigo = atoi(token);

        token = strtok(NULL, ";");
        p.quantidade_estoque = atoi(token);

        token = strtok(NULL, ";");
        p.preco_venda = strtod(token, NULL); 

        e->pro[e->totProd++] = p;
    }

    fclose(f);
}

void salvarVendas(Ecomerce *e) {
    FILE *f = fopen("vendas.txt", "w");
    if (!f) return;

    for (int i = 0; i < e->totVenda; i++) {
        Venda v = e->venda[i];
        fprintf(f, "%d;%d;%.2f;%d;%s\n", 
                v.codigo_venda,
                v.codigo_vendedor,
                v.valor_total,
                v.quantidade_itens,
                v.cpf_comprador);

        for (int j = 0; j < v.quantidade_itens; j++) {
            fprintf(f, "%s;%d;%d;%.2f;%.2f\n",
                    v.itens[j].nome_produto,
                    v.itens[j].codigo_produto,
                    v.itens[j].quantidade_vendida,
                    v.itens[j].preco_unitario,
                    v.itens[j].preco_total);
        }
        fprintf(f, "#\n"); // delimitador de fim da venda
    }

    fclose(f);
}

void carregarVendas(Ecomerce *e) {
    FILE *f = fopen("vendas.txt", "r");
    if (!f) return;

    char linha[300];
    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#') continue; // ignora delimitador

        Venda v;
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        v.codigo_venda = atoi(token);

        token = strtok(NULL, ";");
        v.codigo_vendedor = atoi(token);

        token = strtok(NULL, ";");
        v.valor_total = strtod(token, NULL);

        token = strtok(NULL, ";");
        v.quantidade_itens = atoi(token);

        token = strtok(NULL, ";");
        strcpy(v.cpf_comprador, token);

        for (int j = 0; j < v.quantidade_itens; j++) {
            fgets(linha, sizeof(linha), f);
            linha[strcspn(linha, "\n")] = 0;

            ItemVenda item;

            token = strtok(linha, ";");
            strcpy(item.nome_produto, token);

            token = strtok(NULL, ";");
            item.codigo_produto = atoi(token);

            token = strtok(NULL, ";");
            item.quantidade_vendida = atoi(token);

            token = strtok(NULL, ";");
            item.preco_unitario = strtod(token, NULL);

            token = strtok(NULL, ";");
            item.preco_total = strtod(token, NULL);

            v.itens[j] = item;
        }

        e->venda[e->totVenda++] = v;
    }

    fclose(f);
}


int main() {
    Ecomerce sistema = {0};
    carregarVendedores(&sistema);
    carregarCompradores(&sistema);
    carregarProdutos(&sistema);
    carregarVendas(&sistema);

    int opcao;
    
    do {
        printf("\n=== SISTEMA DE E-COMMERCE ===\n");
        printf("1. Gerenciar Produtos\n");
        printf("2. Gerenciar Vendedores\n");
        printf("3. Gerenciar Compradores\n");
        printf("4. Gerenciar Vendas\n");
        printf("5. Emitir Nota Fiscal\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuProdutos(&sistema);
                break;
            case 2:
                menuVendedores(&sistema);
                break;
            case 3:
                menuCompradores(&sistema);
                break;
            case 4:
                menuVendas(&sistema);
                break;
            case 5:
                emitirNotaFiscal(&sistema);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    salvarVendedores(&sistema);
    salvarCompradores(&sistema);
    salvarProdutos(&sistema);
    salvarVendas(&sistema);

    return 0;
}