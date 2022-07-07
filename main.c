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
        int resultado;
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
            resultado = editarProduto(&listaPromocional);
            if (resultado == -1)
                printf("\nNão foi encontrado um produto com o codigo digitado.");
            else if (resultado == 0)
                printf("\nHouve um erro durante a edição, tente novamente.");
            else
                printf("\nEdição concluida.");
            break;
        case 5:
            resultado = excluirProduto(&listaPromocional);
            if (resultado == -1)
                printf("\nNão foi encontrado um produto com o codigo digitado.");
            else if (resultado == 0)
                printf("\nCodigo invalido, tente novamente.");
            else
                printf("\nExclusão concluida.");
            break;
        default:
            liberarLista(&listaPromocional);
            escolha = 0;
            break;
        }
    } while (escolha != 0);
}