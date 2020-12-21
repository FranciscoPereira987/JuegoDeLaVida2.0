/*
 * tablero.h
 *
 *  Created on: Dec 3, 2020
 *      Author: shory
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#ifndef CELULA
#define CELULA
#include "celula.h"
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef STRING
#define STRING
#include <string>

using std::string;
#endif

#include "listaSeguimiento.h"

typedef unsigned int uint;

/*
 *
 */
class Tablero{

private:

	int filas;
	int columnas;

	unsigned int poblacion;

	unsigned int muertes;
	unsigned int nacimientos;

	unsigned int totalMuertes;
	unsigned int totalNacimientos;

	unsigned int turno;

	Lista<InformacionGenetica>* baseGenetica;

	Celula*** juego;

	ListaSeguimiento* seguimientoGenes;

	/*
	 * Pre: La cantidad de filas y columnas debe ser
	 * positiva
	 * Post: Carga el tablero desde un archivo
	 */
	void obtenerDatos(string path);

	/*
	 * Pre: La cantidad de filas y columnas debe
	 * ser positiva
	 * Post: Inicializa el Tablero
	 */
	void inicializarTablero(int cantFilas, int cantColumnas);


	/*
	 * Pre: El nrFila y el nrColumna debe ser
	 * valido
	 * Post: Se le agrega puntaje a las celulas
	 * adyacentes
	 */
	void contarAdyacentes(int nrFila, int nrColumna, Genes genes);

	/*
	 * Pre: nrFila y nrColumna deben ser validos
	 * y debe haber una celula viva en una posicion
	 * adyacente
	 * Post: Se crea una celula con puntaje uno si no
	 * habia ninguna, caso contrario. Se le suma una vecina
	 */
	void contarVecina(int nrFila, int nrColumna, Genes genes);

	/*
	 * Post: Se libera la memoria de los punteros
	 */
	void limpiarTablero();

	/*
	 * Pre: La fila debe ser valida
	 * Post: Libera el espacio de esa fila
	 */
	void limpiarFila(int fila);

	/*
	 * pre: la fila y columna deben ser validas
	 * ademas, debe haber una celula en ese lugar
	 * Post: Se libera la memoria ocupada por las
	 * celulas
	 */
	void limpiarCelula(int fila, int columna);

	/*
	 * Post: Devuelve si la posicion pasada
	 * como parametro es valida
	 */
	bool posicionValida(int nrFila, int nrColumna);

	/*
	 * Post: Devuelve los puntajes a cero y mata celulas muertas
	 */
	void definirTablero();

	/*
	 * pre: nrFila y nrColumna deben ser validos
	 * Post: Devuelve si en esa posicion del tablero hay una
	 * celula y si la misma esta muerta
	 */
	bool celulaMuerta(int nrFila, int nrColumna);

	/*
	 * Post: inicializa todos los punteros a celula como NULL
	 */
	void inicializarFila(Celula**& fila);

	/*
	 * pre: una celula nacio o murio
	 * post: suma el nacimiento o la muerte
	 */
	void sumarSuceso(bool estadActual, bool cambio);

	/*
	 * Post: divide el total por la cantidad de turnos
	 * y retorna el resultado
	 */
	float calcularPromedio(unsigned int total,unsigned int turnos);

public:

	/*
	 * Pre: La ruta debe ser valida y
	 * contener una cantidad de columnas y
	 * filas positivas
	 * Post: Inicializa el tablero de juego
	 */
	Tablero(string path);

	/*
	 * pre: cantFilas y cantColumnas deben ser
	 * mayores a 0
	 * Post:Se crea el tablero
	 */
	Tablero(int cantFilas, int cantColumnas);

	/*
	 * Post: ---
	 */
	~Tablero();

	/*
	 * pre: el nrFila y el nrColumna deben
	 * ser validos entre [1-cantX]
	 * post: Se agrega una celula viva en
	 * esa posicion con los genes pasados
	 * como parametros
	 */
	void agregarCelula(int nrFila, int nrColumna, Lista<InformacionGenetica> genes);

	/*
	 * Pre: ---
	 * Post: El tablero se actualiza
	 * al proximo turno
	 */
	void actualizar();

	/*
	 * Post: imprime el tablero
	 */
	void imprimirTablero();

	/*
	 * Post: Imprime informacion sobre el estado del juego
	 */
	void imprimirInfoActual();

	/*
	 * Post: imprime si el juego esta congelado o activo
	 */
	void estadoDelJuego();

	/*
	 * post:devuelve el turno acutal
	 */
	unsigned int obtenerTurno();

	/*
	 * pre: el gen tiene que existir en el tablero
	 * post: agrega el gen a la lista de seguimiento
	 */
	void seguirGen(string gen);

	/*
	 * pre: el gen tiene que estar en la lista de seguimiento
	 * post: devuelve la informacion acumulada del gen
	 */
	void dejarDeSeguirGen(string gen);

	/*
	 * pre: el gen debe estar existir en el tablero
	 * post: busca el gen en la lista de seguimiento
	 */
	bool buscarGen(string gen);

	/*
	 * post: devuelve si no hay ningun gen en la lista de seguimiento
	 */
	bool seguimientoVacio();

	/*
	 * Post: Imprime la base de genes del tablero
	 */
	void imprimirBaseGenetica();

	/*
	 * Post: Devuelve si un gen esta en la base genetica
	 */
	bool genValido(string gen);
};



#endif /* TABLERO_H_ */
