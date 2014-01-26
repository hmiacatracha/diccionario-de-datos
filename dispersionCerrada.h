#include "comun.h"

typedef struct entrada_ {
	int ocupada;
	char clave[LONGITUD_CLAVE];
	char sinonimos[LONGITUD_SINONIMOS];
} entrada;
typedef entrada *tabla_cerrada;

void inicializarC(tabla_cerrada d, int tamTabla);
int funResolucionColision(int i);
int buscarPosicion(char *clave, tabla_cerrada d, int tamTabla, int *colisiones,
		int (*calcularDispersion)(char *, int));
void insertarC(char *clave, char *sinonimo, tabla_cerrada d, int tamTabla,
		int *colisiones, int (*calcularDispersion)(char *, int));
void imprimirC(tabla_cerrada d, int tamTabla);
void imprimirBusquedaB(char*clave, tabla_cerrada dc, int n, int *colisiones);
void pruebaDispersionCerrada();
void pruebaDispersionCerradaTest(int nElementos, item sinonimos[]);
