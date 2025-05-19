/**
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-05-18
 * 
 * @file grafos.h
 * @brief Declarações e definições relacionadas aos grafos.
*/
#ifndef GRAFO_H
#define GRAFO_H

#include "../Fase1/antenas/antenas.h"
#include "../Fase1/efeitos/efeitos.h"

#define MAX_ANTENAS 100

// Forward declarations
typedef struct Vertice Vertice;
typedef struct Aresta Aresta;
typedef struct GR GR;

/**
 * @brief Estrutura que representa uma aresta do grafo.
 */
struct Aresta {
    float distancia;
    Vertice* destino;
    Aresta* prox;
};

/**
 * @brief Estrutura que representa um vértice do grafo (uma antena).
 */
struct Vertice {
    Antena info;
    Aresta* adj;
    Vertice* proximo;
    int visitado;
};

/**
 * @brief Estrutura que representa o grafo.
 */
struct GR {
    Vertice* vertices; //Lista de vértices
    int numVertices; //Número de vértices no grafo
};

// Construção e criação
/**
 * @brief Constrói um grafo a partir de uma lista de antenas.
 * @param listaAntenas Lista ligada de antenas.
 * @return Ponteiro para o grafo construído.
 */
GR* construirGrafo(Antena* listaAntenas);

/**
 * @brief Insere um novo vértice (antena) na lista de vértices do grafo.
 * @param lista Lista ligada de vértices.
 * @param a Estrutura Antena a ser inserida.
 * @return Ponteiro para o novo vértice inserido.
 */
Vertice* inserirVertice(Vertice* lista, Antena a);

/**
 * @brief Adiciona uma aresta entre dois vértices (antenas) no grafo.
 * @param origem Vértice de origem.
 * @param destino Vértice de destino.
 * @return 1 se a aresta foi adicionada com sucesso, 0 caso contrário.
 */
int adicionarAresta(Vertice* origem, Vertice* destino);

// Visualização
/**
 * @brief Mostra o grafo no formato de lista de adjacências.
 * @param grafo Ponteiro para o grafo.
 * @return 1 se o grafo foi mostrado com sucesso, 0 caso contrário.
 */
int mostrarGrafo(GR* grafo);

// Pesquisa
/**
 * @brief Limpa os vértices visitados no grafo.
 * @param grafo Ponteiro para o grafo.
 */
void limparVisitados(GR* grafo);
/**
 * @brief Realiza a busca em profundidade (DFS) no grafo a partir de um vértice de origem.
 * @param grafo Ponteiro para o grafo.
 * @param origem Vértice de origem.
 */
void dfs(GR* grafo, Vertice* origem);
/**
 * @brief Realiza a busca em largura (BFS) no grafo a partir de um vértice de origem.
 * @param grafo Ponteiro para o grafo.
 * @param origem Vértice de origem.
 */
void bfs(GR* grafo, Vertice* origem);

// Libertação
/**
 * @brief Liberta a memória alocada para o grafo.
 * @param grafo Ponteiro para o grafo.
 * @return 1 se a memória foi libertada com sucesso, 0 caso contrário.
 */
int libertarGrafo(GR* grafo);

// Binário
/**
 * @brief Guarda o grafo em um ficheiro binário.
 * @param nomeFicheiro Nome do ficheiro onde o grafo será guardado.
 * @param grafo Ponteiro para o grafo a ser guardado.
 * @return 1 se o grafo foi guardado com sucesso, 0 caso contrário.
 */
int guardarGrafoBinario(const char* nomeFicheiro, GR* grafo);

#endif