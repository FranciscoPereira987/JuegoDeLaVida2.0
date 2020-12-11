/*
 * informacionGenetica.cpp
 *
 *  Created on: 7 dic. 2020
 *      Author: icoronel
 */

#include"informacionGenetica.h"


InformacionGenetica::InformacionGenetica(std::string bits, int cargaGenetica){
	int pos = bits.find("1");
	if (pos != -1){
		this->bits = bits.substr(pos);

	}
	else
	{
		this->bits = "0";

	}
	this->edad = 1;
	this->intensidad = cargaGenetica;
}

InformacionGenetica::InformacionGenetica(){
	this->bits = '0';
	this->edad = 1;
	this->intensidad = 0;
}

std::string InformacionGenetica::devolverBits(){
	return this->bits;
}

void InformacionGenetica::envejecer(){
	this->edad++;
}


bool InformacionGenetica::esIgualA(InformacionGenetica* otra){
	return (this->devolverBits() == otra->devolverBits());
}

bool InformacionGenetica::estaEncendidoBit(unsigned int i){
	return this->bits[i] == '1';
}

unsigned int InformacionGenetica::contarBits(){
	return this->bits.length() ;
}


void InformacionGenetica::combinarCon(InformacionGenetica* otra){
	InformacionGenetica* min;
	InformacionGenetica* max;
	std::string mutado;
	if(this->contarBits() > otra->contarBits()){
		max = this;
		min = otra;
	}
	else
	{
		max = otra;
		min = this;
	}
	mutado = max->devolverBits();
	for(unsigned int i = 1; i <= min->contarBits() ; i++)
	{
		if(min->estaEncendidoBit(min->contarBits() - i) ^ max->estaEncendidoBit(max->contarBits() - i)){
			mutado.replace(max->contarBits() - i, 1, "1");
		}
		else
		{
			mutado.replace(max->contarBits() - i, 1, "0");
		}
	}
	this->bits = mutado;
}


bool InformacionGenetica::operator ==(InformacionGenetica otro){

	return !(this->bits.compare(otro.bits));

}

bool InformacionGenetica::operator <(InformacionGenetica otro){

	return (this->bits.compare(otro.bits) < 0);
}

bool InformacionGenetica::operator >(InformacionGenetica otro){

	return (this->bits.compare(otro.bits) > 0);
}

int InformacionGenetica::obtenerIntensidad(){

	return this->intensidad;
}

int InformacionGenetica::obtenerEdad(){

	return this->edad;
}
