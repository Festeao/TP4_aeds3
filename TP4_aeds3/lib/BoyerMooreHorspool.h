#ifndef BOYERMOOREHORSPOOL_H
#define BOYERMOOREHORSPOOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qnt_letras_tab; // guarda a quantidade de letras individais no padrao (sem repetir)

int is_in_array (char *array, char letra);
int deslocamento (int** tabela, char letra, int tamanho_padrao);
int** cria_tabela (char *padrao, int tamanho);
void bmh (char *texto, char *padrao);

#endif