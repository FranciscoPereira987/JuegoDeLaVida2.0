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

	genes = new Lista<InformacionGenetica>[3];

	genes[0] = genesPadre;

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

	return &genes[0];

}

void Celula::agregarPadre(Lista<InformacionGenetica> nuevoPadre){

	if(!obtenerEstado() && puntaje <= 3){
		genes[puntaje-1] = nuevoPadre;
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
	while(genes[0].longitud() ||
			genes[1].longitud() ||
			genes[2].longitud()){
		maximo = devolverMaximo();
		transferir(maximo, cargaFinal, nrTurno);
	}

	destruirGenes();
	genes = new Lista<InformacionGenetica>[3];
	genes[0] = *cargaFinal;

}

void Celula::transferir(InformacionGenetica maximo,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	int contador = 0, indices[3] = {0, 0, 0};
	for(int i = 0; i < 3; i++){
		if(genes[i].longitud() &&
				genes[i].operator [](PRIMERA) == maximo){
			indices[i] = 1;
			contador++;
		}
	}
	switch(contador){
	case 1:{
		int i = 0;
		while(!(indices[i])){
			i++;
		}
		transferenciaSimple(i, cargaFinal, nrTurno);
		break;
	}
	case 2:{
		int primero = -1, segundo = 0, j = 0;
		while(!segundo){
			if(indices[j]){
				if(primero == -1){
					primero = j;
				}
				else{
					segundo = j;
				}
			}
			j++;
		}
		transferenciaDoble(primero, segundo, cargaFinal, nrTurno);
		break;
	}
	case 3:
		transferenciaTriple(cargaFinal, nrTurno);
		break;
	default: throw string("ERROR EN TRANSFERENCIA");
	}


}

InformacionGenetica Celula::devolverMaximo(){

	InformacionGenetica maximo;
	for(int i = 0; i < 3; i++){
		if(genes[i].longitud() &&
				genes[i].operator [](PRIMERA) > maximo){
			maximo = genes[i].operator [](PRIMERA);
		}
	}

	return maximo;
}


void Celula::destruirGenes(){

	for(int i = 0; i < 3; i++){
		genes[i].~Lista();
	}
	delete [] genes;
	genes = NULL;
}

void Celula::transferenciaSimple(int indice,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	InformacionGenetica nuevo(genes[indice][0].devolverBits(),0);
	genes[indice].remove(PRIMERA);
	cargaFinal->push(nuevo);

}

void Celula::transferenciaDoble(int primero, int segundo,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	InformacionGenetica gen1 = genes[primero][PRIMERA],
			gen2 = genes[segundo][PRIMERA];

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
	genes[primero].remove(PRIMERA);
	genes[segundo].remove(PRIMERA);
	cargaFinal->push(nuevo);

}

void Celula::transferenciaTriple(Lista<InformacionGenetica>* cargaFinal,
		int nrTurno){

	InformacionGenetica gen1 = genes[0][PRIMERA],
			gen2 = genes[1][PRIMERA],
			gen3 = genes[2][PRIMERA];

	int intensidad;
	if(gen1.obtenerIntensidad() || gen2.obtenerIntensidad() ||\
			gen3.obtenerIntensidad()){
		intensidad = 0;
		for (int i = 0; i < 3; i++){
			if(genes[i][0].obtenerIntensidad() > intensidad){
				intensidad = genes[i][0].obtenerIntensidad();
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
		genes[i].remove(0);
	}

}



