#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cliente{
	//Atributos: int id, string nombre, string telefono string correo
private:
	int id;
	string nombre;
	string telefono;
	string correo;
public:
	//Constructores
	Cliente() : id(0), nombre(""), telefono(""), correo(""){}
	Cliente(int id, string nombre, string telefono, string correo) : id(id), nombre(nombre), telefono(telefono), correo(correo) {
		this->id = id;
		this->nombre = nombre;
		this->telefono = telefono;
		this->correo = correo;
	}
	//Metodos de clase
	//Getter
	int getID() const { return id; }
	string getNombre() const { return nombre; }
	string getTelefono() const { return telefono; }
	string getCorreo() const { return correo; }
	//Setter
	void setID(int nuevoID) { id = nuevoID;}
	void setNombre(string nuevoNombre) { nombre = nuevoNombre; }
	void setTelefono(string nuevoTelefono) { telefono = nuevoTelefono; }
	void setCorreo(string nuevoCorreo) { correo = nuevoCorreo; }

	void mostrarInfo() const {
		cout << "====DATOS DEL CLIENTE =====" << endl;
		cout << "ID: " << id << endl;
		cout << "Nombre: " << getNombre() << endl;
		cout << "Telefono: " << getTelefono() << endl;
		cout << "Correo: " << getCorreo() << endl;

	}

};

