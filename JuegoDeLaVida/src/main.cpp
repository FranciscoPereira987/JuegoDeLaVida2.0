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

int main(){

	Juego partida;
	string path = "/home/francisco/TPALGOII/JuegoDeLaVida/prueba";

	partida.iniciarPartida(path);

	return 0;
}


