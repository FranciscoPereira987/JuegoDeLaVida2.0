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
		/*
		Juego partida;
		string path = "celulas/prueba";

		partida.iniciarPartida(path);
		*/
		Lista<int> nuevaLista(0);

		nuevaLista.append(2);

		nuevaLista[0] = 1;

		nuevaLista.imprimir();



	}catch(string& excepcion){

		cout << excepcion << endl;

	}

	return 0;
}


