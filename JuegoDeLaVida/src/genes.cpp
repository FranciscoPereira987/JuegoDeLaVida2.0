/*
 * genes.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: francisco
 */
#include "genes.h"


Genes::Genes(Lista<InformacionGenetica> genes){

	transferidos = TRANSFERIDOS;


	cargaGenetica = new Lista<InformacionGenetica>;
	*cargaGenetica = genes;
	progenitores = 0;

}

Genes::Genes(Genes& genesPadre, bool listos){

	transferidos = listos;
	if(transferidos){
		cargaGenetica = new Lista<InformacionGenetica>;
		*cargaGenetica = *(genesPadre.obtenerGenes());
	}
	else{
		cargaGenetica = new Lista<InformacionGenetica>[3];
		cargaGenetica[0] = *(genesPadre.obtenerGenes());
	}
	progenitores = 1;

}

Genes::~Genes(){

	if(!transferidos){
		reacomodarCargaGenetica();
	}
	else{
		cargaGenetica->~Lista();
		delete cargaGenetica;
	}
	cargaGenetica = NULL;

}

void Genes::agregarProgenitor(Genes progenitor){

	if(!transferidos && progenitores < 3){
		cargaGenetica[progenitores] = *(progenitor.obtenerGenes());
	}
	progenitores++;

}

void Genes::envejecerGenes(){

	this->cargaGenetica->inicializarCursor();
	while(this->cargaGenetica->avanzarCursor()){
		this->cargaGenetica->obtenerCursor()->envejecer();
	}

}

int Genes::obtenerProgenitores(){

	return progenitores;
}

void Genes::resetearProgenitores(){

	progenitores = 0;
}

Lista<InformacionGenetica>* Genes::obtenerGenes(){

	if(!transferidos){
		throw string("GENES NO TRANSFERIDOS");
	}

	return cargaGenetica;
}

void Genes::mezclarGenes(int nrTurno, Lista<InformacionGenetica>* baseGenetica){

	Lista<InformacionGenetica>* cargaFinal = new Lista<InformacionGenetica>;
	Pila<InformacionGenetica>* genesACombinar = new Pila<InformacionGenetica>;
	InformacionGenetica maximo;
	while(cargaGenetica[0].longitud() ||
			cargaGenetica[1].longitud() ||
			cargaGenetica[2].longitud()){
		maximo = devolverMaximo();
		transferir(maximo, cargaFinal, genesACombinar, nrTurno);
	}
	if(!genesACombinar->vacia()){
		InformacionGenetica genMutado = combinarGenes(genesACombinar, nrTurno);
		revisarGen(genMutado, cargaFinal, baseGenetica);
	}
	/*
	 * Libero la memoria de genes
	 * para combinar
	 */
	delete genesACombinar;
	/*
	 * Paso a finalizar la transferencia
	 */
	finalizarTransferencia(cargaFinal);
}


/*
 * Metodos privados
 */

InformacionGenetica Genes::devolverMaximo(){

	InformacionGenetica maximo;
	for(int i = 0; i < 3; i++){
		if(cargaGenetica[i].longitud() &&
				cargaGenetica[i][PRIMERA] > maximo){
			maximo = cargaGenetica[i][PRIMERA];
		}
	}

	return maximo;
}

void Genes::finalizarTransferencia(Lista<InformacionGenetica>* cargaFinal){

	reacomodarCargaGenetica();

	cargaGenetica = cargaFinal;
	transferidos = TRANSFERIDOS;


}

void Genes::reacomodarCargaGenetica(){

	for(int i = 0; i < 3; i++){
		cargaGenetica[i].~Lista();
	}

	delete [] cargaGenetica;

	cargaGenetica = NULL;

}

void Genes::transferir(InformacionGenetica maximo,
		Lista<InformacionGenetica>* cargaFinal,
		Pila<InformacionGenetica>* genesACombinar,
		int nrTurno){

	int contador = 0, indices[3] = {0, 0, 0};
	for(int i = 0; i < 3; i++){
		if(cargaGenetica[i].longitud() &&
				cargaGenetica[i][PRIMERA] == maximo){
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
		transferenciaSimple(i, genesACombinar, nrTurno);
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
		transferenciaDoble(primero, segundo, genesACombinar, cargaFinal, nrTurno);
		break;
	}
	case 3:
		transferenciaTriple(cargaFinal, genesACombinar, nrTurno);
		break;
	default: throw string("ERROR EN TRANSFERENCIA");
	}

}

void Genes::transferenciaSimple(int indice,
		Pila<InformacionGenetica>* genesACombinar,
		int nrTurno){

	InformacionGenetica nuevo(cargaGenetica[indice][0].devolverBits(),0);
	cargaGenetica[indice].remove(PRIMERA);
	genesACombinar->apilar(nuevo);

}

void Genes::transferenciaDoble(int primero, int segundo,
		Pila<InformacionGenetica>* genesACombinar,
		Lista<InformacionGenetica>* cargaFinal, int nrTurno){

	InformacionGenetica gen1 = cargaGenetica[primero][PRIMERA],
			gen2 = cargaGenetica[segundo][PRIMERA];

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
	if(intensidad){
		cargaFinal->push(nuevo);
	}
	else{
		genesACombinar->apilar(nuevo);
	}
	cargaGenetica[primero].remove(PRIMERA);
	cargaGenetica[segundo].remove(PRIMERA);


}

void Genes::transferenciaTriple(Lista<InformacionGenetica>* cargaFinal,
		Pila<InformacionGenetica>* genesACombinar,
		int nrTurno){

	InformacionGenetica gen1 = cargaGenetica[0][PRIMERA],
			gen2 = cargaGenetica[1][PRIMERA],
			gen3 = cargaGenetica[2][PRIMERA];

	int intensidad;
	if(gen1.obtenerIntensidad() || gen2.obtenerIntensidad() ||\
			gen3.obtenerIntensidad()){
		intensidad = 0;
		for (int i = 0; i < 3; i++){
			if(cargaGenetica[i][0].obtenerIntensidad() > intensidad){
				intensidad = cargaGenetica[i][0].obtenerIntensidad();
			}
		}
	}
	else{
		intensidad = gen1.obtenerEdad() / (100 * nrTurno);
		intensidad++;
	}

	InformacionGenetica nuevo(gen1.devolverBits(), intensidad);
	if(intensidad){
		cargaFinal->push(nuevo);
	}
	else{
		genesACombinar->apilar(nuevo);
	}
	cargaFinal->push(nuevo);
	for (int i = 0; i < 3; i++){
		cargaGenetica[i].remove(0);
	}

}

InformacionGenetica Genes::combinarGenes(Pila<InformacionGenetica>* genesACombinar,
		int nrTurno){

	InformacionGenetica genFinal = genesACombinar->pop();
	while(!genesACombinar->vacia()){
		InformacionGenetica siguiente = genesACombinar->pop();
		if(!genFinal.esMasJoven(&siguiente)){
			genFinal.cambiarEdad(siguiente.obtenerEdad());
		}
		genFinal.combinarCon(&siguiente);
	}
	int intensidadFinal = (genFinal.obtenerEdad()/(100* nrTurno)) + 1;
	genFinal.cambiarIntensidad(intensidadFinal);


	return genFinal;
}

void Genes::revisarGen(InformacionGenetica genARevisar,
		Lista<InformacionGenetica>* cargaFinal,
		Lista<InformacionGenetica>* baseGenetica){

	if(baseGenetica->estaEnLista(genARevisar)){
		if(!cargaFinal->estaEnLista(genARevisar)){
			/*
			 * Si el gen esta en la base pero no en la
			 * carga final, entonces le cambio su edad
			 * por la correcta y lo inserto en la carga
			 */
			int edad = baseGenetica->obtenerCursor()->obtenerEdad();
			genARevisar.cambiarEdad(edad);
			cargaFinal->insertar(genARevisar);
		}

	}
	else{
		/*
		 * Si el gen no esta en la base
		 * lo agrego a la base y a la cargaFinal
		 */
		baseGenetica->push(genARevisar);
		cargaFinal->insertar(genARevisar);
	}

}
