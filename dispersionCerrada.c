#include "dispersionCerrada.h"
/*
 * IMPLEMENTACION DE DISPERSION CERRADA
 *
 */

void inicializarC(tabla_cerrada d, int tamTabla) {
	int i;
	for (i = 0; i < tamTabla; i++) {
		d[i].ocupada = 0;
	}
}

int funResolucionColision(int i) {
	return (i * i);
}

int buscarPosicion(char *clave, tabla_cerrada d, int tamTabla, int *colisiones,
		int (*calcularDispersion)(char *, int)) {

	int i = 0, posActual = 0;
	int x = calcularDispersion(clave, tamTabla);
	posActual = x;
	while ((d[posActual].ocupada == 1)
			&& (strcmp(d[posActual].clave, clave) != 0)) {
		i++;
		posActual = (x + (funResolucionColision(i))) % tamTabla;
		(*colisiones)++;
	}
	return posActual;
}

void insertarC(char *clave, char *sinonimo, tabla_cerrada d, int tamTabla,
		int *colisiones, int (*calcularDispersion)(char *, int)) {
	int pos;
	pos = buscarPosicion(clave, d, tamTabla, colisiones, calcularDispersion);

	strcpy(d[pos].clave, clave);
	strcpy(d[pos].sinonimos, sinonimo);
	d[pos].ocupada = 1;

}

void imprimirC(tabla_cerrada d, int tamTabla) {
	int i;
	printf("\n ***TABLA CERRADA CUADRATICA \n");
	for (i = 0; i < tamTabla; i++) {
		printf("%4d- ", i);
		if (d[i].ocupada != 0) {
			printf("(%s)", d[i].clave);
			printf("\n");
		} else {
			printf("\n");
		}
	}
}

void imprimirBusquedaB(char*clave, tabla_cerrada dc, int n, int *colisiones) {
	int posicion;
	posicion = buscarPosicion(clave, dc, n, colisiones, dispersion);
	printf("Al buscar:%8s encuentro: %8s \n", clave, dc[posicion].clave);
}

void pruebaDispersionCerrada() {
	int n = 11;
	int cuenta = 6, colisiones = 0, busq = 7;
	char *clave[6] = { "ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN" };
	char *busco[7] = { "ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN", "CARLOS" };
	char *sinonimo[6] = { "7", "7", "6", "6", "7", "6" };
	tabla_cerrada dc = malloc(n * sizeof(entrada));

	inicializarC(dc, n);
	int i;
	for (i = 0; i < cuenta; i++) {
		insertarC(clave[i], sinonimo[i], dc, n, &colisiones, dispersion);
	}

	imprimirC(dc, n);
	printf("Numero total de colisiones: %d", colisiones);
	printf("\n");

	for (i = 0; i < busq; i++) {
		imprimirBusquedaB(busco[i], dc, n, &colisiones);
	}
	printf("\n");
	free(dc);
}

void pruebaDispersionACerradaTest(int nElementos, item sinonimos[]) {

	int tamVector = 38197;
	double ta = 0, tb = 0, t = 0;
	double sub = 0, ajus = 0, sobre = 0;
	int colisionesA = 0;
	tabla_cerrada dc = malloc(tamVector * sizeof(entrada));
	int i, j, k,z;
	inicializarC(dc, tamVector);

	printf("insertando %d elementos", nElementos);
	for (i = 0; i < nElementos; i++) {

		insertarC(sinonimos[i].clave, sinonimos[i].sinonimos, dc, tamVector,
				&colisionesA, dispersionA);
	}
	printf("Numero total de colisiones: %d\n", colisionesA);
	printf("Buscando...\n");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.9 ",
			"t(n)/n^0.999", "t(n)/n^1.1");
			
	for (z = 0; z < 3; z++){		
	for (j = 125; j <= 2000; j = j * 2) {
		ta = microsegundos();
		for (i = 0; i < j; i++) {
			buscarPosicion(sinonimos[i].clave, dc, tamVector, &colisionesA,
					dispersionA);
		}
		tb = microsegundos();
		t = (tb - ta);
		if (t < UMBRAL) {
			ta = microsegundos();
			for (k = 0; k < 1000; k++) {
				for (i = 0; i < j; i++){
				buscarPosicion(sinonimos[k].clave, dc, tamVector, &colisionesA,
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
	free(dc);
}

void pruebaDispersionBCerradaTest(int nElementos, item sinonimos[]) {
	int tamVector = 38197;
	int colisionesB = 0;
	double ta = 0, tb = 0, t = 0;
	double sub = 0, ajus = 0, sobre = 0;
	int i, j, k,z;
	tabla_cerrada dc = malloc(tamVector * sizeof(entrada));

	inicializarC(dc, tamVector);

	printf("insertando %d elementos", nElementos);
	for (i = 0; i < nElementos; i++) {
		insertarC(sinonimos[i].clave, sinonimos[i].sinonimos, dc, tamVector,
				&colisionesB, dispersionB);
	}
	printf("Numero total de colisiones: %d\n", colisionesB);
	printf("Buscando...\n");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.9 ",
			"t(n)/n^0.999", "t(n)/n^1.1");
			
   for (z = 0; z < 3; z++){
	for (j = 125; j <= 2000; j = j * 2) {
		ta = microsegundos();
		for (i = 0; i < j; i++) {
			buscarPosicion(sinonimos[i].clave, dc, tamVector, &colisionesB,
					dispersionB);
		}
		tb = microsegundos();
		t = (tb - ta);
		if (t < UMBRAL) {
			ta = microsegundos();
			for (k = 0; k < 1000; k++){
				for (i = 0; i < j; i++){
				buscarPosicion(sinonimos[k].clave, dc, tamVector, &colisionesB,
						dispersionB);
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
	free(dc);
}

void pruebaDispersionCerradaTest(int nElementos, item sinonimos[]) {
	printf("\n");
	printf("***Dispersion cerrada cuadratica con dispersion A \n");
	pruebaDispersionACerradaTest(nElementos, sinonimos);
	printf("\n");
	printf("***Dispersion cerrada cuadratica con dispersion B \n");
	pruebaDispersionBCerradaTest(nElementos, sinonimos);
	printf("\n");
}
