#include <iostream>
#include "Cliente.h"

using namespace std;

//Constructores
Cliente::Cliente() : id(0), nombre(""), telefono(""), correo("") {}

Cliente::Cliente(int id, string nombre, string telefono, string correo)
	: id(id), nombre(nombre), telefono(telefono), correo(correo) {}

//Getters
int Cliente::getID() const { return id; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getCorreo() const { return correo; }

//Setters
void Cliente::setID(int nuevoID) { id = nuevoID; }
void Cliente::setNombre(string nuevoNombre) { nombre = nuevoNombre; }
void Cliente::setTelefono(string nuevoTelefono) { telefono = nuevoTelefono; }
void Cliente::setCorreo(string nuevoCorreo) { correo = nuevoCorreo; }

//Metodos de clase
void Cliente::mostrarInfo() const {
	cout << "==== DATOS DEL CLIENTE ====" << endl;
	cout << "ID: " << id << endl;
	cout << "Nombre: " << nombre << endl;
	cout << "Telefono: " << telefono << endl;
	cout << "Correo: " << correo << endl;
}
void Cliente::mostrarLinea() const {
	cout << "ID: " << id
		<< " | Nombre: " << nombre
		<< " | Telefono: " << telefono
		<< " | Correo: " << correo << endl;
}