/*
 * interfaz.h
 *
 *  Created on: 6 Dec 2020
 *      Author: luca
 */

#ifndef INTERFAZ_H_
#define INTERFAZ_H_

#include <iostream>

#include "tablero.h"

class Juego{

private:


	int var;

	void DesarrolloDelJuego(Tablero* partida);

	Tablero* agregarCelulas(string path);

public:

	Juego();

	void pedirEleccion();

	void iniciarPartida(string path);


};



#endif /* INTERFAZ_H_ */
