#pragma once
#include "Cliente.h"
#include <iostream>
#include <string>

using namespace std;

class GestorClientes {
private:
	Cliente* clientes[100];
	int total;
public:
	//1- GestorClientes: Constructor que inicializa el arreglo de clientes.
	GestorClientes() : total(0) {
		for (int i = 0; i < 100; i++) {
			clientes[i] = nullptr;
		}
	}
	//2- Agregar: Método que recibe un puntero a un objeto Cliente y lo agrega al arreglo de clientes.
	bool agregarCliente(Cliente* cliente) {
		if (total < 100) {
			clientes[total] = cliente;
			total++;
			return true;
		}
		return false;
	}
	//3- Eliminar: Método que recibe un índice y elimina el cliente en esa posición.
	bool eliminarCliente(int indice) {
		if (indice >= 0 && indice < total) {
			delete clientes[indice];
			for (int i = indice; i < total - 1; i++) {
				clientes[i] = clientes[i + 1];
			}
			clientes[total - 1] = nullptr;
			total--;
			return true;
		}
		return false;
	}
	//4- Buscar: Método que recibe un índice y devuelve el cliente en esa posición.
	Cliente* buscarCliente(int id) {
		for (int i = 0; i < total; i++) {
			if (clientes[i]->getID() == id) {
				return clientes[i];
			}
		}
		return nullptr;
	}
	//5- Listar: Método que muestra todos los clientes.
	void listarClientes() {}
	//6- Cantidad Clientes: Método que devuelve la cantidad de clientes en el arreglo.
	int getCantidadClientes() const {
		return total;
	}
};