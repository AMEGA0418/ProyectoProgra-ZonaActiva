#pragma once
#include <iostream>
#include <string>
#include "Cliente.h"

using namespace std;

class GestorClientes{
private:
	Cliente* clientes[100];
	int total;
public:
	// Constructores
	GestorClientes() {
		total = 0;
		for (int i = 0; i < 100; i++) {
			clientes[i] = nullptr;
		}
	}
	GestorClientes(Cliente** clientes, int total) {
		this->total = total;
		for (int i = 0; i < total; i++) {
			this->clientes[i] = clientes[i];
		}
		for (int i = total; i < 100; i++) {
			this->clientes[i] = nullptr;
		}
	}

	// Metodos
	// Agregar un cliente (mientras haya espacio)
	bool agregar(Cliente* nuevoCliente) {
		if (total < 100) {
			clientes[total] = nuevoCliente;
			total++;
			return true;
		}
		return false; // ya no hay espacio
	}

	// Eliminar un cliente por posición
	bool eliminar(int indice) {
		if (indice < 0 || indice >= total) {
			return false; // índice inválido
		}
		if (clientes[indice] != nullptr) {
			delete clientes[indice]; // libera la memoria del puntero
		}
		// Recorremos el resto para "recorrer" el hueco
		for (int i = indice; i < total - 1; i++) {
			clientes[i] = clientes[i + 1];
		}
		clientes[total - 1] = nullptr;
		total--;
		return true;
	}

	// Buscar un cliente por su código/id
	Cliente* buscar(int id) {
		for (int i = 0; i < total; i++) {
			if (clientes[i] == nullptr) continue;
			if (clientes[i]->getID() == id) {
				return clientes[i];
			}
		}
		return nullptr; // no encontrado
	}

	void listar() {
		cout << "Lista de Clientes:" << endl;
		for (int i = 0; i < total; i++) {
			if (clientes[i] != nullptr) {
				cout << "ID: " << clientes[i]->getID()
					<< ", Nombre: " << clientes[i]->getNombre()
					<< ", Correo: " << clientes[i]->getCorreo()
					<< endl;
			}
		}
	}

	// Encapsulador 
	int getCantidad() {
		return total;
	}
};

