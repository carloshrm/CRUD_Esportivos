#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int contadorCodigo;

typedef struct produto
{
    int codigo;
    char *nome;
    double valorUnitario;
} produto;

typedef struct node
{
    struct produto *item;
    struct node *prox;
} node;

char *lerEntrada()
{
    char *in = calloc(100, sizeof(char));
    if (in)
    {
        setbuf(stdin, NULL);
        fgets(in, 100, stdin);
        in[strcspn(in, "\n")] = 0;
        return in;
    }
    else
        return NULL;
}

produto *novoProduto(char *nome, double val)
{
    produto *p = calloc(1, sizeof(produto));
    if (p)
    {
        p->codigo = ++contadorCodigo;
        p->nome = nome;
        p->valorUnitario = val;
        return p;
    }
    else
        return NULL;
}

void adicionarProduto(node **l, produto *p)
{
    if ((*l)->item == NULL)
        (*l)->item = p;
    else
    {
        node *novo = malloc(sizeof(node));
        if (novo)
        {
            novo->item = p;
            novo->prox = (*l);
            (*l) = novo;
        }
        else
            return;
    }
}

void adicionarExemplos(node **lista)
{
    adicionarProduto(lista, novoProduto("Tênis  ", 550.00));
    adicionarProduto(lista, novoProduto("Halteres", 101.10));
    adicionarProduto(lista, novoProduto("Bola de Volei", 99.90));
    adicionarProduto(lista, novoProduto("Kit Ping-Pong", 120.55));
    adicionarProduto(lista, novoProduto("Fone sem fio", 89.60));
}

produto *lerNovoProduto()
{
    printf("\n\n Digite as informações para um novo produto: ");
    printf("\nNome: ");
    char *nome = lerEntrada();
    printf("Valor Unitario");
    char *vu = lerEntrada();
    if (vu && nome)
        return novoProduto(nome, atof(vu));
    else
    {
        printf("\nOcorreu um erro durante a leitura, tente novamente.");
        return NULL;
    }
}

char *produtoToString(produto p)
{
    char *info = calloc(100, sizeof(char));
    snprintf(info, 100, "\nCodigo %d > Nome: %s. Valor Unitário: %.2f.", p.codigo, p.nome, p.valorUnitario);
    return info;
}

node *inicializarLista()
{
    node *l = malloc(sizeof(node));
    if (l)
    {
        l->item = NULL;
        l->prox = NULL;
        adicionarExemplos(&l);
        return l;
    }
    else
        return NULL;
}

void mostrarLista(node *li)
{
    printf("\nLista de items em promoção: ");
    node *p = li;
    while (p)
    {
        printf("%s", produtoToString(*(p->item)));
        p = p->prox;
    }
}

void destrocaValorUnitario(node *a, node *b)
{
    double aux = a->item->valorUnitario;
    a->item->valorUnitario = b->item->valorUnitario;
    b->item->valorUnitario = aux;
}

void procurarProduto(node **anterior, node **atual, int cod)
{
    while ((*atual) && (*atual)->item->codigo != cod)
    {
        (*anterior) = (*atual);
        (*atual) = (*atual)->prox;
    }
}

int editarProduto(node **ini)
{
    printf("\nDigite o codigo do produto a ser editado: ");
    int entrada = atoi(lerEntrada());
    if (entrada == 0)
        return 0;

    node *temp = NULL, *produto = (*ini);
    procurarProduto(&temp, &produto, entrada);

    if (produto)
    {
        printf("\nEncontrado: %s.", produtoToString(*(produto->item)));
        printf("\n  Digite o novo nome: ");
        char *novoNome = lerEntrada();
        if (novoNome && strlen(novoNome) != 0)
            produto->item->nome = novoNome;
        else
            return 0;
        printf("\n  Digite o novo valor unitario: ");
        double novoVU = atof(lerEntrada());
        if (novoVU > 0)
            produto->item->valorUnitario = novoVU;
        else
            return 0;
        printf("\nEdição concluida.");
    }
    else
        return -1;
}

int excluirProduto(node **ini)
{
    printf("\nDigite o código do produto a ser excluido: ");
    int entrada = atoi(lerEntrada());
    if (entrada == 0)
        return 0;

    node *anterior = NULL, *produto = (*ini);
    procurarProduto(&anterior, &produto, entrada);
    if (produto)
    {
        if (anterior)
            anterior->prox = anterior->prox->prox;
        else
            (*ini) = (*ini)->prox;
        free(produto);
        return 1;
    }
    else
        return -1;
}

int trocarPosicao(node **ini, int cod1, int cod2)
{
    node *umPtr = NULL, *umNode = (*ini);
    procurarProduto(&umPtr, &umNode, cod1);

    node *doisPtr = NULL, *doisNode = (*ini);
    procurarProduto(&doisPtr, &doisNode, cod2);

    if (!umNode || !doisNode)
        return 0;
    /*
    else
    {
        destrocaValorUnitario(umNode, doisNode); # Funcção relacionada ao exercicio de ED1      ]
    }
    */

    if (umPtr)
        umPtr->prox = doisNode;
    else
        (*ini) = doisNode;

    if (doisPtr)
        doisPtr->prox = umNode;
    else
        (*ini) = umNode;

    node *aux = doisNode->prox;
    doisNode->prox = umNode->prox;
    umNode->prox = aux;
    return 1;
}

void organizarTroca(node **lista)
{
    printf("\nDigite os codigos dos dois produtos a serem trocados de posição:  \n1: ");
    int a = atoi(lerEntrada());
    printf("\n2: ");
    int b = atoi(lerEntrada());

    if (a == b)
    {
        printf("Numeros iguais não são validos.");
        return;
    }
    else
    {
        if (trocarPosicao(lista, a, b))
        {
            printf("\n Troca realizada com sucesso, mostrando lista atualizada...");
            mostrarLista(*lista);
        }
        else
        {
            printf("\n ! Não foram encontrados produtos com os codigos digitados.");
            return;
        }
    }
}

void mostrarMenu()
{
    printf("\n\n:: Loja de Artigos esportivos, Digite um numero e tecle enter para executar uma das opções: ");
    printf("\n\t 1 > Ver todos os produtos na lista.\n\t 2 > Trocar a ordem de dois produtos na lista.\n\t 3 > Cadastrar um novo produto. \n\t 4 > Editar um Produto.\n\t 5 > Excluir um produto.");
    printf("\n\t Qualquer outra tecla para encerrar.\n");
}

void liberarLista(node **lista)
{
    if ((*lista)->prox == NULL)
        return;
    node *p = *lista;
    liberarLista(&(*lista)->prox);
    free(p);
}