#ifndef TEMPO_H
#define TEMPO_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

struct rusage r_usage;
struct timeval start, end;
struct timeval user_start, user_end;
struct timeval sys_start, sys_end;

void imprimir_usuario (struct timeval start, struct timeval tend);
void imprimir_sistema (struct timeval start, struct timeval tend);
void fim_do_programa ();
#endif