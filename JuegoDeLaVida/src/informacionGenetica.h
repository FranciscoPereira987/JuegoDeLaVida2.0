/*
 * informacionGenetica.h
 *
 *  Created on: 7 dic. 2020
 *      Author: icoronel
 */

#ifndef INFORMACIONGENETICA_H_
#define INFORMACIONGENETICA_H_

#include<string>
#include<iostream>

/* La Informacion Genetica está conformada por una
* secuencia de bits.
* Un bit es la mínima expresión de información,
* que puede tomar dos únicos valores posibles: 0/1,
* apagado/encendido o desactivado/activado.
*/
class InformacionGenetica{
private:
	std::string bits;
	unsigned int edad;
	unsigned int intensidad;
public:
	/* pre : 'bits' es una secuencia de 1 y 0.
	* post: la instancia creada representa la
	información dada en 'bits'.
	*/
	InformacionGenetica(std::string bits);
	/* post: la instancia creada representa la
	*
	información dada por un bit: 0.
	*/
	InformacionGenetica();
	/* post : indica si la instancia y 'otra'
	* representan la misma secuencia de
	* bits, es decir si son iguales.
	*/
	bool esIgualA(InformacionGenetica* otra);
	/* post: combina la secuencia de bits de la
	* instancia con la secuencia bits de
	* 'otra', aplicando un OR bit a bit.
	*/
	void combinarCon(InformacionGenetica* otra);
	/* post: indica si el valor del 'i'-ésimo bit
	* es 1, numerándolos de derecha a
	* izquierda a partir de 1.
	*/
	bool estaEncendidoBit(unsigned int i);
	/* post: devuelve cantidad de bits que tiene
	la instancia.
	*/
	unsigned int contarBits();

	void envejecer();

	std::string devolverBits();
};
#endif /* INFORMACIONGENETICA_H_ */
