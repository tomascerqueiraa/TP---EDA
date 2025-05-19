/**
 * @author Tomás Cerqueira Gomes (a31501@alunos.ipca.pt)
 * @date 2025-05-18
 * 
 * @file antenas.h
 * @brief Definição da estrutura de dados para as antenas.
 */

 #ifndef ANTENAS_H
 #define ANTENAS_H
 
 #include <stdio.h>
 #include <stdlib.h>

 /**
  * @struct Antena
  * @brief Representa uma antena na cidade.
  *
  * Esta estrutura define uma antena, armazenando a sua frequência
  * e localização (x, y).
  */
 typedef struct Antena {
     char frequencia;  /**< Caracter que representa a frequência da antena */
     int x;            /**< Coordenada X da antena */
     int y;            /**< Coordenada Y da antena */
     //Aresta* adj; /**< Ponteiro para a lista de arestas (antenas adjacentes) */
     struct Antena* prox; /**< Ponteiro para a próxima antena na lista ligada */
     int visitado;   // usado no DFS/BFS
 } Antena;
 
 /**
  * @brief Lê um ficheiro e armazena as antenas na lista ligada.
  * 
  * Esta função abre um ficheiro de texto que representa um mapa da cidade
  * e insere todas as antenas encontradas numa lista ligada.
  * São ignorados os caracteres '.' e '0'.
  * 
  * @param filename Nome do ficheiro de entrada.
  * @return Ponteiro para a cabeça da lista de antenas.
  */
 Antena* carregarAntenasDeFicheiro(const char* ficheiro);
 
 /**
  * @brief Cria um novo nó de antena.
  * 
  * Esta função reserva memória e inicializa uma nova antena com os dados fornecidos.
  * 
  * @param frequencia Caracter representando a frequência da antena.
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  * @return Ponteiro para a nova antena, ou NULL em caso de erro.
  */
 Antena* criarAntena(char frequencia, int x, int y);
 
 /**
  * @brief Insere uma antena no início da lista ligada.
  * 
  * A nova antena criada será inserida como o novo primeiro nó da lista.
  * 
  * @param lista Ponteiro para a cabeça da lista ligada.
  * @param frequencia Caracter representando a frequência da antena.
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  * @return Nova cabeça da lista de antenas.
  */
 Antena* inserirAntena(Antena* lista, char frequencia, int x, int y);
 
 /**
  * @brief Remove uma antena da lista ligada com base nas coordenadas fornecidas.
  * 
  * @param lista Cabeça da lista ligada.
  * @param x Coordenada X da antena a ser removida.
  * @param y Coordenada Y da antena a ser removida.
  * @return Nova cabeça da lista de antenas.
  */
 Antena* removerAntena(Antena* lista, int x, int y);
 
 /**
  * @brief Liberta toda a memória da lista ligada de antenas.
  * 
  * Esta função percorre a lista e liberta todos os nós alocados dinamicamente.
  * 
  * @param lista Cabeça da lista ligada.
  */
 void limparLista(Antena* lista);
 
 /**
  * @brief Mostra todas as antenas da lista ligada.
  * 
  * Imprime uma tabela formatada com a frequência e as coordenadas de cada antena.
  * 
  * @param lista Cabeça da lista ligada.
  */
 void listarAntenas(Antena* lista);
 
 #endif 