/*
 * interfaz.cpp
 *
 *  Created on: 6 Dec 2020
 *      Author: luca
 */

#include <iostream>

#include "interfaz.h"

Juego::Juego(){


	var = 2;
}

Tablero* Juego::agregarCelulas(string path){

	Tablero* partida = new Tablero(path);

	return partida;
}

void Juego::DesarrolloDelJuego(Tablero* partida){

	var = 1;

	do{
		partida->imprimirTablero();


		std::cout << std::endl << "Para continuar, ingrese:" << std::endl;
		std::cout << "(1) Siguiente turno." << std::endl;
		std::cout << "(2) Reiniciar el juego." << std::endl;
		std::cout << "(3) Menu de segumineto de genes" << std::endl;
		std::cout << "(4) Terminar" << std::endl;

		this->pedirEleccion();
		partida->actualizar();

	}while(var == 1);

}

void Juego::pedirEleccion(){

	std::cin >> var;

}

void Juego::iniciarPartida(string path){

	while(var == 2){
		Tablero* partida = agregarCelulas(path);
		this->DesarrolloDelJuego(partida);

		delete partida;
	}

	std::cout <<"-----  FIN DEL JUEGO -----" << std::endl;

}





