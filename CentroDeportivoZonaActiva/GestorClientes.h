/*Universidad nacional
Maria Emilia Gamboa Abarca
Clase coleccion que administra los clientes del sistema
*/

#pragma once
#include <string>
#include <iostream>
#include "Cliente.h"

using namespace std;

class GestorClientes {
public:
	static const int MAX_CLIENTES = 100;

private:
	Cliente* clientes[MAX_CLIENTES];   // arreglo unidimensional de punteros
	int total;

public:
	//Constructor y destructor
	GestorClientes();
	~GestorClientes();

	//Metodos de clase

	// Agrega un cliente si hay espacio y su ID no esta duplicado.
	bool agregar(Cliente* nuevoCliente); // false si esta lleno o el ID se repite

	// Elimina un cliente por posicion en el arreglo
	bool eliminar(int indice);

	// Busca un cliente por su ID (no por posicion)
	Cliente* buscar(int id) const; 

	Cliente* getCliente(int indice) const;
	int getCantidad() const;
	bool estaLleno() const;
	bool existeID(int id) const;

	void listar() const;

};

