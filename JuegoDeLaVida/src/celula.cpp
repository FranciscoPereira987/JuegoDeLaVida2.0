/*
 * celula.cpp
 *
 *  Created on: Dec 3, 2020
 *      Author: shory
 */

#include "celula.h"


Celula::Celula(Lista<InformacionGenetica> genesPadre){

	estado = MUERTA;

	cambioDeEstado = false;

	puntaje = 1;

	genes = new Lista<InformacionGenetica>*[3];

	genes[0] = new Lista<InformacionGenetica>(genesPadre);
	genes[1] = genes[2] = NULL;

}

Celula::~Celula(){

	if(genes){
		destruirGenes();
	}

}

void Celula::nacer(){

	estado = VIVA;
	puntaje = 0;
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


void Celula::decidirEstado(int nrTurno){

	aplicarReglas(nrTurno);
	resetearPuntaje();

}

Lista<InformacionGenetica>* Celula::obtenerGenes(){

	if(!obtenerEstado()){
		throw string("CELULA MUERTA");
	}

	return genes[0];

}

void Celula::agregarPadre(Lista<InformacionGenetica> nuevoPadre){

	if(!obtenerEstado() && puntaje <= 3){
		genes[puntaje-1] = new Lista<InformacionGenetica>(nuevoPadre);
	}

}

/*
 * Metodos privados
 */

void Celula::resetearPuntaje(){

	puntaje = 0;
}

void Celula::aplicarReglas(int nrTurno){

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

	if(puntaje == 1){
		/*
		 * Simplemente dejo los
		 * genes que habia
		 */
		puntaje = 0;
	}
	else{
		/*
		 * Hago la mezcla de genes
		 * aca debe haber 3 padres
		 */
		mezclarGenes(nrTurno);
	}

}


void Celula::mezclarGenes(int nrTurno){

	Lista<InformacionGenetica>* cargaFinal = new Lista<InformacionGenetica>;
	InformacionGenetica maximo;
	while(genes[0]->longitud() &&
			genes[1]->longitud() &&
			genes[2]->longitud()){
		maximo = devolverMaximo();
		transferir(maximo, cargaFinal, nrTurno);
	}

	destruirGenes();
	genes = new Lista<InformacionGenetica>*[3];
	genes[0] = cargaFinal;
	genes[1] = genes[2] = NULL;
}

void Celula::transferir(InformacionGenetica minimo,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	InformacionGenetica primero = genes[0][0][0],
				segundo = genes[1][0][0],
				tercero = genes[2][0][0];

	if(primero == minimo && segundo == minimo && tercero == minimo){
		transferenciaTriple(cargaFinal, nrTurno);
	}
	else if(primero == minimo){
		if (segundo == minimo){
			transferenciaDoble(0,1,cargaFinal, nrTurno);
		}
		else if(tercero == minimo){
			transferenciaDoble(0,2,cargaFinal, nrTurno);
		}
		else{
			transferenciaSimple(0,cargaFinal, nrTurno);
		}
	}
	else if(segundo == minimo){
		if(tercero == minimo){
			transferenciaDoble(1,2,cargaFinal, nrTurno);
		}
		else{
			transferenciaSimple(1, cargaFinal, nrTurno);
		}
	}
	else{
		transferenciaSimple(2, cargaFinal, nrTurno);
	}
}

InformacionGenetica Celula::devolverMaximo(){

	InformacionGenetica primero = genes[0][0][0],
			segundo = genes[1][0][0],
			tercero = genes[2][0][0];

	InformacionGenetica maximo;
	if(primero < segundo){
		if(segundo < tercero){
			maximo = tercero;
		}
		else{
			maximo = segundo;
		}
	}
	else if(primero < tercero){
		maximo = tercero;
	}
	else{
		maximo = primero;
	}

	return maximo;
}


void Celula::destruirGenes(){

	for(int i = 0; i < 3; i++){
		Lista<InformacionGenetica>* actual = genes[i];
		if(actual){
			genes[i]->~Lista();
		}
	}
	delete [] genes;
	genes = NULL;
}

void Celula::transferenciaSimple(int indice,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	InformacionGenetica nuevo(genes[indice][0][0].devolverBits(),0);
	genes[indice][0].remove(0);
	cargaFinal->push(nuevo);

}

void Celula::transferenciaDoble(int primero, int segundo,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	InformacionGenetica gen1 = genes[primero][0][0],
			gen2 = genes[segundo][0][0];

	int intensidad;

	if(gen1.obtenerIntensidad() && gen2.obtenerIntensidad()){
		intensidad = (gen1.obtenerIntensidad() + gen2.obtenerIntensidad());
		intensidad /= 2;
	}
	else{
		if(gen1.obtenerIntensidad()){
			intensidad = gen2.obtenerIntensidad();
		}
		else if(gen2.obtenerIntensidad()){
			intensidad = gen2.obtenerIntensidad();
		}
		else{
			intensidad = (gen1.obtenerEdad()/(100*nrTurno));
			intensidad++;
		}
	}
	InformacionGenetica nuevo(gen1.devolverBits(), intensidad);
	genes[primero][0].remove(0);
	genes[segundo][0].remove(0);
	cargaFinal->push(nuevo);

}

void Celula::transferenciaTriple(Lista<InformacionGenetica>* cargaFinal,
		int nrTurno){

	InformacionGenetica gen1 = genes[0][0][0],
			gen2 = genes[1][0][0],
			gen3 = genes[2][0][0];

	int intensidad;
	if(gen1.obtenerIntensidad() || gen2.obtenerIntensidad() ||\
			gen3.obtenerIntensidad()){
		intensidad = 0;
		for (int i = 0; i < 3; i++){
			if(genes[i][0][0].obtenerIntensidad() > intensidad){
				intensidad = genes[i][0][0].obtenerIntensidad();
			}
		}
	}
	else{
		intensidad = gen1.obtenerEdad() / (100 * nrTurno);
		intensidad++;
	}

	InformacionGenetica nuevo(gen1.devolverBits(), intensidad);
	cargaFinal->push(nuevo);
	for (int i = 0; i < 3; i++){
		genes[i][0].remove(0);
	}

}



