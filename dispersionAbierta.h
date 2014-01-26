#include "comun.h"

typedef struct nodo {
	char clave[LONGITUD_CLAVE];
	char sinonimos[LONGITUD_SINONIMOS];
	struct nodo *siguiente;
};

typedef struct nodo *pnodo;
typedef pnodo lista;
typedef lista *tabla_abierta;


void crearLista(lista *l);
pnodo buscarLista(char *elemento, pnodo lista, int *colisiones);
void insertarLista(char *clave, char *sinonimo, pnodo p);
void desplegarHashLista(pnodo lista);
void inicializarA(tabla_abierta t, int tamTabla);
char *buscarA(char *clave, tabla_abierta t, int tamTabla, int *colisiones,int (*calcularDispersion)(char *, int));
void imprimirBusquedaA(item t, tabla_abierta d, int n, int *colisiones);
void insertarA(item datos, tabla_abierta t, int tamTabla, int *colisiones,int (*calcularDispersion)(char *, int));
void imprimirA(tabla_abierta t, int lHash);
void pruebaDispersionAbierta();
void pruebaDispersionAbiertaTest(int nElementos, item sinonimos[]);
