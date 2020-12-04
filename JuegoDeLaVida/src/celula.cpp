/*
 * celula.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */

#include "celula.h"

Celula::Celula(){

	estado = MUERTA;

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
    }
    else{
        estado = (puntaje == 3);
    }

}
