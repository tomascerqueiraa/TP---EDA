/**
 * @file main.c
 * @author Tomás Cerqueira Gomes
 * @date 2025-05-18
 *
 * @brief Programa principal para testar as funcionalidades da Fase 1 do projeto de EDA.
 */

#include <stdio.h>
#include "antenas/antenas.h"
#include "efeitos/efeitos.h"


#define MAX_ANTENAS 100

int main() {
    Antena *lista = NULL;
    Efeito *efeitos = NULL;
    //Antena* antenas[MAX_ANTENAS];
    //Adjacencia* matrizAdj[MAX_ANTENAS][MAX_ANTENAS];
    //int total = 0;

    /*
    // Inicializar matriz de adjacências
    for (int i = 0; i < MAX_ANTENAS; i++)
        for (int j = 0; j < MAX_ANTENAS; j++)
            matrizAdj[i][j] = NULL;*/

    // Fase 1 - Carregar antenas
    lista = carregarAntenasDeFicheiro("antenas.txt");

    printf("=== Antenas Carregadas ===\n");
    listarAntenas(lista);

    // Fase 1 - Calcular e listar efeitos nefastos
    efeitos = deduzirEfeitosNefastos(lista);
    printf("\n=== Efeitos Nefastos ===\n");
    listarEfeitos(efeitos);

    /*
    // Fase 2 - Passar antenas da lista ligada para vetor
    for (Antena* a = lista; a != NULL; a = a->prox)
        adicionarAntena(a, antenas, &total);

    // Fase 2 - Criar arestas e mostrar grafo
    criarArestas(antenas, matrizAdj, total);
    printf("\n=== Grafo de Antenas ===\n");
    mostrarGrafo(antenas, matrizAdj, total);

    // Libertar memória
    limparEfeitos(efeitos);             // Efeitos da Fase 1
    liberarGrafo(matrizAdj, total);     // Matriz de adjacência da Fase 2
    limparLista(lista);                 // Lista ligada da Fase 1
    */
    return 0;
}
