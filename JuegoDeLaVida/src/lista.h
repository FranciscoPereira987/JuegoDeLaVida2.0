/*
 * lista.h
 *
 *  Created on: Dec 3, 2020
 *      Author: francisco
 */

#ifndef LISTA_H_
#define LISTA_H_


#ifndef NODO
#define NODO
#include "nodo.h"
#endif


#ifndef IMPRESION
#define IMPRESION
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
#endif

#include "informacionGenetica.h"

/*
 * Template de lista simplemente
 * enlazada con cursor
 *
 */
template <typename Type> class Lista{

private:

	Nodo<Type>* head;

	Nodo<Type>* cursor;

	unsigned int tamanio;

	/*
	 * Post: Libera la memoria de todos
	 * los nodos de la lista
	 */
	void liberar(Nodo<Type>* actual);

	/*
	 * Post: Verifica que la posicion
	 * sea valida
	 */
	bool posicionValida(int posicion);

	/*
	 * Pre: La posicion debe ser valida y el cursor
	 * debe estar apuntando al head
	 * Post: inserta al elemento en la posicion dada
	 */
	void insertarElemento(Type valor, int posObjetivo);

	/*
	 * Pre: La posicion debe ser valida y el cursor apuntar
	 * al head
	 * post: elimina al elemento en la posicion i de la
	 * lista
	 */
	void eliminarElemento(int posObjetivo);

	/*
	 * pre: La lista no puede estar vacia
	 * Post: Elimina al primer elemento de la lista
	 */
	void eliminarPrimero();

	/*
	 * Pre: La posicion debe estar en el rango
	 * Post: Apunta el cursor a la posicion pasada
	 * por parametro
	 */
	void moverCursor(int posicion);

	/*
	 * Post: Crea una copia de otra lista
	 * en la actual
	 */
	void copiarLista(Lista<Type>& otra);


public:

	/*
	 * Post: Crea una lista con
	 * un elemento
	 */
	Lista(Type valor);

	/*
	 * Post: Crea una copia de
	 * otra lista
	 */
	Lista(Lista<Type>& otra);

	/*
	 * Post: Crea una lista vacia
	 */
	Lista();

	/*
	 * Post:---
	 */
	~Lista();

	/*
	 * Pre: La posicion debe ser valida
	 * (Estar entre 0 y tamano)
	 * Post: Agrega al elemento en la posicion
	 * especificada
	 */
	void insertar(Type valor, int posicion);

	/*
	 * Pre: El tipo de dato de la lista
	 * debe ser comparable
	 * Post: Incerta en la lista, el valor
	 * luego de encontrar un valor menor
	 * al pasado como parametro
	 */
	void insertar(Type valor);

	/*
	 * Post: Devuelve la cantidad de
	 * elementos de la lista
	 */
	unsigned int longitud();

	/*
	 * Post: Agrega el elemento al
	 * final de la lista
	 */
	void append(Type valor);

	/*
	 * Post: Agrega al elemento al
	 * principio de la lista
	 */
	void push(Type valor);

	/*
	 * Post: Elimina al elemento
	 * de la lista, solo la primer
	 * aparicion.
	 * Si no esta en la lista, no hace nada
	 */
	void pop(Type valor);

	/*
	 * pre: La posicion debe ser valida
	 * post: Elimina al elemento de
	 * la posicion i
	 */
	void remove(int posicion);

	/*
	 * Post: Imprime la lista en orden
	 */
	void imprimir();

	/*
	 * Pre: La posicion debe ser valida
	 * Post: Devuelve una referencia a la posicion indicada
	 * (a el nodo de esa posicion)
	 *
	 */
	 Type& operator[](int posicion);

	 /*
	 * Post: Mueve el cursor
	 * a la derecha, si la posicion
	 * es la ultima, devuelve NULL
	 */
	 void avanzarCursor();

	 /*
	 * Post: Dirije el cursor al
	 * head
	 */
	 void inicializarCursor();

	 /*
	  * Pre: El cursor no debe apuntar a NULL
	  * Post: Obtiene el valor guardado
	  * en el cursor
	  */
	 Type obtenerCursor();

	 /*
	  * Post: Hace que mi lista sea igual
	  * a otra
	  */
	 Lista<Type>& operator=(Lista<Type>& otra);

	 /*
	  * Post: Devuelve si el elemento
	  * se encuentra en la lista
	  */
	 bool estaEnLista(Type elemento);


};

template <class Type>
Lista<Type>::Lista(){

	head = NULL;

	cursor = NULL;

	tamanio = 0;



}

template <class Type>
Lista<Type>::Lista(Type valor){

	head = new Nodo<Type>(valor);

	cursor = head;


	tamanio = 1;



}

template <class Type>
Lista<Type>::Lista(Lista<Type>& otra){


	tamanio = 0;
	head = NULL;
	cursor = NULL;
	this->copiarLista(otra);

}

template <class Type>
Lista<Type>::~Lista(){

	if(head){
		liberar(head);
		head = NULL;
	}


}

template <class Type>
void Lista<Type>::insertar(Type valor, int posicion){

	if(posicion != tamanio && !(posicionValida(posicion))){
		throw string("POSICION INVALIDA");
	}

	if(posicion == 0){
		push(valor);
	}
	else{
		insertarElemento(valor, posicion);
	}
}

template <class Type>
void Lista<Type>::append(Type valor){

	insertarElemento(valor, tamanio);
}

template <class Type>
void Lista<Type>::push(Type valor){

	Nodo<Type>* nuevo = new Nodo<Type>(valor, head);

	head = nuevo;

	tamanio++;
}

template <class Type>
void Lista<Type>::pop(Type valor){

	cursor = head;

	if (head->getValue() == valor){
		eliminarPrimero();
	}
	else{
		while(cursor->getNext() &&
				cursor->getNext()->getValue() != valor){

			cursor = cursor->getNext();

		}
		if(cursor){
			Nodo<Type>* auxiliar = cursor->getNext();

			cursor->setNext(auxiliar->getNext());

			delete auxiliar;
			tamanio--;
		}
	}

}

template <class Type>
void Lista<Type>::remove(int posicion){

	if(!(posicionValida(posicion))){
		throw string("POSICION INVALIDA");
	}

	if(posicion == 0){
		eliminarPrimero();
	}
	else{
		eliminarElemento(posicion);
	}

}

template <class Type>
void Lista<Type>::imprimir(){

	cursor = head;
	while(cursor){
		cout << cursor->getValue() << "->";
		cursor = cursor->getNext();
	}
	cout << endl;

}


template <class Type>
unsigned int Lista<Type>::longitud(){

	return tamanio;
}

template <class Type>
Type& Lista<Type>::operator[](int posicion){

	if(!posicionValida(posicion)){
		throw string("POSICION INVALIDA");
	}

	moverCursor(posicion);

	return *(this->cursor->getValuePointer());

}

template <class Type>
void Lista<Type>::insertar(Type valor){

	if(!head){
		push(valor);
	}
	else if((head->getValue() < valor)){
		push(valor);
	}
	else{
		inicializarCursor();
		while((cursor->getNext()) && \
				(cursor->getNext()->getValue() > valor)){
			avanzarCursor();
		}
		Nodo<Type>* aux = new Nodo<Type>(valor);

		aux->setNext(cursor->getNext());
		cursor->setNext(aux);
	}

}

template <class Type>
Type Lista<Type>::obtenerCursor(){

	return cursor->getValue();
}

template <class Type>
Lista<Type>& Lista<Type>::operator=(Lista<Type>& otra){

	this->~Lista();
	this->copiarLista(otra);

	return *(this);

}

template <class Type>
bool Lista<Type>::estaEnLista(Type elemento){

	this->inicializarCursor();
	while(this->cursor &&
			this->obtenerCursor() != elemento){
		this->avanzarCursor();
	}


	return (cursor && this->obtenerCursor() == elemento);
}


/*
 * Metodos privados
 */
template <class Type>
void Lista<Type>::liberar(Nodo<Type>* actual){

	if(actual->getNext()){

		liberar(actual->getNext());

	}
	delete actual;

}

template <class Type>
bool Lista<Type>::posicionValida(int posicion){

	return ((posicion >= 0) && (posicion < tamanio));
}

template <class Type>
void Lista<Type>::insertarElemento(Type valor, int posFinal){


	moverCursor(posFinal-1);

	Nodo<Type>* nuevo = new Nodo<Type>(valor, cursor->getNext());

	cursor->setNext(nuevo);
	tamanio++;




}

template <class Type>
void Lista<Type>::eliminarElemento(int posObjetivo){


	moverCursor(posObjetivo-1);
	Nodo<Type>* auxiliar = cursor->getNext();

	cursor->setNext(auxiliar->getNext());
	delete auxiliar;
	tamanio--;

}

template <class Type>
void Lista<Type>::eliminarPrimero(){

	Nodo<Type>* nuevoHead = head->getNext();

	delete head;
	head = nuevoHead;
	tamanio--;

}

template <class Type>
void Lista<Type>::inicializarCursor(){

	cursor = head;

}

template <class Type>
void Lista<Type>::avanzarCursor(){

	if(!(cursor)){
		throw string("CURSOR EN POSICION INVALIDA");
	}

	cursor = cursor->getNext();

}

template <class Type>
void Lista<Type>::moverCursor(int posicion){

	int posActual = 0;
	inicializarCursor();
	while(posActual < posicion){
		avanzarCursor();
		posActual++;
	}

}

template <class Type>
void Lista<Type>::copiarLista(Lista<Type>& otra){

	otra.inicializarCursor();
		while(otra.cursor->getNext()){
			push(otra.obtenerCursor());
			otra.avanzarCursor();
		}
		push(otra.obtenerCursor());
}


#endif /* LISTA_H_ */
