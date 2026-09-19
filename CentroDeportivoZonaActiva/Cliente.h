/*Universidad nacional
María Emilia Gamboa Abarca
Clase para representar a un cliente del centro deportivo*/

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cliente {
private:
	int id;
	string nombre;
	string telefono;
	string correo;

public:
	//Constructores
	Cliente();
	Cliente(int id, string nombre, string telefono, string correo);

	//Getters
	int getID() const;
	string getNombre() const;
	string getTelefono() const;
	string getCorreo() const;

	//Setters
	void setID(int nuevoID);
	void setNombre(string nuevoNombre);
	void setTelefono(string nuevoTelefono);
	void setCorreo(string nuevoCorreo);

	//Metodos de clase
	void mostrarInfo() const;
};