#include "../lib/BoyerMooreHorspool.h"

int is_in_array (char *array, char letra) {
	/* recebe uma string e um caractere e retorna o indicie
	do caractere caso o mesmo se encontre na string*/
	for (int i = 0; i < strlen(array); i++) {
		if (array[i] == letra) {
			return i;
		}
	}
	return -1;
}

int deslocamento (int** tabela, char letra, int tamanho_padrao) {
	/* recebe uma tabela e um caractere e retorna o deslocamento
	do caractere caso o mesmo se encontre na tabela*/
	for (int i = 0; i < qnt_letras_tab; i++) {
		if (tabela[i][0] == letra) {
			return tabela[i][1];
		}
	}
	return tamanho_padrao;
}

int** cria_tabela (char *padrao, int tamanho) {
	/*funcao que cria a tabela de deslocamento*/
	//---------------descobrir qual o tamanho da tabela---------------
	int i; // contador
	qnt_letras_tab = 0;
	char *aux = (char*)calloc(tamanho, sizeof(char)); // inicializa o buffer auxiliar com 0
	for (i = 0; i < tamanho; i++) { // percorrer o padrao e verificar se existe alguma letra repetida
		if (is_in_array(aux, padrao[i]) == -1) {
			aux[qnt_letras_tab] = padrao[i];
			qnt_letras_tab++;
		}
	}
	//----------------------construir a tabela-------------------------
	//alocando tabela
	int **tabela = (int**)malloc(sizeof(int*) * qnt_letras_tab);
	for (i = 0; i < qnt_letras_tab; i++) {
		tabela[i] = (int*)malloc(sizeof(int) * 2);
		tabela[i][0] = aux[i];
		tabela[i][1] = tamanho;
	}
	//calculando deslocamentos
	for (i = 0; i < tamanho - 1; i++) {
		tabela[is_in_array(aux, padrao[i])][1] = tamanho - i - 1;
	}
	free(aux);
	return tabela;
}

void bmh (char *texto, char *padrao) {
	int i, j; //contadores
	int trigger; // variavel de controle
	int aux; // variavel auxiliar
	int tamanho_padrao = strlen(padrao);
	int tamanho_texto = strlen(texto);
	int **tabela = cria_tabela(padrao, tamanho_padrao);
	/*
	printf("%s\n", padrao);
	for (i = 0; i < qnt_letras_tab; i++) {
		printf("%c %d", tabela[i][0], tabela[i][1]);
	}
	printf("\n");
	*/
	for (i = tamanho_padrao - 1; i < tamanho_texto - 1;) {
		trigger = 0;
		for (j = tamanho_padrao - 1; j >= 0 && trigger == 0; j--) {
			if (padrao[j] != texto[i + (j - (tamanho_padrao - 1))]) {
				i += deslocamento(tabela, texto[i], tamanho_padrao);
				trigger = 1;
			}
			else if (j == 0) {
				printf("Match: \"%s\"/Indicie: %d\n", padrao, i - (tamanho_padrao - 1));
				i += deslocamento(tabela, texto[i], tamanho_padrao);
			}
		}
	}
	
	for (i = 0; i < qnt_letras_tab; i++) {
		free(tabela[i]);
	}

	free(tabela);
}