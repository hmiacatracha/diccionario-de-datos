#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dispersionAbierta.h"
#include "dispersionCerrada.h"
/**
 *  FECHA:10/NOV/2013
	PRACTICA 3: TABLAS DE DISPERSION
	GRUPO: 2.2.1
	HORARIO: MIERCOLES 8:30-10:30
 */

int main(void) {

	int n = 19069;
	int cuenta;
	item sinonimos[n];
	cuenta = leer_sinonimos(sinonimos);

	pruebaDispersionAbierta();
	pruebaDispersionCerrada();
	pruebaDispersionAbiertaTest(cuenta, sinonimos);
	pruebaDispersionCerradaTest(cuenta, sinonimos);
	return 0;
}
