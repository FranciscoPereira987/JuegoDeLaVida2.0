/*
 * interfaz.cpp
 *
 *  Created on: 6 Dec 2020
 *      Author: luca
 */

#include <iostream>
#include <string>
using std::string;

#include "interfaz.h"

#include "tablero.h"

Juego::Juego(){


	var = 2;
}

Tablero* Juego::agregarCelulas(string path){

	Tablero* partida = new Tablero(path);

	return partida;
}

void Juego::mostrarOpciones(){

	std::cout << std::endl << "Para continuar, ingrese:" << std::endl;
	std::cout << "(1) Siguiente turno." << std::endl;
	std::cout << "(2) Reiniciar el juego." << std::endl;
	std::cout << "(3) Terminar" << std::endl;
	std::cout << "(4) Seguimiento de genes" << std::endl;

	std::cin >> var;

}
void Juego::agregarSeguimiento(Tablero* partida){
	 string gen;
	 std::cout << "Ingrese el gen a seguir." << std::endl;
	 std::cin >> gen;
	 if(partida->genValido(gen)){
		 while(partida->buscarGen(gen)){
			 std::cout << "Ya se esta siguiendo al gen. ingrese otro" << std::endl;
			 std::cin >> gen;
	     }
	     partida->seguirGen(gen);
	 }else{
		 std::cout << "El gen ingresado no existe en el tablero." << std::endl;
	 }

}

void Juego::terminarSeguimiento(Tablero* partida){
	string gen;

	if(!partida->seguimientoVacio()){
		std::cout << "ingresar gen para terminar seguimiento" << std::endl;
		std::cin >> gen;

		bool estaElGen;
		do{
			if(!(estaElGen = partida->buscarGen(gen))){
				std::cout << "El gen no se esta siguiendo" << std::endl;
				std::cin >>gen;
			}
		}while(!estaElGen);

		if(estaElGen){
			partida->dejarDeSeguirGen(gen);
		}
	}else{
		std::cout << "No se esta siguiendo a ningun gen." << std::endl;
	}
}

void Juego::opcionesSeguimiento(Tablero* partida){

	char opcion;


	do{
		std::cout << "(1) Agregar seguimiento de un gen." << std::endl;
		std::cout << "(2) Terminar seguimiento de un gen." << std::endl;
		std::cout << "(3) Imprimir base genetica" << std::endl;
		std::cout << "(4) Volver" << std::endl;
		std::cin >> opcion;

		switch(opcion){
		case '1':
			this->agregarSeguimiento(partida);

			break;
		case '2':
			this->terminarSeguimiento(partida);
			break;
		case '3':
			partida->imprimirBaseGenetica();
			break;
		case '4':
			break;
		default:
			std::cout << "Opcion Incorrecta" << std::endl;
			break;
		}
	}while(opcion != '4');

}

void Juego::modificarSeguimiento(Tablero* partida){

	while(var == 4){
		this->opcionesSeguimiento(partida);
		this->mostrarOpciones();
	}

}

void Juego::DesarrolloDelJuego(Tablero* partida){

	var = 1;

	do{
		partida->imprimirTablero();


		this->mostrarOpciones();
		this->modificarSeguimiento(partida);

		partida->actualizar();

	}while(var == 1);

}




void Juego::iniciarPartida(string path){

	while(var == 2){
		Tablero* partida = agregarCelulas(path);
		this->DesarrolloDelJuego(partida);

		delete partida;
	}

	std::cout <<"-----  FIN DEL JUEGO -----" << std::endl;

}





