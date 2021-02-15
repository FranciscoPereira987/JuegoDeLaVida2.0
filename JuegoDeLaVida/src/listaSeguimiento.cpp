/*
 * listaSeguimiento.cpp
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#include <iostream>
#include <string>
#include "listaSeguimiento.h"
#include "nodoGenes.h"

using std::string;

ListaSeguimiento::ListaSeguimiento(){

	this->seguimientos = new Lista<NodoGen>;
}

ListaSeguimiento::ListaSeguimiento(string gen, unsigned int turno){



	NodoGen nuevoSeguimiento(gen, turno);
	this->seguimientos = new Lista<NodoGen>(nuevoSeguimiento);

}

void ListaSeguimiento::insertar(string gen, unsigned int turno){

	NodoGen nuevoSeguimiento(gen, turno);

	this->seguimientos->insertar(nuevoSeguimiento, 0);

}

bool ListaSeguimiento::estaVacia(){
	return (this->seguimientos->longitud() == 0);
}


bool ListaSeguimiento::colaVacia(){
	return this->seguimientos->obtenerCursor()->estaVacia();
}

void ListaSeguimiento::reiniciarCursor(){

	this->seguimientos->inicializarCursor();

}



bool ListaSeguimiento::buscarEnLalista(Lista<InformacionGenetica>* lista){

	return this->seguimientos->obtenerCursor()->buscarGen(lista);

}

void ListaSeguimiento::compararGenes(Lista<InformacionGenetica>* lista){

	if(!this->estaVacia()){
		bool pudoAvanzar = true;
		this->reiniciarCursor();

		while(pudoAvanzar){

			if((this->buscarEnLalista(lista))){
				this->agregarIntensidad(lista->obtenerCursor()->obtenerIntensidad());
			}

			pudoAvanzar = this->seguimientos->avanzarCursor();
		}
	}


}

void ListaSeguimiento::finalizarAcumulacion(){

	if(!this->estaVacia()){
		bool pudoAvanzar = true;
		this->reiniciarCursor();

		while(pudoAvanzar){

			this->acolarIntensidad();
			pudoAvanzar = this->seguimientos->avanzarCursor();

		}
	}
}

BMP* ListaSeguimiento::crearGrafico(unsigned int cantidadTurnos,
		unsigned int maximaAltura, int turnoInicial){

	BMP* grafico;

	grafico = new BMP;

	grafico->SetSize(1100, 1100);

	grafico->SetBitDepth(8);

	RGBApixel negro;
	negro.Red = 0;
	negro.Green = 0;
	negro.Blue = 0;
	negro.Alpha = 1;

	RGBApixel gris;

	gris.Red = 178;
	gris.Green = 186;
	gris.Blue = 187;
	gris.Alpha = 0;


	int posicionVariable;
	for(int turno = 0; turno < cantidadTurnos; turno++){
		posicionVariable = turno * (1000/ cantidadTurnos) + 50;
		char* numero = (char*) std::to_string(turno + turnoInicial).c_str();
		PrintString(*grafico,  numero,
				posicionVariable, grafico->TellHeight() - 45, 10, negro);
		DrawAALine(*grafico, posicionVariable, 4950, posicionVariable, 10, gris);
	}
	if(!maximaAltura){
		maximaAltura = 11;
	}
	cout << maximaAltura << endl;
	for(int intensidad = (maximaAltura/10); intensidad <= maximaAltura;
			intensidad += (maximaAltura/10)){
		posicionVariable = 1050 - intensidad * (1000 / maximaAltura);

		char* valor = (char*) std::to_string(intensidad).c_str();

		PrintString(*grafico, valor, 10, posicionVariable, 10, negro);

		DrawAALine(*grafico, 50, posicionVariable, 4950, posicionVariable, gris);
	}

	DrawAALine(*grafico,50, 10, 50, grafico->TellHeight() - 50, negro);
	DrawAALine(*grafico,50, grafico->TellHeight() - 50, grafico->TellWidth() - 50,
			grafico->TellHeight() - 50, negro);


	return grafico;
}



string ListaSeguimiento::obtenerGen(){
	return this->seguimientos->obtenerCursor()->obtenerGen();
}

bool ListaSeguimiento::buscarGen(string gen){

	this->reiniciarCursor();

	bool estaEnLaLista = false;

	if(!this->estaVacia()){
		string genActual = this->seguimientos->obtenerCursor()->obtenerGen();
		while((gen != genActual) && this->seguimientos->avanzarCursor()){
			genActual = this->seguimientos->obtenerCursor()->obtenerGen();
		}

		if(genActual == gen){
			estaEnLaLista = true;
		}
	}
	return estaEnLaLista;
}

void ListaSeguimiento::agregarIntensidad(unsigned int intensidad){
	this->seguimientos->obtenerCursor()->sumarIntensidad(intensidad);
}

void ListaSeguimiento::acolarIntensidad(){
	this->seguimientos->obtenerCursor()->agregarIntensidad();
}

unsigned int ListaSeguimiento::obtenerIntensidad(){
	return this->seguimientos->obtenerCursor()->obtenerIntensidad();
}

unsigned int ListaSeguimiento::obtenerTurno(){
	return this->seguimientos->obtenerCursor()->obtenerTurno();
}

void ListaSeguimiento::detenerSeguimiento(string gen){
	this->reiniciarCursor();


		string nombreDelGrafico = "seguimientos/gen-" + gen + "-";

	if(this->buscarGen(gen)){

		unsigned int longitudCola = this->seguimientos->obtenerCursor()\
				->obtenerLongitudCola();
		unsigned int maximaAltura = this->seguimientos->obtenerCursor()\
				->obtenerMaximaIntesidad();

		BMP *grafico = crearGrafico(longitudCola, maximaAltura,
				this->obtenerTurno());

		RGBApixel rojo;
			rojo.Red = 255;
			rojo.Green = 0;
			rojo.Blue = 0;
			rojo.Alpha = 1;


		unsigned int turnos = this->obtenerTurno();
		unsigned int turnoInicial = turnos;

		nombreDelGrafico += std::to_string(turnos) + "-";

		unsigned int pasoX = 1000 / longitudCola;
		unsigned int pendienteY = 1;
		if(maximaAltura){
			pendienteY = (1000) / maximaAltura;
		}

		unsigned int coordXanterior = 50;
		unsigned int coordYanterior = grafico->TellHeight() - 50 - \
				this->obtenerIntensidad()* pendienteY;




		while(!this->colaVacia()){
			int coordX = (turnos - turnoInicial + 1)*pasoX + 50;
			int coordY = grafico->TellHeight()- 50 - pendienteY * this->obtenerIntensidad();
			DrawAALine(*grafico, coordXanterior, coordYanterior, coordX, coordY, rojo);
			coordXanterior = coordX;
			coordYanterior = coordY;
			turnos ++;
		}

		nombreDelGrafico += std::to_string(turnos) + ".bmp";

		this->seguimientos->pop(NodoGen(gen, 0));


	grafico->WriteToFile(nombreDelGrafico.c_str());

	delete grafico;

	}
}

ListaSeguimiento::~ListaSeguimiento(){

	this->seguimientos->~Lista();

}
