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

	/*Tablero partida(20, 80);

	partida.agregarCelula(10, 40);
	partida.agregarCelula(10, 41);
	partida.agregarCelula(11, 40);
	partida.agregarCelula(9, 40);
	partida.agregarCelula(9, 39);

	return partida;*/

	Tablero* partida = new Tablero(path);

	return partida;
}

void Juego::DesarrolloDelJuego(Tablero* partida){

	var = 1;

	do{
		partida->imprimirTablero();
		partida->actualizar();

		std::cout << std::endl << "Para continuar, ingrese:" << std::endl;
		std::cout << "(1) Siguiente turno." << std::endl;
		std::cout << "(2) Reiniciar el juego." << std::endl;
		std::cout << "(3) Terminar" << std::endl;

		this->pedirEleccion();

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





