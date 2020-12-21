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

	/*
	 * Post: Define la cadena de bits
	 * empezando desde el primer 1
	 */
	void definirBits();

public:
	/* pre : 'bits' es una secuencia de 1 y 0.
	* post: la instancia creada representa la
	información dada en 'bits'.
	*/
	InformacionGenetica(std::string bits, int intensidad);
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

	/*
	 * Post: Agrega al stream los bits del gen
	 */
	friend std::ostream& operator<<(std::ostream& o, InformacionGenetica const& gen);

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

	/*
	 * Post: Devuelve la intensidad del gen
	 */
	int obtenerIntensidad();

	/*
	 * Post: Cambia la intensidad del gen
	 */
	void cambiarIntensidad(int nuevaIntensidad);

	/*
	 * Post: Devuelve si el gen es mas
	 * joven que otro
	 */
	bool esMasJoven(InformacionGenetica* otro);

	/*
	 * Post: Devuelve la edad del gen
	 */
	int obtenerEdad();

	/*
	 * Post: Cambia la edad de un gen
	 */
	void cambiarEdad(int nuevaEdad);


	/*
	 * Post: Aumenta la edad del gen en uno
	 */
	void envejecer();

	/*
	 * Post: Devuelve los bits del gen
	 */
	std::string devolverBits();

	/*
	 * Post: Devuelve si la cadena de bits del
	 * gen es igual a la de otro
	 */
	bool operator ==(InformacionGenetica otro);

	/*
	 * Post: Devuelve si la cadena de bits
	 * es distinta a la de otro
	 */
	bool operator !=(InformacionGenetica otro);

	/*
	 * Post: Devuelve si la cadena de bits del gen
	 * es mayor a la del otro
	 */
	bool operator >(InformacionGenetica otro);

	/*
	 * Post: Devuelve si la cadena de bits del gen es
	 * menor a la del otro
	 */
	bool operator <(InformacionGenetica otro);
};
#endif /* INFORMACIONGENETICA_H_ */
