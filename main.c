/**
 * @file main.c
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 * @file main.c
 * @brief Programa principal para testar a implementação da lista ligada de antenas.
 */

#include <stdio.h>
#include "antenas/antenas.h"
#include "efeitos/efeitos.h"

int main()
{
    Antena *lista = NULL;
    Efeito *efeitos = NULL;

    carregarAntenasDeFicheiro(&lista, "antenas.txt");
    listarAntenas(lista);
    
    // Remover uma antena (exemplo)
    if (removerAntena(&lista, 6, 5)){
        printf("Antena removida com sucesso!\n");
    }
    else{
        printf("Antena não encontrada.\n");
    }
    
    listarAntenas(lista); // Exibe a lista atualizada
    
    efeitos = deduzirEfeitosNefastos(lista);
    listarEfeitos(efeitos);

    limparEfeitos(efeitos);
    limparLista(lista);
    return 0;
}
