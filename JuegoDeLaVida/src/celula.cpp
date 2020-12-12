/*
 * celula.cpp
 *
 *  Created on: Dec 3, 2020
 *      Author: shory
 */

#include "celula.h"


Celula::Celula(Lista<InformacionGenetica> genesPadre){

	estado = VIVA;

	cambioDeEstado = false;

	genes = new Genes(genesPadre);

}

Celula::Celula(Genes genesPadre){

	estado = MUERTA;

	cambioDeEstado = false;

	genes = new Genes(genesPadre, NOTRANSFERIDOS);

}

Celula::~Celula(){

	delete genes;

}


void Celula::sumarVecina(Genes progenitor){

	genes->agregarProgenitor(progenitor);
}

bool Celula::obtenerEstado(){

	return estado;
}

bool Celula::obtenerCambio(){

	return cambioDeEstado;
}


void Celula::decidirEstado(int nrTurno){

	aplicarReglas(nrTurno);
	resetearPuntaje();

}

Genes Celula::obtenerGenes(){

	if(!obtenerEstado()){
		throw string("CELULA MUERTA");
	}

	return *genes;

}

/*
 * Metodos privados
 */

void Celula::resetearPuntaje(){

	genes->resetearProgenitores();
}

void Celula::aplicarReglas(int nrTurno){
	int puntaje = genes->obtenerProgenitores();

    if(estado){
        estado = (puntaje == 3) || (puntaje == 2);
        cambioDeEstado = !estado;
    }
    else{
        if((estado = (puntaje == 3))){
        	nacer(nrTurno);
        }
        cambioDeEstado = estado;
    }
}

void Celula::nacer(int nrTurno){

	estado = VIVA;

	mezclarGenes(nrTurno);

}


void Celula::mezclarGenes(int nrTurno){

	genes->mezclarGenes(nrTurno);

}




