#include "tablero.h"
#include "lista.h"

#include <fstream>


void obtenerDatos(std::string path){

	std::ifstream entrada;
	int filas, columnas;
	std::string auxiliar="";

	entrada.open(path);

	entrada >> auxiliar;

	if (auxiliar == "tablero"){
		entrada >> filas;
		entrada >> columnas;
	}
	else {
		throw std::string("Error de formato.");
	}

	Tablero* tablero = new Tablero(filas, columnas);

	if (! entrada.eof()){
		entrada >> auxiliar;
	}

	while (! entrada.eof()){
		int fila, columna;

		if (auxiliar == "celula"){
			entrada >> fila;
			entrada >> columna;
		}

		Lista<int> infoGen;
		entrada >> auxiliar;

		while (auxiliar == "gen"){
			int info[2];
			entrada >> info[0];
			entrada >> info[1];
			infoGen.push(info[1]);
			entrada >> auxiliar;
		}

		tablero->agregarCelula(fila, columna);//, infoGen);


	}

}
