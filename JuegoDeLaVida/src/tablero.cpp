/*
 * tablero.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */


#include "tablero.h"
#include "lista.h"
#include "informacionGenetica.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;


Tablero::Tablero(string path){

	obtenerDatos(path);
}

Tablero::Tablero(int cantFilas, int cantColumnas){

	inicializarTablero(cantFilas, cantColumnas);
}


Tablero::~Tablero(){

	if(juego){
		limpiarTablero();
		this->baseGenetica->imprimir();
		delete this->baseGenetica;
	}

}

void Tablero::agregarCelula(int fila, int columna\
		, Lista<InformacionGenetica*> genes){

	if(posicionValida(fila, columna)){
		juego[fila][columna] = new Celula(genes);

	}
	else{
		throw string("Posicion invalida");
	}

}

void Tablero::imprimirTablero(){
	poblacion = 0;
	for(int fila = 0; fila < filas; fila++){
		for(int columna = 0; columna < columnas; columna++){
			if(juego[fila][columna]){
				cout << "*";
				poblacion++;
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}
	imprimirInfoActual();

}

void Tablero::imprimirInfoActual(){
	cout << "Generacion: " << turno
		 << endl
		 << "poblacion: "<< poblacion
		 << " | "
		 << "Nacimientos: " << nacimientos
	 	 << " | "
		 << "Muertes: " << muertes
		 << endl;
	if(turno > 0){

		cout << "Promedio de nacimientos: " << calcularPromedio(totalNacimientos, turno)
			 << " | "
			 <<"Promedio de muertes: " << calcularPromedio(totalMuertes, turno)
			 << endl;
		estadoDelJuego();
	}


}

void Tablero::estadoDelJuego(){
	if ((nacimientos == 0) && (muertes == 0)){
		std::cout << "estado del juego: congelado" << std::endl;
	}else{
		std::cout << "estado del juego: activo" << std::endl;
	}
}


void Tablero::actualizar(){
	envejecerBaseGenetica();
	for(int fila = 0; fila < filas; fila++){
		for(int columna = 0; columna < columnas; columna++){
			if(juego[fila][columna] &&
					!(celulaMuerta(fila, columna))){
				Genes actuales(*juego[fila][columna]->obtenerGenes().obtenerGenes());
				contarAdyacentes(fila, columna, actuales);
			}
		}
	}
	definirTablero();
}

/*
 * Metodos privados
 */

void Tablero::envejecerBaseGenetica(){
	for(int i=0; i < baseGenetica->longitud(); i++ ){
		(*baseGenetica)[i]->envejecer();
	}
}


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


void Tablero::contarAdyacentes(int nrFila, int nrColumna\
		,Genes genes){
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
	    	contarVecina(filaActual, columnaActual, genes);
	    }
	}
}

void Tablero::contarVecina(int nrFila, int nrColumna\
		, Genes genes){

	/*
	 * declaro una referencia al puntero
	 */
	Celula*& actual = juego[nrFila][nrColumna];

	if(!actual){
		actual = new Celula(genes);
	}
	else{
		actual->sumarVecina(genes);

	}

}

void Tablero::definirTablero(){

	nacimientos = 0;
	muertes = 0;


	for(int fila = 0; fila < filas; fila++){
		for(int columna = 0; columna < columnas; columna++){
			if(juego[fila][columna]){
				juego[fila][columna]->decidirEstado(this->turno,
						this->baseGenetica);
				sumarSuceso(juego[fila][columna]->obtenerEstado(),
						juego[fila][columna]->obtenerCambio());
			}
			/*
			 * Si la celula queda muerta, libero la memoria
			 */
			if(celulaMuerta(fila, columna)){
				limpiarCelula(fila, columna);
			}
		}
	}

	turno++;

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

void Tablero::sumarSuceso(bool estadoActual, bool cambio){
	if((estadoActual) && (cambio)){
		nacimientos++;
		totalNacimientos++;
	}else if(!(estadoActual) && (cambio)){
		muertes++;
		totalMuertes++;
	}

}

float Tablero::calcularPromedio(unsigned int total, unsigned int turno){

	float promedio;
	promedio = (float)total/(float)turno;

	return promedio;
}

bool Tablero::celulaMuerta(int nrFila, int nrColumna){

	return (juego[nrFila][nrColumna] &&
			!(juego[nrFila][nrColumna]->obtenerEstado()));
}

void Tablero::obtenerDatos(std::string path){

	std::ifstream entrada;
	int filas, columnas;
	std::string auxiliar="";

	entrada.open(path.c_str());

	entrada >> auxiliar;

	if (auxiliar == "tablero"){
		entrada >> filas;
		entrada >> columnas;
	}
	else {
		throw std::string("Error de formato.");
	}

	this->inicializarTablero(filas, columnas);

	if (! entrada.eof()){
		entrada >> auxiliar;
	}

	while (! entrada.eof()){
		int fila, columna;

		if (auxiliar == "celula"){
			entrada >> fila;
			entrada >> columna;
		}

		string gen;
		int intensidad;
		Lista<InformacionGenetica*> genes;
		entrada >> auxiliar;

		while (auxiliar == "gen"){

			entrada >> gen;
			entrada >> intensidad;
			entrada >> auxiliar;
			InformacionGenetica genActual(gen, intensidad);
			if(!this->baseGenetica->estaEnLista(&genActual)){
				this->baseGenetica->push(&genActual);
			}
			genes.insertar(&genActual);
		}
		entrada >> auxiliar;

		this->agregarCelula(fila-1, columna-1, genes);
		//genes.~Lista();

		}

	entrada.close();
}

void Tablero::inicializarTablero(int cantFilas, int cantColumnas){

	if(!((cantFilas > 0) && (cantColumnas > 0))){
		throw string(
					"La cantidad de filas y \
					columnas debe ser mayor a 0"
					);
	}

	filas = cantFilas;
	columnas = cantColumnas;
	juego = new Celula**[filas];
	this->baseGenetica = new Lista<InformacionGenetica*>;
	for(int fila = 0; fila < filas; fila++){
		juego[fila] = new Celula*[columnas];
		inicializarFila(juego[fila]);
	}

	muertes = 0;
	nacimientos = 0;
	totalMuertes = 0;
	totalNacimientos = 0;
	turno = 1;
}


