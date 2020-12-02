/*
 * tablero.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */


#include "tablero.h"
#include <iostream>
using std::cout;
using std::endl;

Tablero::Tablero(int cantFilas, int cantColumnas){

	if(!((cantFilas > 0) && (cantColumnas > 0))){
		throw string(
					"La cantidad de filas y \
					columnas debe ser mayor a 0"
					);
	}

	filas = cantFilas;
	columnas = cantColumnas;
	juego = new Celula**[filas];

	for(int fila = 0; fila < filas; fila++){
		juego[fila] = new Celula*[columnas];
		inicializarFila(juego[fila]);
	}

}

Tablero::~Tablero(){

	if(juego){
		limpiarTablero();
	}

}

void Tablero::agregarCelula(int fila, int columna){

	if(posicionValida(fila, columna)){
		juego[fila][columna] = new Celula;
		juego[fila][columna]->nacer();
	}
	else{
		throw string("Posicion invalida");
	}

}

void Tablero::imprimirTablero(){

	for(int fila = 0; fila < filas; fila++){
		for(int columna = 0; columna < columnas; columna++){
			if(juego[fila][columna]){
				cout << "*";
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}

}

void Tablero::actualizar(){

	for(int fila = 0; fila < filas; fila++){
		for(int columna = 0; columna < columnas; columna++){
			if(juego[fila][columna] &&
					!(celulaMuerta(fila, columna))){
				contarAdyacentes(fila, columna);
			}
		}
	}
	definirTablero();
}

/*
 * Metodos privados
 */

void Tablero::limpiarCelula(int fila, int columna){

	delete juego[fila][columna];
	juego[fila][columna] = NULL;

}

void Tablero::limpiarFila(int fila){
	Celula** filaCelulas = juego[fila];

	for(int columna = 0; columna < columnas; columna++){
		/*
		 * Si hay una celula en esa posicion
		 * libero la memoria que esta ocupando
		 */
		if(filaCelulas[columna]){
			limpiarCelula(fila, columna);
		}
	}

	delete [] filaCelulas;
}

void Tablero::limpiarTablero(){

	for(int fila = 0; fila < filas; fila++){
		/*
		 * Libero la memoria de los punteros a punteros a Celulas
		 */
		limpiarFila(fila);
	}
	/*
	 * Libero la memoria de punteros a punteros a punteros a Celulas
	 */
	delete [] juego;

}

void Tablero::contarAdyacentes(int nrFila, int nrColumna){
	int filaActual, columnaActual;
	/*Son las posiciones relativas de las celulas adyacentes*/
	int movimientos[][2] = {
	      {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
	      {1, 0}, {1, -1}, {0, -1}, {-1, -1}
	    };
	for(int i = 0; i < 8; i++){
		filaActual = nrFila + movimientos[i][0];
	    columnaActual = nrColumna + movimientos[i][1];
	    /*Solamente actualizo el valor de la celda si la celda esta en
	     * el tablero
	     */
	    if(posicionValida(filaActual, columnaActual)){
	    	contarVecina(filaActual, columnaActual);
	    }
	}
}

void Tablero::contarVecina(int nrFila, int nrColumna){

	/*
	 * declaro una referencia al puntero
	 */
	Celula*& actual = juego[nrFila][nrColumna];

	if(!actual){
		actual = new Celula;
	}

	actual->sumarVecina();

}

void Tablero::definirTablero(){

	for(int fila = 0; fila < filas; fila++){
		for(int columna = 0; columna < columnas; columna++){
			if(juego[fila][columna]){
				juego[fila][columna]->decidirEstado();
			}
			/*
			 * Si la celula queda muerta, libero la memoria
			 */
			if(celulaMuerta(fila, columna)){

				limpiarCelula(fila, columna);
			}
		}
	}

}

bool Tablero::posicionValida(int nrFila, int nrColumna){

	bool filaBien = ((0 <= nrFila) && (nrFila < filas)),
		 columnaBien = ((0 <= nrColumna) && (nrColumna < columnas));

	return (filaBien && columnaBien);


}

void Tablero::inicializarFila(Celula**& fila){

	for(int columna = 0; columna < columnas; columna++){
		fila[columna] = NULL;
	}

}

bool Tablero::celulaMuerta(int nrFila, int nrColumna){

	return (juego[nrFila][nrColumna] &&
			!(juego[nrFila][nrColumna]->obtenerEstado()));
}
