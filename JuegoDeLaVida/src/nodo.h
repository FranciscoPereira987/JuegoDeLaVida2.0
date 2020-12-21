/*
 * nodo.h
 *
 *  Created on: Dec 3, 2020
 *      Author: francisco
 */

#ifndef NODO_H_
#define NODO_H_

#ifndef NULL
#define NULL 0
#endif

/*
 * Clase nodo con valor
 * y puntero a un siguiente
 */
template <class Type> class Nodo{

private:

	Type* llave;

	Nodo* siguiente;

public:

	/*
	 * Post: Crea un nodo, con siguiente nulo
	 */
	Nodo(Type valor);

	/*
	 * Post: Crea un nodo, con siguiente como
	 * el valor pasado como parametro
	 */
	Nodo(Type valor, Nodo<Type>* nodoSiguiente);

	/*
	 * Post: Libera la memoria ocupada por el nodo
	 */
	~Nodo();

	/*
	 * Post: Devuelve el valor del Nodo
	 */
	Type getValue();

	/*
	 * Post: Devuelve un puntero a la llave
	 */
	Type* getValuePointer();

	/*
	 * Post: Devuelve un puntero a siguiente
	 */
	Nodo<Type>* getNext();

	/*
	 * Post: Cambia el valor de siguiente
	 */
	void setNext(Nodo<Type>* nuevoSiguiente);

	/*
	 * Post: Cambia el valor de la llave
	 */
	void setValue(Type valor);

};


template <class Type>
Nodo<Type>::Nodo(Type valor){

	siguiente = NULL;

	llave = new Type(valor);

}

template <class Type>
Nodo<Type>::Nodo(Type valor, Nodo<Type>* nodoSiguiente){

	siguiente = nodoSiguiente;

	llave = new Type(valor);

}

template <class Type>
Nodo<Type>::~Nodo(){
	if(llave){
		delete llave;
	}
}

template <class Type>
void Nodo<Type>::setNext(Nodo<Type>* nuevoSiguiente){

	siguiente = nuevoSiguiente;

}

template <class Type>
void Nodo<Type>::setValue(Type valor){
	if(!llave){
		llave = new Type;
	}
	llave = valor;
}


template <class Type>
Type Nodo<Type>::getValue(){

	return *llave;
}

template <class Type>
Type* Nodo<Type>::getValuePointer(){

	return llave;

}

template <class Type>
Nodo<Type>* Nodo<Type>::getNext(){

	return siguiente;
}
#endif /* NODO_H_ */
