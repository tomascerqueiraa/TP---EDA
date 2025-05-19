/**
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-05-18
 * 
 * @file grafos.h
 * @brief Impleementação das funções de manipulação de grafos.
*/

#include "grafos.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_FILA 100

#pragma region inserirVertice
/**
 * @brief Insere um novo vértice (antena) na lista de vértices do grafo.
 * @param lista Lista ligada de vértices.
 * @param a Estrutura Antena a ser inserida.
 * @return Ponteiro para o novo vértice inserido.
 */
Vertice* inserirVertice(Vertice* lista, Antena a) {
    Vertice* novo = malloc(sizeof(Vertice));
    if (!novo) return lista;

    novo->info = a;
    novo->adj = NULL;
    novo->proximo = lista;
    novo->visitado = 0;
    return novo;
}
#pragma endregion

#pragma region adicionarAresta
/**
 * @brief Adiciona uma aresta entre dois vértices (antenas) no grafo.
 * @param origem Vértice de origem.
 * @param destino Vértice de destino.
 * @return 1 se a aresta foi adicionada com sucesso, 0 caso contrário.
 */
int adicionarAresta(Vertice* origem, Vertice* destino) {
    if (!origem || !destino) return 0;

    Aresta* nova = malloc(sizeof(Aresta));
    if (!nova) return 0;

    nova->distancia = calcularDistancia(&origem->info, &destino->info);
    nova->destino = destino;
    nova->prox = origem->adj;
    origem->adj = nova;

    return 1;
}
#pragma endregion

#pragma region construirGrafo
/**
 * @brief Constrói um grafo a partir de uma lista de antenas.
 * @param listaAntenas Lista de antenas.
 * @return Ponteiro para o grafo construído.
 */
GR* construirGrafo(Antena* listaAntenas) {
    GR* grafo = malloc(sizeof(GR));
    if (!grafo) return NULL;
    grafo->vertices = NULL;
    grafo->numVertices = 0;

    Vertice* ultimo = NULL;
    for (Antena* a = listaAntenas; a != NULL; a = a->prox) {
        Vertice* novo = inserirVertice(NULL, *a);
        grafo->numVertices++;

        if (!grafo->vertices) {
            grafo->vertices = novo;
            ultimo = novo;
        } else {
            ultimo->proximo = novo;
            ultimo = novo;
        }
    }

    for (Vertice* v1 = grafo->vertices; v1 != NULL; v1 = v1->proximo) {
        for (Vertice* v2 = v1->proximo; v2 != NULL; v2 = v2->proximo) {
            if (v1->info.frequencia == v2->info.frequencia) {
                adicionarAresta(v1, v2);
                adicionarAresta(v2, v1);
            }
        }
    }

    return grafo;
}
#pragma endregion

#pragma region mostrarGrafo
/**
 * @brief Mostra o grafo no formato de lista de adjacências.
 * @param g Ponteiro para o grafo.
 * @return 1 se o grafo foi mostrado com sucesso, 0 caso contrário.
 */
int mostrarGrafo(GR* grafo) {
    if (!grafo || !grafo->vertices) return 0;
    Vertice* g = grafo->vertices;
    while (g) {
        printf("%c (%d,%d): ", g->info.frequencia, g->info.x, g->info.y);
        Aresta* a = g->adj;
        while (a) {
            printf("-> %c(%d,%d) ",
                   a->destino->info.frequencia,
                   a->destino->info.x,
                   a->destino->info.y);
            a = a->prox;
        }
        printf("\n");
        g = g->proximo;
    }
    return 1;
}
#pragma endregion

#pragma region limparVisitados
/**
 * @brief Limpa os vértices visitados no grafo.
 * @param g Ponteiro para o grafo.
 */
void limparVisitados(GR* grafo) {
    if (!grafo) return;
    for (Vertice* g = grafo->vertices; g; g = g->proximo)
        g->visitado = 0;
}
#pragma endregion

#pragma region libertarGrafo
/**
 * @brief Liberta a memória alocada para o grafo.
 * @param g Ponteiro para o grafo.
 * @return 1 se a memória foi libertada com sucesso, 0 caso contrário.
 */
int libertarGrafo(GR* grafo) {
    if (!grafo) return 0;
    Vertice* g = grafo->vertices;
    while (g) {
        Aresta* a = g->adj;
        while (a) {
            Aresta* temp = a;
            a = a->prox;
            free(temp);
        }
        Vertice* tempV = g;
        g = g->proximo;
        free(tempV);
    }
    free(grafo);
    return 1;
}
#pragma endregion

#pragma region bfs
/**
 * @brief Realiza a busca em largura (BFS) no grafo a partir de um vértice de origem.
 * @param origem Vértice de origem.
 */
void bfs(GR* grafo, Vertice* origem) {
    if (!origem || !grafo) return;

    Vertice* fila[MAX_FILA];
    int inicio = 0, fim = 0;

    origem->visitado = 1;
    fila[fim++] = origem;

    while (inicio < fim) {
        Vertice* atual = fila[inicio++];
        printf("Visitado: %c (%d,%d)\n", atual->info.frequencia, atual->info.x, atual->info.y);

        for (Aresta* adj = atual->adj; adj != NULL; adj = adj->prox) {
            if (!adj->destino->visitado) {
                adj->destino->visitado = 1;
                fila[fim++] = adj->destino;
            }
        }
    }
}
#pragma endregion

#pragma region dfs
/**
 * @brief Realiza a busca em profundidade (DFS) no grafo a partir de um vértice de origem.
 * @param origem Vértice de origem.
 */
void dfs(GR* grafo, Vertice* origem) {
    if (!origem || origem->visitado) return;

    origem->visitado = 1;
    printf("Visitado: %c (%d,%d)\n", origem->info.frequencia, origem->info.x, origem->info.y);

    for (Aresta* adj = origem->adj; adj != NULL; adj = adj->prox) {
        if (!adj->destino->visitado)
            dfs(grafo, adj->destino);
    }
}
#pragma endregion

#pragma region guardarGrafoBinario
/*Exemplo de guardar grafo em binário
int guardarGrafoBinario(const char* nomeFicheiro, Vertice* grafo) {
    FILE* f = fopen(nomeFicheiro, "wb");
    if (!f) return 0;

    for (Vertice* v = grafo; v != NULL; v = v->proximo) {
        fwrite(&v->info, sizeof(Antena), 1, f);
        for (Aresta* a = v->adj; a != NULL; a = a->prox) {
            fwrite(&a->distancia, sizeof(float), 1, f);
            fwrite(&a->destino->info, sizeof(Antena), 1, f);
        }
    }

    fclose(f);
    return 1;
}*/

/**
 * @brief Guarda o grafo em um ficheiro binário.
 * @param nomeFicheiro Nome do ficheiro onde o grafo será guardado.
 * @param grafo Ponteiro para o grafo a ser guardado.
 * @return 1 se o grafo foi guardado com sucesso, 0 caso contrário.
 */
int guardarGrafoBinario(const char* nomeFicheiro, GR* grafo) {
    FILE* f = fopen(nomeFicheiro, "wb");
    if (!f) {
        perror("Erro ao abrir ficheiro binário");
        return 0;
    }

    for (Vertice* v = grafo->vertices; v != NULL; v = v->proximo) {
        fwrite(&v->info, sizeof(Antena), 1, f);

        int numArestas = 0;
        for (Aresta* a = v->adj; a != NULL; a = a->prox)
            numArestas++;

        fwrite(&numArestas, sizeof(int), 1, f);

        for (Aresta* a = v->adj; a != NULL; a = a->prox) {
            fwrite(&a->distancia, sizeof(float), 1, f);
            fwrite(&a->destino->info, sizeof(Antena), 1, f);
        }
    }

    fclose(f);
    return 1;
}

#pragma endregion