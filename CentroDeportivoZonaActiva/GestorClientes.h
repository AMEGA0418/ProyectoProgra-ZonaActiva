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
private:
	Cliente* clientes[100];
	int total;

public:
	//Constructor y destructor
	GestorClientes();
	~GestorClientes();

	//Metodos de clase

	// Agrega un cliente si hay espacio y su ID no esta duplicado.
	bool agregar(Cliente* nuevoCliente);

	// Elimina un cliente por posicion en el arreglo
	bool eliminar(int indice);

	// Busca un cliente por su ID (no por posicion)
	Cliente* buscar(int id) const;

	void listar() const;

	int getCantidad() const;
	Cliente* getCliente(int indice) const;
};

