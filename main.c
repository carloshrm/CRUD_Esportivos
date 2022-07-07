#include "header.h"

int contadorCodigo = 0;

int main()
{
    system("@cls||clear");
    node *listaPromocional = inicializarLista();
    int escolha = 0;
    do
    {
        mostrarMenu();
        escolha = atoi(lerEntrada());
        switch (escolha)
        {
        case 1:
            mostrarLista(listaPromocional);
            break;
        case 2:
            organizarTroca(&listaPromocional);
            break;
        case 3:
            adicionarProduto(&listaPromocional, lerNovoProduto());
            break;
        case 4:
            editarProduto(&listaPromocional);
            break;
        case 5:
            excluirProduto(&listaPromocional);
        default:
            escolha = 0;
            break;
        }
    } while (escolha != 0);
}