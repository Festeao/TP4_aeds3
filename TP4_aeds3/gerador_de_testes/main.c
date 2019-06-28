#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main (int agrc, char *agrv[]) {

	srand(time(NULL));

	if (!agrv[1]) {
		printf("Passe o nome do arquivo por aprametro\n");
		exit(1);
	}

	FILE *arquivo_entrada = fopen(agrv[1], "r");
	if (!arquivo_entrada) {
		printf("Erro ao abrir o arquivo\n");
		exit(1);
	}

	FILE *arquivo_saida = fopen("../inputs/padroes.txt", "w");
	if (!arquivo_saida) {
		printf("Erro ao abrir o arquivo\n");
		exit(1);
	}

	int quantidade_padroes = 2 + rand() % 20;
	int tamanho_max = 4 + rand() % 20;
	char *string_aux = (char*)calloc(tamanho_max, sizeof(char));
	char aux;
	int i = 0, j = 0, max = 0;

	while ((aux = fgetc(arquivo_entrada)) != EOF && i < quantidade_padroes) {
		setbuf(arquivo_saida, NULL);
		if (aux == ' ' || aux == '\n' || aux == '\t' || j == tamanho_max - 2) {
			string_aux[j] = '\n';
			string_aux[j + 1] = '\0';
			if (string_aux[0] != '\n' && strlen(string_aux) - 1 > 3 && rand() % 100 >= 60) {
				if (fputs(string_aux, arquivo_saida) == EOF) {
					printf("Erro na escrita\n");
					fclose(arquivo_entrada);
					fclose(arquivo_saida);
					exit(1);
				}
				else if (strlen(string_aux) - 1 > max) {
					max = strlen(string_aux) - 1;
				}
				fflush(arquivo_saida);
				i++;
			}
			j = 0;
			free(string_aux);
			string_aux = (char*)calloc(tamanho_max, sizeof(char));
		}
		else {
			string_aux[j] = aux;
			j++;
		}
	}

	fclose(arquivo_saida);
	arquivo_saida = fopen("../inputs/padroes.txt", "r+");

	fprintf(arquivo_saida, "%d %d\n", i, max);

	fclose(arquivo_entrada);
	fclose(arquivo_saida);
	free(string_aux);

	return 0;
}