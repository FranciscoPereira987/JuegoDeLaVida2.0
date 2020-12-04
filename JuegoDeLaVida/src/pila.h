/*
 * pila.h
 *
 *  Created on: Dec 3, 2020
 *      Author: francisco
 */

#ifndef PILA_H_
#define PILA_H_

#ifndef LISTA
#define LISTA
#include "lista.h"
#endif

/*
 * clase pila, solo se
 * pueden agregar elementos
 * y sacar elementos
 */
template <class Type> class Pila{

private:

	Lista<Type>* pila;


public:

	/*
	 * Post: crea una pila vacia
	 */
	Pila();

	/*
	 * Post: Crea una pila con un elemento
	 */
	Pila(Type valor);

	/*
	 * Post: ---
	 */
	~Pila();

	/*
	 * Pre: La pila no debe estar vacia
	 * Post: Devuelve el primer elemento
	 * de la pila
	 */
	Type pop();

	/*
	 * Pre: La pila no debe estar vacia
	 * Post: Elimina el primer elemento
	 * de la pila
	 */

	/*
	 * Post: Apila un elemento
	 */
	void apilar(Type valor);

	/*
	 * Post: Devuelve si la pila
	 * esta vacia
	 */
	bool vacia();


};

template <class Type>
Pila<Type>::Pila(){

	pila = new Lista<Type>;

}

template <class Type>
Pila<Type>::Pila(Type valor){

	pila = new Lista<Type>(valor);

}

template <class Type>
Type Pila<Type>::pop(){

	if(vacia()){
		throw string("PILA VACIA");
	}

	Type valor = *(pila)[0];

	pila->remove(0);

	return valor;
}

template <class Type>
void  Pila<Type>::apilar(Type valor){

	pila->push(valor);
}


template <class Type>
bool Pila<Type>::vacia(){

	return pila->longitud();
}

template <class Type>
Pila<Type>::~Pila(){

	pila->~Lista();
	delete pila;

}

#endif /* PILA_H_ */
