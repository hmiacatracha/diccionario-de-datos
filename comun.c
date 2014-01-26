#include "comun.h"
/**


 * ALGORITMOS DE DISPERSION
 */

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL ) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

int dispersion(char *clave, int tamTabla) {
	int valor = clave[0];
	switch (valor) {
	case 'A':
		return 7;
	case 'O':
		return 7;
	case 'L':
		return 6;
	case 'R':
		return 6;
	case 'J':
		return 7;
	case 'I':
		return 6;
	}
	return 0;
}

int dispersionA(char *clave, int tamTabla) {
	int i, valor = clave[0];
	for (i = 1; i < strlen(clave); i++)
		valor += clave[i];
	return valor % tamTabla;
}

int dispersionB(char *clave, int tamTabla) {
	int i, valor = clave[0], n = MIN(8, strlen(clave));
	for (i = 1; i < n; i++)
		valor = (32 * valor + clave[i]) % tamTabla;
	return valor;
}

/**
 *  leer sinonimos
 */


int leer_sinonimos(item datos[]) {
	char c;
	int i, j;
	FILE *archivo;
	if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
		printf("Error al abrir ’sinonimos.txt’\n");
		return (EXIT_FAILURE);
	}

	for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
		if ((c = fgetc(archivo)) != '\t') {
			printf("Error al leer el tabulador\n");
			return (EXIT_FAILURE);
		}
		for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
			if (j < LONGITUD_SINONIMOS - 1)
				datos[i].sinonimos[j] = c;
		}
		datos[i].sinonimos[j] = '\0';
	}
	if (fclose(archivo) != 0) {
		printf("Error al cerrar el fichero\n");
		return (EXIT_FAILURE);
	}
	return (i);
}
