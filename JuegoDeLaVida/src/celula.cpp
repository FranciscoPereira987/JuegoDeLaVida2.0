/*
 * celula.cpp
 *
 *  Created on: Dec 3, 2020
 *      Author: shory
 */

#include "celula.h"


Celula::Celula(){

	estado = MUERTA;

	cambioDeEstado = false;

	puntaje = 0;
}

void Celula::nacer(){

	estado = VIVA;

}


void Celula::sumarVecina(){

	puntaje++;
}

bool Celula::obtenerEstado(){

	return estado;
}

bool Celula::obtenerCambio(){

	return cambioDeEstado;
}


void Celula::decidirEstado(){

	aplicarReglas();
	resetearPuntaje();

}

/*
 * Metodos privados
 */

void Celula::resetearPuntaje(){

	puntaje = 0;
}

void Celula::aplicarReglas(){

    if(estado){
        estado = (puntaje == 3) || (puntaje == 2);
        cambioDeEstado = !estado;
    }
    else{
        estado = (puntaje == 3);
        cambioDeEstado = estado;
    }
}




