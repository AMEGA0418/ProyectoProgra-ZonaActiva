#pragma once
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Cancha.h"

using namespace std;

class Reserva{
	//Atributos: int ID, Cliente* cliente, Cancha* cancha, int numeroFranja, string fecha
private:
	int ID;
	Cliente * cliente;
	Cancha* cancha;
	int numeroFranja;
	string fecha;
public:
	//Constructores
	Reserva() : ID(0), cliente(nullptr), cancha(nullptr), numeroFranja(0), fecha("") {}
	Reserva(int ID, Cliente* cliente, Cancha* cancha, int numeroFranja, string fecha) : ID(ID), cliente(cliente), cancha(cancha), numeroFranja(numeroFranja), fecha(fecha) {
		this->ID = ID;
		this->cliente = cliente;
		this->cancha = cancha;
		this->numeroFranja = numeroFranja;
		this->fecha = fecha;
	}
	//Getters y Setters
	int getId() const { return ID; }
	Cliente* getCliente() const { return cliente; }
	Cancha* getCancha() const { return cancha; }
	int getNumeroFranja() const { return numeroFranja; }
	string getFecha() const { return fecha; }
	void setId(int nuevoID) { ID = nuevoID; }
	void setCliente(Cliente* nuevoCliente) { cliente = nuevoCliente; }
	void setCancha(Cancha* nuevaCancha) { cancha = nuevaCancha; }
	void setNumeroFranja(int nuevaFranja) { numeroFranja = nuevaFranja; }
	void setFecha(string nuevaFecha) { fecha = nuevaFecha; }

	//Metodos de clase
	void mostrarInfo() const {
		cout << "====DATOS DE LA RESERVA =====" << endl;
		cout << "ID: " << ID << endl;
		cout << "Cliente: " << cliente->getNombre() << endl;
		cout << "Cancha: " << cancha->getNombre() << endl;
		cout << "Numero de Franja: " << numeroFranja << endl;
		cout << "Fecha: " << fecha << endl;
	}
};

