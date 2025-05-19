/**
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-05-18
 * 
 * @file efeitos.h
 * @brief Declarações e definições relacionadas aos efeitos nefastos causados por antenas.
*/

#ifndef EFEITOS_H
#define EFEITOS_H

#include "../antenas/antenas.h"

/**
 * @struct Efeito
 * @brief Representa uma localização com efeito nefasto.
 * 
 * Um efeito nefasto ocorre quando duas antenas com a mesma frequência
 * estão alinhadas e uma está ao dobro da distância da outra em relação a um ponto.
*/
typedef struct Efeito {
    int x;                  /**< Coordenada X do efeito nefasto */
    int y;                  /**< Coordenada Y do efeito nefasto */
    struct Efeito* prox;    /**< Ponteiro para o próximo nó da lista ligada */
} Efeito;

/**
 * @brief Deduz os efeitos nefastos com base nas posições das antenas.
 * 
 * Analisa todos os pares de antenas com a mesma frequência e determina
 * as localizações com efeito nefasto, armazenando-as numa lista ligada.
 * 
 * @param lista Lista ligada de antenas.
 * @return Lista ligada de efeitos nefastos.
 */
Efeito* deduzirEfeitosNefastos(Antena* lista);

/**
 * @brief Lista todos os efeitos nefastos na consola.
 * 
 * Mostra de forma tabular todas as localizações com efeito nefasto armazenadas.
 * 
 * @param lista Lista ligada de efeitos.
 */
void listarEfeitos(Efeito* lista);

/**
 * @brief Liberta a memória associada à lista de efeitos nefastos.
 * 
 * Percorre a lista ligada e liberta todos os nós alocados dinamicamente.
 * 
 * @param lista Lista ligada de efeitos.
 */
void limparEfeitos(Efeito* lista);

#endif