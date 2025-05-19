/**
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-05-18
 * 
 * @file grafos.h
 * @brief Programa principal para testar as funcionalidades da fase 2 do projeto de EDA.
*/

#include "../Fase1/antenas/antenas.h"
#include "grafos.h"
#include <stdio.h>

int main() {
    // Carregar antenas
    Antena* listaAntenas = carregarAntenasDeFicheiro("antenas.txt");
    if (!listaAntenas) {
        printf("Erro ao carregar antenas.\n");
        return 1;
    }

    // Construir grafo
    GR* grafo = construirGrafo(listaAntenas);

    // Mostrar grafo
    printf("\n=== GRAFO ===\n");
    mostrarGrafo(grafo);

    // DFS
    printf("\n=== DFS ===\n");
    limparVisitados(grafo);
    dfs(grafo, grafo->vertices); // começa pela primeira antena

    // BFS
    printf("\n=== BFS ===\n");
    limparVisitados(grafo);
    bfs(grafo, grafo->vertices); // começa pela primeira antena

    // Guardar ficheiro binário
    guardarGrafoBinario("grafo.bin", grafo);

    // Libertar memória
    libertarGrafo(grafo);
    limparLista(listaAntenas);

    return 0;
}
