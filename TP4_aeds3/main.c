#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/BoyerMooreHorspool.h"
#include "lib/BoyerMooreHorspoolSunday.h"
#include "lib/ShiftAndExato.h"
#include "lib/ShiftAndAproximado.h"
#include "lib/tempo.h"

int main (int argc, char *argv[]) {

	system("clear");

	if (!argv[1]) {
		printf("Nome do arquivo com o texto nao foi passado como parametro\n");
		exit(1);
	}
	if (!argv[2]) {
		printf("Nome do arquivo com os padroes nao foi passado como parametro\n");
		exit(1);
	}
	if (!argv[3] || (*argv[3] != '1' && *argv[3] != '2' && *argv[3] != '3' && *argv[3] != '4' && *argv[3] != '5')) {
		printf("Opcao de algoritmo a ser rodado nao esta correta\n1_Boyer Moore Horspool\n2_Boyer Moore Horspool Sunday\n3_Shift And Exato\n4_Shift And Aproximado\n5_Paralelizado\n");
		exit(1);
	}

	FILE *arquivo_texto = fopen(argv[1], "r");
	if (!arquivo_texto) {
		printf("Erro ao abrir o arquivo com o texto. Confira se o nome e caminho do arquivo estao corretos\n");
		exit(1);
	}

	FILE *arquivo_padroes = fopen(argv[2], "r");
	if (!arquivo_padroes) {
		printf("Erro ao abrir o arquivo com os padroes. Confira se o nome e caminho do arquivo estao corretos\n");
		exit(1);
	}

	//guardando o texto na memoria principal (talvez seja uma ma ideia, mas vou deixar acontecer <3)

	//descbrindo o tamanho do arquivo
	fseek(arquivo_texto, 0, SEEK_END);
	int tamanho_texto = ftell(arquivo_texto);
	int cont = 0;
	//rebobinando o ponteiro para o inicio do arquivo
	rewind(arquivo_texto);

	// alocando um espaco em memoria pricipal para armazenar o texto
	char *array_texto = (char*)malloc(sizeof(char)*tamanho_texto);
	
	while (!feof(arquivo_texto)) {
		array_texto[cont] = getc(arquivo_texto);
		cont++;
	}
	array_texto[tamanho_texto] = '\0'; // setando o terminador na ultima posicao da string

	fclose(arquivo_texto);

	//----------------guardando os padroes em um array de strings-----------------------------------

	int numero_de_padroes; // quantidade de padroes no arquivo
	int tamanho_buffer;	// tamanho do maior padrao do arquivo
	fscanf(arquivo_padroes, "%d %d", &numero_de_padroes, &tamanho_buffer);

	//alocacao do espaco para os padroes

	char **array_padroes = (char**)malloc(sizeof(char*)*numero_de_padroes);

	char *buffer_aux = (char*)malloc(sizeof(char)*tamanho_buffer + 1); // buffer auxiliar na leitura dos padrões contidos no arquivo

	int aux_leitura;
	for (int trigger = 0, i = 0; !feof(arquivo_padroes) && trigger == 0; i++) {
		aux_leitura = fscanf(arquivo_padroes, "%s", buffer_aux);
		if (aux_leitura != EOF) {
			array_padroes[i] = (char*)malloc(sizeof(char) * (strlen(buffer_aux) + 1));
			strcpy(array_padroes[i], buffer_aux);
		}
		else {
			trigger = 1;
		}
	}

	free(buffer_aux);

	fclose(arquivo_padroes);

	//------------------------inicio da execucao dos algoritmos-----------------------------------

	/*ate aqui, ja se obteve as seguintes informacoes:
	o meu texto se encontra na string "array_texto"
	o tamanho do meu texto se encontra na variavel "tamanho_texto"
	todos os meus padroes se encontram no vetor de arrays "array_padroes"
	a quantidade de padroes existentes se encontra na variavel "numero_de_padroes"*/

	//inincio da contagem de tempo
	gettimeofday(&start ,NULL);
	getrusage(RUSAGE_SELF, &r_usage);
	user_start = r_usage.ru_utime;
	sys_start = r_usage.ru_stime;

	switch (atoi(argv[3])) {
		case 1:
			for (int i = 0; i < numero_de_padroes; i++) {
				bmh(array_texto, array_padroes[i]);
			}
		break;
		case 2:
			for (int i = 0; i < numero_de_padroes; i++) {
				bmhs(array_texto, array_padroes[i]);
			}
		break;
		case 3:

		break;
		case 4:

		break;
		case 5:

		break;
	}

	//fim da contagem de tempo
	fim_do_programa(0, 1, 0); // imprime o tempo de leitura e o tempo de processamento

	//liberando o vetor de strings
	for (int i = 0; i < numero_de_padroes; i++) {
		free(array_padroes[i]);
	}
	free(array_padroes);
	//liberando o texto
	free(array_texto);
	return 0;
}