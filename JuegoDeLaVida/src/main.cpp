/*
 * main.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */

#include "tablero.h"

#include "lista.h"

#include <iostream>
using std::cin;

int main(){

	/*
	int var;
	Tablero prueba(100000, 100000);

	prueba.agregarCelula(10, 40);
	prueba.agregarCelula(10, 41);
	prueba.agregarCelula(11, 40);
	prueba.agregarCelula(9, 40);
	prueba.agregarCelula(9, 39);

	do{

		prueba.actualizar();
		std::cout << "Listo!" << std::endl;
		cin >> var;
	}while(var == 1);
	*/

	Lista<int> prueba(60);

	prueba.push(10);
	prueba.insertar(45, 1);
	prueba.insertar(70, 3);
	prueba.append(99);

	prueba.remove(0);
	prueba.remove(2);



	for(int i = 0; i < prueba.longitud(); i++){
		cout << prueba[i] << "-->";
	}
	std::cout << std::endl;



	prueba.imprimir();


	return 0;
}


