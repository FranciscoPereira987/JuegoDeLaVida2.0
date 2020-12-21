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

	/*
	 * post: desarrolla los turnos del juego
	 */
	void DesarrolloDelJuego(Tablero* partida);

	/*
	 * post: agrega las celulas vivas iniciales al tablero
	 */
	Tablero* agregarCelulas(string path);

	/*
	 * post: muestra las opciones del juego
	 */
	void mostrarOpciones();

	/*
	 * post: agrega o quita un gen de la lista de seguimiento
	 */
	void opcionesSeguimiento(Tablero* partida);

	/*
	 * pre: el gen debe existir en el tablero
	 * post: agrega un gen a la lista de seguimiento
	 */
	void agregarSeguimiento(Tablero* partida);

	/*
	 * pre: el gen debe estar en la lista de seguimiento
	 * post: quita un gen de la lista de seguimiento
	 */
	void terminarSeguimiento(Tablero* partida);

	/*
	 * pre: el usuario debe haber elegido la opcion 4
	 * post: cambia la lista de seguimiento de genes
	 */
	void modificarSeguimiento(Tablero* partida);

public:

	/*
	 * post: el juego esta listo para iniciar
	 */
	Juego();

	/*
	 * pre: path debe ser una direccion a un archivo valido
	 * post: crea una partida del juego de la vida
	 */
	void iniciarPartida(string path);
};

#endif /* INTERFAZ_H_ */
