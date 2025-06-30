#include <stdio.h>
#include <string.h>
#include "munit.h"
#include "seu_arquivo_ecommerce.h"

static void *setup(const MunitParameter params[], void *user_data) {
    Ecomerce *sistema = malloc(sizeof(Ecomerce));
    memset(sistema, 0, sizeof(Ecomerce));
    return sistema;
}

static void teardown(void *fixture) {
    free(fixture);
}

static MunitResult test_cadastrarProduto(const MunitParameter params[], void *data) {
    Ecomerce *sistema = (Ecomerce *)data;

    Produto p = {"Teclado", 1, 10, 150.0f};
    sistema->pro[sistema->totProd++] = p;

    munit_assert_int(sistema->totProd, ==, 1);
    munit_assert_string_equal(sistema->pro[0].nome, "Teclado");
    munit_assert_float(sistema->pro[0].preco_venda, ==, 150.0f);

    return MUNIT_OK;
}

static MunitResult test_buscarProdutoPorCodigo(const MunitParameter params[], void *data) {
    Ecomerce *sistema = (Ecomerce *)data;

    int idx = buscarProdutoPorCodigo(sistema, 1);
    munit_assert_int(idx, ==, 0);

    idx = buscarProdutoPorCodigo(sistema, 999);
    munit_assert_int(idx, ==, -1);

    return MUNIT_OK;
}

static MunitResult test_atualizarComissaoVendedor(const MunitParameter params[], void *data) {
    Ecomerce *sistema = (Ecomerce *)data;

    Vendedor v = {"Joao Silva", 1, 2000.0f, 0.0f};
    sistema->vendedor[sistema->totVendedor++] = v;

    atualizarComissaoVendedor(sistema, 1, 1000.0f);

    munit_assert_float(sistema->vendedor[0].comissoes, ==, 30.0f);

    return MUNIT_OK;
}

static MunitResult test_inserirVenda(const MunitParameter params[], void *data) {
    Ecomerce *sistema = (Ecomerce *)data;

    Produto p = {"Teclado", 1, 10, 150.0f};
    sistema->pro[sistema->totProd++] = p;

    Vendedor v = {"Joao Silva", 1, 2000.0f, 0.0f};
    sistema->vendedor[sistema->totVendedor++] = v;

    Comprador c = {"Ana", "12345678900", "ana@email.com"};
    sistema->comp[sistema->totCom++] = c;

    Venda venda = {100, {}, 0, 0, 1, "12345678900"};
    ItemVenda item = { "Teclado", 1, 2, 150.0f, 300.0f };
    venda.itens[venda.quantidade_itens++] = item;
    venda.valor_total = 300.0f;

    sistema->venda[sistema->totVenda++] = venda;

    sistema->pro[0].quantidade_estoque -= 2;
    atualizarComissaoVendedor(sistema, 1, venda.valor_total);

    munit_assert_int(sistema->pro[0].quantidade_estoque, ==, 8);
    munit_assert_float(sistema->vendedor[0].comissoes, ==, 9.0f);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/cadastrarProduto", test_cadastrarProduto, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "/buscarProdutoPorCodigo", test_buscarProdutoPorCodigo, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "/atualizarComissaoVendedor", test_atualizarComissaoVendedor, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inserirVenda", test_inserirVenda, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/ecommerce", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
