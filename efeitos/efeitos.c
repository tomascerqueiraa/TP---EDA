/**
 * @file efeitos.c
 * @brief Implementação das funções para calcular e gerenciar os efeitos nefastos causados por antenas.
*/

#include <stdio.h>
#include <stdlib.h>

#include "efeitos.h"

#pragma region calcularEfeito
/**
 * @brief Verifica se duas antenas estão alinhadas e se uma está ao dobro da distância da outra.
 *        Se sim, calcula a localização com efeito nefasto.
 * 
 * Esta função determina se duas antenas da mesma frequência estão alinhadas e se a distância entre elas
 * é tal que o ponto médio entre elas resulta em um efeito nefasto. O ponto de efeito nefasto é calculado 
 * como o ponto médio entre as antenas quando elas estão alinhadas (horizontal, vertical ou diagonal).
 * 
 * @param a Ponteiro para a primeira antena.
 * @param b Ponteiro para a segunda antena.
 * @param xRes Ponteiro para a coordenada X do efeito nefasto calculado.
 * @param yRes Ponteiro para a coordenada Y do efeito nefasto calculado.
 * @return Retorna 1 se houver efeito nefasto entre as antenas, 0 caso contrário.
 */
int calcularEfeito(Antena* a, Antena* b, int* xRes, int* yRes) {
    // Verifica se as antenas estão alinhadas horizontalmente, verticalmente ou diagonalmente
    if (a->x == b->x || a->y == b->y || abs(b->x - a->x) == abs(b->y - a->y)) {
         // Calcula o ponto médio
        *xRes = (a->x + b->x) / 2;
        *yRes = (a->y + b->y) / 2;

        // Verifica se o ponto médio não corresponde à posição de nenhuma das antenas
        if ((*xRes == a->x && *yRes == a->y) || (*xRes == b->x && *yRes == b->y)) {
            return 0; // Ignora este efeito
        }
        return 1; // Retorna 1 se houver efeito nefasto
    }
    return 0; // Retorna 0 se não houver efeito nefasto
}
#pragma endregion

#pragma region efeitoExiste
/**
 * @brief Verifica se um efeito com coordenadas específicas já existe na lista de efeitos.
 * 
 * Esta função percorre a lista de efeitos nefastos e verifica se já existe um efeito com as coordenadas
 * fornecidas (x, y). Se o efeito já existir, a função retorna 1, caso contrário, retorna 0.
 * 
 * @param lista Ponteiro para a lista de efeitos.
 * @param x Coordenada X do efeito a ser verificado.
 * @param y Coordenada Y do efeito a ser verificado.
 * @return Retorna 1 se o efeito já existir na lista, 0 caso contrário.
 */
int efeitoExiste(Efeito* lista, int x, int y) {
    while (lista) {  // Percorre a lista de efeitos
        if (lista->x == x && lista->y == y)  // Verifica se as coordenadas do efeito já existem na lista
            return 1;  // Efeito já existe
        lista = lista->prox;  // Avança para o próximo efeito na lista
    }
    return 0;  // Efeito não encontrado na lista
}
#pragma endregion

#pragma region adicionarEfeito
/**
 * @brief Adiciona um novo efeito à lista de efeitos.
 * 
 * Esta função adiciona um novo efeito com as coordenadas fornecidas à lista ligada de efeitos nefastos.
 * Antes de adicionar, a função verifica se o efeito já existe na lista para evitar duplicação de efeitos.
 * A inserção do novo efeito é feita no início da lista.
 * 
 * @param lista Ponteiro para a lista de efeitos.
 * @param x Coordenada X do novo efeito.
 * @param y Coordenada Y do novo efeito.
 */
void adicionarEfeito(Efeito** lista, int x, int y) {
    if (efeitoExiste(*lista, x, y)) return;  // Se o efeito já existir na lista, não faz nada

    // Cria um novo nó para o efeito
    Efeito* novo = (Efeito*)malloc(sizeof(Efeito));
    novo->x = x;  // Atribui a coordenada X do efeito
    novo->y = y;  // Atribui a coordenada Y do efeito
    novo->prox = *lista;  // O próximo efeito será o atual primeiro da lista
    *lista = novo;  // A cabeça da lista agora aponta para o novo efeito
}
#pragma endregion

#pragma region deduzirEfeitosNefastos
/**
 * @brief Gera uma lista de localizações com efeito nefasto a partir das antenas.
 * 
 * Esta função percorre a lista de antenas e verifica todos os pares de antenas para calcular
 * os efeitos nefastos entre elas. Para cada par de antenas, se as condições forem atendidas
 * (mesma frequência e distância adequada), um novo efeito é gerado e adicionado à lista de efeitos.
 * 
 * @param lista Ponteiro para a lista de antenas.
 * @return Retorna a lista de efeitos nefastos gerados.
 */
Efeito* deduzirEfeitosNefastos(Antena* lista) {
    Efeito* efeitos = NULL;

    for (Antena* a = lista; a != NULL; a = a->prox) {
        for (Antena* b = lista; b != NULL; b = b->prox) {
            if (a == b) continue;  // Ignorar comparações com a própria antena

            int x, y;
            if (calcularEfeito(a, b, &x, &y)) {
                adicionarEfeito(&efeitos, x, y);
            }
        }
    }

    return efeitos;
}
#pragma endregion

#pragma region listarEfeitos
/**
 * @brief Exibe todos os efeitos nefastos encontrados na consola.
 * 
 * Esta função imprime na consola todos os efeitos nefastos encontrados na lista. A exibição é feita
 * de forma tabular, mostrando as coordenadas de cada efeito.
 * 
 * @param lista Ponteiro para a lista de efeitos.
 */
void listarEfeitos(Efeito* lista) {
    printf("\n+----------------------+\n");
    printf("| Efeitos Nefastos     |\n");
    printf("+----------------------+\n");
    while (lista) {
        printf("|   (%2d, %2d)          |\n", lista->x, lista->y);  // Exibe as coordenadas do efeito
        lista = lista->prox;  // Avança para o próximo efeito
    }
    printf("+----------------------+\n");
}
#pragma endregion

#pragma region limparEfeitos
/**
 * @brief Liberta a memória associada à lista de efeitos.
 * 
 * Esta função percorre a lista de efeitos e liberta a memória alocada para cada nó da lista.
 * Ao fim, a memória de toda a lista de efeitos é limpa.
 * 
 * @param lista Ponteiro para a lista de efeitos.
 */
void limparEfeitos(Efeito* lista) {
    while (lista) {
        Efeito* temp = lista;  // Guarda o ponteiro do nó atual
        lista = lista->prox;  // Avança para o próximo nó
        free(temp);  // Limpa a memória do nó atual
    }
}
#pragma endregion