#include <iostream>
#include "GestorClientes.h"

using namespace std;

//Constructor y destructor
GestorClientes::GestorClientes() {
	total = 0;
	for (int i = 0; i < 100; i++) {
		clientes[i] = nullptr;
	}
}

GestorClientes::~GestorClientes() {
	for (int i = 0; i < total; i++) {
		delete clientes[i];
	}
}

//Metodos de clase
bool GestorClientes::agregar(Cliente* nuevoCliente) {
	if (nuevoCliente == nullptr) return false;
	if (total >= 100) return false;
	if (buscar(nuevoCliente->getID()) != nullptr) return false; // ID duplicado
	clientes[total] = nuevoCliente;
	total++;
	return true;
}

bool GestorClientes::eliminar(int indice) {
	if (indice < 0 || indice >= total) {
		return false;
	}
	delete clientes[indice];
	for (int i = indice; i < total - 1; i++) {
		clientes[i] = clientes[i + 1];
	}
	clientes[total - 1] = nullptr;
	total--;
	return true;
}

Cliente* GestorClientes::buscar(int id) const {
	for (int i = 0; i < total; i++) {
		if (clientes[i] != nullptr && clientes[i]->getID() == id) {
			return clientes[i];
		}
	}
	return nullptr;
}

void GestorClientes::listar() const {
	if (total == 0) {
		cout << "No hay clientes registrados." << endl;
		return;
	}
	cout << "Lista de Clientes:" << endl;
	for (int i = 0; i < total; i++) {
		if (clientes[i] != nullptr) {
			cout << "ID: " << clientes[i]->getID()
				<< ", Nombre: " << clientes[i]->getNombre()
				<< ", Telefono: " << clientes[i]->getTelefono()
				<< ", Correo: " << clientes[i]->getCorreo()
				<< endl;
		}
	}
}

int GestorClientes::getCantidad() const {
	return total;
}

Cliente* GestorClientes::getCliente(int indice) const {
	if (indice >= 0 && indice < total) {
		return clientes[indice];
	}
	return nullptr;
}