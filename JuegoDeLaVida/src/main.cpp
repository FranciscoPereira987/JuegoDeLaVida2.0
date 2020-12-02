/*
 * main.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */

#include "tablero.h"

#include <iostream>
using std::cin;

int main(){

	int var;
	Tablero prueba(20, 80);

	prueba.agregarCelula(10, 40);
	prueba.agregarCelula(10, 41);
	prueba.agregarCelula(11, 40);
	prueba.agregarCelula(9, 40);
	prueba.agregarCelula(9, 39);

	do{
		prueba.imprimirTablero();
		prueba.actualizar();
		cin >> var;
	}while(var == 1);


	return 0;
}


