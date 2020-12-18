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
		string path = "celulas/prueba";

		partida.iniciarPartida(path);



	}catch(string& excepcion){

		cout << excepcion << endl;

	}

	return 0;
}


