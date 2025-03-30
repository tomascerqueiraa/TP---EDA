/**
 * @file antenas.c
 * @brief Impleementação das funções de manipulação da lista ligada de antenas.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "antenas.h"

#define MAX_LINHAS 100  // Número máximo de linhas suportadas
#define MAX_COLUNAS 100 // Número máximo de colunas suportadas

#pragma region carregarAntenasDeFicheiro
/**
 * @brief Lê um ficheiro linha a linha e insere antenas na lista ligada.
 * 
 * Apenas são considerados como antenas os caracteres diferentes de '.' e '0'.
 * As antenas são inseridas na lista com as coordenadas correspondentes.
 * 
 * @param lista Ponteiro para o ponteiro da lista ligada.
 * @param ficheiro Nome do ficheiro de entrada.
 */
 void carregarAntenasDeFicheiro(Antena** lista, const char* ficheiro) {
    FILE* file = fopen(ficheiro, "r");
    if (!file) {
        printf("Erro: Não foi possível abrir o ficheiro %s.\n", ficheiro);
        return;
    }
    char linha[100];
    int y = 0;
    while (fgets(linha, sizeof(linha), file) && y < MAX_LINHAS) {
        for (int x = 0; linha[x] != '\n' && linha[x] != '\0'; x++) {
            // Verifica se o caractere é uma letra (A-Z ou a-z)
            if ((linha[x] >= 'A' && linha[x] <= 'Z') || (linha[x] >= 'a' && linha[x] <= 'z')) {
                // Chama a função para inserir a antena na lista com as coordenadas (x, y)
                inserirAntena(lista, linha[x], x, y);
            }
        }
        y++;  // Incrementa o índice de linha
    }
    fclose(file);
}
#pragma endregion

#pragma region inserirAntena
/**
 * @brief Insere uma nova antena no início da lista ligada.
 * 
 * A nova antena será a nova cabeça da lista.
 * 
 * @param lista Ponteiro para a lista.
 * @param frequencia Carácter da antena.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
/*Antena** lista é um ponteiro para o ponteiro, utilizado para manipular diretamente o início da lista ligada, 
que é importante quando precisamos de modificar a cabeça da lista (adicionar ou remover elementos no início).*/
void inserirAntena(Antena** lista, char frequencia, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (nova == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        return;
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = *lista;
    /*'lista = nova;': Modifica a cabeça da lista, fazendo com que ela aponte para a 
    nova antena inserida, e deslocando o restante da lista para baixo.*/
    *lista = nova;
}
#pragma endregion

#pragma region removerAntena

/**
 * @brief Remove uma antena da lista ligada com base nas coordenadas fornecidas.
 * 
 * @param lista Ponteiro para o ponteiro da cabeça da lista ligada.
 * @param x Coordenada X da antena a ser removida.
 * @param y Coordenada Y da antena a ser removida.
 * @return Retorna 1 se a antena foi removida com sucesso, 0 caso contrário.
 */
 /*'Antena**' - Recebe como entrada um ponteiro para o ponteiro da 
 cabeça da lista (lista), e as coordenadas x e y da antena a ser removida*/
int removerAntena(Antena** lista, int x, int y) {
    Antena* atual = *lista;
    Antena* anterior = NULL;

    // Percorre a lista para encontrar a antena com as coordenadas fornecidas
    while (atual) {
        if (atual->x == x && atual->y == y) {
            // A antena foi encontrada
            if (anterior) {
                // A antena não é a primeira da lista
                anterior->prox = atual->prox;
            } else {
                // A antena é a primeira da lista
                *lista = atual->prox;
            }

            free(atual); // Libera a memória da antena removida
            return 1; // Retorna 1 para indicar sucesso
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0; // Retorna 0 se a antena não foi encontrada
}

#pragma endregion

#pragma region limparLista
/**
 * @brief Liberta toda a memória associada à lista ligada de antenas.
 * 
 * @param lista Cabeça da lista.
 */
void limparLista(Antena* lista) {
    Antena* aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}
#pragma endregion

#pragma region listarAntenas
/**
 * @brief Imprime uma tabela com todas as antenas da lista.
 * 
 * Mostra frequência, X e Y de forma formatada.
 * 
 * @param lista Lista de antenas.
 */
void listarAntenas(Antena* lista) {
    printf("+------------------+\n");
    printf("| Freq |  X  |  Y  |\n");
    printf("+------------------+\n");

    while (lista) {
        if (lista->frequencia != '.') { // Verifica se a frequência é diferente de '.'
            printf("|  %c  | %2d  | %2d  |\n", lista->frequencia, lista->x, lista->y);
        }
        lista = lista->prox;
    }

    printf("+------------------+\n");
}
#pragma endregion