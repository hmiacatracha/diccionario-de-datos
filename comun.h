#ifndef COMUN
#define COMUN

#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define UMBRAL 2000
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

typedef struct {
	char clave[LONGITUD_CLAVE];
	char sinonimos[LONGITUD_SINONIMOS];
} item;

double microsegundos();
int dispersion(char *clave, int tamTabla);
int dispersionA(char *clave, int tamTabla);
int dispersionB(char *clave, int tamTabla);
int leer_sinonimos(item datos[]);

#endif
