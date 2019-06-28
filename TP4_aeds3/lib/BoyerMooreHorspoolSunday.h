#ifndef BOYERMOOREHORSPOOLSUNDAY_H
#define BOYERMOOREHORSPOOLSUNDAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qnt_letras_tab; // guarda a quantidade de letras individais no padrao (sem repetir)

int is_in_array_ (char *array, char letra);
int deslocamento_ (int** tabela, char letra, int tamanho_padrao);
int** cria_tabela_ (char *padrao, int tamanho);
void bmhs (char *texto, char *padrao);

#endif