/**
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-05-18
 * 
 * @file antenas.c
 * @brief Impleementação das funções de manipulação da lista ligada de antenas.
 */

 #include <stdio.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include <malloc.h>
 #include <string.h>
 
 #include "antenas.h"
 
 #define MAX_LINHAS 100
 #define MAX_COLUNAS 100
 
 #pragma region carregarAntenasDeFicheiro
 /**
  * @brief Lê um ficheiro linha a linha e insere antenas na lista ligada.
  * 
  * Apenas são considerados como antenas os caracteres diferentes de '.' e '0'.
  * As antenas são inseridas na lista com as coordenadas correspondentes.
  * 
  * @param ficheiro Nome do ficheiro de entrada.
  * @return Ponteiro para a lista de antenas.
  */
 Antena* carregarAntenasDeFicheiro(const char* ficheiro) {
     FILE* file = fopen(ficheiro, "r");
     if (!file) {
         return NULL;
     }
 
     Antena* lista = NULL;
     char linha[100];
     int y = 0;
 
     while (fgets(linha, sizeof(linha), file) && y < MAX_LINHAS) {
         for (int x = 0; linha[x] != '\n' && linha[x] != '\0'; x++) {
             if ((linha[x] >= 'A' && linha[x] <= 'Z') || (linha[x] >= 'a' && linha[x] <= 'z')) {
                 lista = inserirAntena(lista, linha[x], x, y);
             }
         }
         y++;
     }
     fclose(file);
 
     return lista;
 }
 #pragma endregion
 
 #pragma region inserirAntena
 /**
  * @brief Insere uma nova antena no início da lista ligada.
  * 
  * A nova antena será a nova cabeça da lista.
  * 
  * @param lista Cabeça da lista.
  * @param frequencia Carácter da antena.
  * @param x Coordenada X.
  * @param y Coordenada Y.
  * @return Ponteiro para a nova cabeça da lista.
  */
 Antena* inserirAntena(Antena* lista, char frequencia, int x, int y) {
     Antena* nova = (Antena*)malloc(sizeof(Antena));
     if (nova == NULL) {
         return lista;
     }
 
     nova->frequencia = frequencia;
     nova->x = x;
     nova->y = y;
     nova->prox = lista;
 
     return nova;
 }
 #pragma endregion
 
 #pragma region removerAntena
 /**
  * @brief Remove uma antena da lista ligada com base nas coordenadas fornecidas.
  * 
  * @param lista Cabeça da lista.
  * @param x Coordenada X da antena a ser removida.
  * @param y Coordenada Y da antena a ser removida.
  * @return Nova cabeça da lista.
  */
 Antena* removerAntena(Antena* lista, int x, int y) {
     Antena* atual = lista;
     Antena* anterior = NULL;
 
     while (atual) {
         if (atual->x == x && atual->y == y) {
             if (anterior) {
                 anterior->prox = atual->prox;
             } else {
                 lista = atual->prox;
             }
 
             free(atual);
             return lista; // Retorna a nova cabeça da lista
         }
         anterior = atual;
         atual = atual->prox;
     }
 
     return lista; // Caso não encontre a antena, retorna a lista original
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