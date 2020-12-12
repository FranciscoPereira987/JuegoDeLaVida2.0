/*
 * main.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */

#include "interfaz.h"

#include "lista.h"
#include "pila.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){
try{
	Juego partida;
	string path = "/home/francisco/TPALGOII/JuegoDeLaVida/prueba";

	partida.iniciarPartida(path);

	/*
	Lista<int> prueba;

	prueba.insertar(10);
	prueba.insertar(1);
	prueba.insertar(5);
	prueba.insertar(-2);
	prueba.insertar(11);

	prueba.imprimir();
	*/
}catch(string& excepcion){

	cout << excepcion << endl;

}

	return 0;
}


