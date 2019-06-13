#include "../lib/tempo.h"

void imprimir_usuario (struct timeval start, struct timeval tend){
	double startsec = (((double)start.tv_sec) + ((double)start.tv_usec/1000000));
	double endsec = (((double)tend.tv_sec) + ((double)tend.tv_usec/1000000));
	double process = (endsec - startsec);
	printf("| Tempo de Leitura: %.5fseg.       |\n| Tempo de Processamento: %.5fseg. |\n", startsec, process);
}

void imprimir_sistema (struct timeval start, struct timeval tend){
	double sistema = (((double)tend.tv_sec) + ((double)tend.tv_usec/1000000)) - (((double)start.tv_sec) + ((double)start.tv_usec/1000000));
	printf("| Tempo de Sistema: %.5fseg.       |\n", sistema);
}

void fim_do_programa(int sys_print, int user_print, int total_print) {
	getrusage(RUSAGE_SELF, &r_usage);
	user_end = r_usage.ru_utime;
	sys_end = r_usage.ru_stime;

	printf("\n+-------------------------------------+\n");
	if (user_print == 1) {
		imprimir_usuario(user_start, user_end);
	}
	if (sys_print == 1) {
		imprimir_sistema(sys_start, sys_end);
	}

	gettimeofday(&end ,NULL);
	if (total_print == 1) {
		double total = (((double)end.tv_sec) + ((double)end.tv_usec/1000000)) - (((double)start.tv_sec) + ((double)start.tv_usec/1000000));
		printf("| Tempo Total: %.5fseg.            |\n", total);

	}
	printf("+-------------------------------------+\n");
}