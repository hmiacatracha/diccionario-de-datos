#include "dispersionAbierta.h"

void crearLista(lista *l) {
	pnodo tmp = (pnodo) malloc(sizeof(struct nodo));
	if (tmp == NULL) {
		printf("memoria agotada\n");
		exit(EXIT_FAILURE);
	}
	tmp->siguiente = NULL;
	*l = tmp;
}
pnodo buscarLista(char *elemento, pnodo lista, int *colisiones) {
	pnodo p = lista->siguiente;
	while ((p != NULL) && (strcmp(p->clave, elemento) != 0)) {
		p = p->siguiente;
		(*colisiones)++;
	}
	return p;
}

void insertarLista(char *clave, char *sinonimo, pnodo p) {
	pnodo tmp = (pnodo) malloc(sizeof(struct nodo));
	if (tmp == NULL) {
		printf("memoria agotada\n");
		exit(EXIT_FAILURE);
	}

	strcpy(tmp->clave, clave);
	strcpy(tmp->sinonimos, sinonimo);
	tmp->siguiente = p->siguiente;
	p->siguiente = tmp;
}

void desplegarHashLista(pnodo lista) {
	lista = lista->siguiente;

	while (lista != NULL) {
		printf("( %s) ", lista->clave);
		lista = lista->siguiente;
	}
	return;
}

/**
 * DISPERSION ABIERTA
 */

void inicializarA(tabla_abierta t, int tamTabla) {
	int i;
	for (i = 0; i < tamTabla; i++) {
		lista l;
		crearLista(&l);
		t[i] = l;
	}
}

void insertarA(item datos, tabla_abierta t, int tamTabla, int *colisiones,
		int (*calcularDispersion)(char *, int)) {
	int i;
	char *pos;
	pos = buscarA(datos.clave, t, tamTabla, colisiones, calcularDispersion);
	if (pos == NULL) {
		i = calcularDispersion(datos.clave, tamTabla);
		insertarLista(datos.clave, datos.sinonimos, t[i]);
	}
}

char *buscarA(char *clave, tabla_abierta t, int tamTabla, int *colisiones,
		int (*calcularDispersion)(char *, int)) {

	int i = calcularDispersion(clave, tamTabla);
	pnodo nodo = buscarLista(clave, t[i], colisiones);

	if (nodo == NULL) {
		return NULL;
	}
	return nodo->clave;
}

void imprimirA(tabla_abierta t, int lHash) {
	int i;
	printf("\n ***TABLA ABIERTA \n");
	for (i = 0; i < lHash; i++) {
		printf("%4d- ", i);
		if (t[i]->siguiente == NULL) {
			printf("[]");
			printf("\n");
		} else {
			printf("[ ");
			desplegarHashLista(t[i]);
			printf("] ");
			printf("\n");
		}
	}
}

void imprimirBusquedaA(item t, tabla_abierta d, int n, int *colisiones) {
	char *busqueda;
	busqueda = buscarA(t.clave, d, n, colisiones, dispersion);

	if (busqueda != NULL)
		printf("Al buscar:%8s encuentro: %8s\n", t.clave, busqueda);
	else
		printf("No encontrado:%s", t.clave);
}

void pruebaDispersionAbierta() {
	int n = 11, cuenta = 6, colisiones = 0, busq = 7;
	char *clave[6] = { "ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN" };
	char *busco[7] = { "ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN", "CARLOS" };
	char *sinonimo[6] = { "7", "7", "6", "6", "7", "6" };
	tabla_abierta d = malloc(n * sizeof(lista));
	item sinonimos[n];
	item busqueda[n];
	inicializarA(d, n);

	int i;
	for (i = 0; i < cuenta; i++) {
		strcpy(sinonimos[i].clave, clave[i]);
		strcpy(sinonimos[i].sinonimos, sinonimo[i]);
		insertarA(sinonimos[i], d, n, &colisiones, dispersion);
	}
	imprimirA(d, n);
	printf("Numero total de colisiones: %d\n", colisiones);
	printf("\n");
	for (i = 0; i < busq; i++) {
		strcpy(busqueda[i].clave, busco[i]);
		imprimirBusquedaA(busqueda[i], d, n, &colisiones);
	}
	printf("\n");
	free(d);
}

void pruebaDispersionAAbiertaTest(int nElementos, item sinonimos[]) {

	int n = 19069;
	int i, j, k,z;
	int colisionesA = 0;
	double ta = 0, tb = 0, t = 0;
	double sub = 0, ajus = 0, sobre = 0;
	tabla_abierta d = malloc(n * sizeof(lista));
	inicializarA(d, n);

	printf("insertando %d elementos", nElementos);
	for (i = 0; i < nElementos; i++) {
		insertarA(sinonimos[i], d, n, &colisionesA, dispersionA);
	}
	printf("Numero total de colisiones: %d\n", colisionesA);

	printf("Buscando...\n");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.060 ",
			"t(n)/1.067", "t(n)/n^1.092");
   for (z = 0; z < 3; z++){
	for (j = 125; j <= 2000; j = j * 2) {
		ta = microsegundos();
		for (i = 0; i < j; i++) {
			buscarA(sinonimos[i].clave, d, n, &colisionesA, dispersionA);
		}
		tb = microsegundos();
		t = (tb - ta);
		if (t < UMBRAL) {
			ta = microsegundos();
			for (k = 0; k < 1000; k++) {
				for (i = 0; i < j; i++){
				buscarA(sinonimos[i].clave, d, n, &colisionesA,
						dispersionA);
				}
			}
			tb = microsegundos();
			t = (tb - ta)/1000;
			sub = t / pow(j, 1.060);
			ajus = t / pow(j, 1.067);
			sobre = t / pow(j, 1.092);
			printf("|%12d | %15.3f*  | %15.6f | %15.6f | %15.6f|\n", j, t, sub,
					ajus, sobre);
		} else {
			sub = t / pow(j, 1.060);
			ajus = t / pow(j,1.067);
			sobre = t / pow(j, 1.092);
			printf("|%12d | %15.3f   | %15.6f | %15.6f | %15.6f|\n", j, t, sub,
					ajus, sobre);
		}

	}
	printf("\n");
	}
	free(d);
}

void pruebaDispersionBAbiertaTest(int nElementos, item sinonimos[]) {

	int n = 19069;
	int i,j,k,z;
	int colisionesB = 0;
	double ta = 0, tb = 0, t = 0;
	double sub = 0, ajus = 0, sobre = 0;

	tabla_abierta d = malloc(n * sizeof(lista));
	inicializarA(d, n);

	printf("insertando %d elementos", nElementos);
	for (i = 0; i < nElementos; i++) {
		insertarA(sinonimos[i], d, n, &colisionesB, dispersionB);
	}
	printf("Numero total de colisiones: %d\n", colisionesB);
	printf("Buscando...\n");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.9 ",
			"t(n)/0.999", "t(n)/n^1.1");

   for (z = 0; z < 3; z++){
	for (j = 125; j <= 2000; j = j * 2) {
		ta = microsegundos();
		for (i = 0; i < j; i++) {
			buscarA(sinonimos[i].clave, d, n, &colisionesB, dispersionA);
		}
		tb = microsegundos();
		t = (tb - ta);
		if (t < UMBRAL) {
			ta = microsegundos();
			for (k = 0; k < 1000; k++) {
				for (i = 0; i < j; i++){
				buscarA(sinonimos[k].clave, d, n, &colisionesB,
						dispersionA);
				}
			}
			tb = microsegundos();
			t = (tb - ta)/1000;
			sub = t / pow(j, 0.9);
			ajus = t / pow(j, 0.999);
			sobre = t / pow(j, 1.1);
			printf("|%12d | %15.3f*  | %15.6f | %15.6f | %15.6f|\n", j, t, sub,
					ajus, sobre);
		} else {
			sub = t / pow(j, 0.9);
			ajus = t / pow(j, 0.999);
			sobre = t / pow(j, 1.1);
			printf("|%12d | %15.3f   | %15.6f | %15.6f | %15.6f|\n", j, t, sub,
					ajus, sobre);
		}

	}
	printf("\n");
	}

	free(d);
}

void pruebaDispersionAbiertaTest(int nElementos, item sinonimos[]) {
	printf("\n");
	printf("***Dispersion abierta con dispersion A \n");
	pruebaDispersionAAbiertaTest(nElementos, sinonimos);
	printf("\n");
	printf("***Dispersion abierta con dispersion B \n");
	pruebaDispersionBAbiertaTest(nElementos, sinonimos);
	printf("\n");

}
