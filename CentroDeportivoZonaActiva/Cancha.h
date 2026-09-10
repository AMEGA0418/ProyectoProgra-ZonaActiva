//Universidad nacional
//fecha:07/09/2026
//Andrey David Arias Pérez
//Clase para crear como tal la cancha 

#pragma once
#include <iostream>
#include <string>
#include"FranjaHoraria.h"
using namespace std;

class Cancha {
	//Atributos
private:
	int id;
	string nombre;
	string deporte;
	FranjaHoraria franjas[12];
	//Constructores
public:
	Cancha() {
		id = 0;
		nombre = "";
		deporte = "";
		for (int i = 0;i < 12;i++) {
			franjas[i] = FranjaHoraria(i, "L");
		}
	}
	Cancha(int id, string nombre, string deporte) {
		this->id = id;
		this->nombre = nombre;
		this->deporte = deporte;
		for (int i = 0; i < 12; i++) {
			franjas[i] = FranjaHoraria(i, "L");
		}
	}
	//Encapsuladores

	int getId() {
		return id;
	}
	void setId(int nuevoId) {
		id = nuevoId;
	}
	string getNombre() {
		return nombre;
	}
	void setNombre(string nuevoNombre) {
		nombre = nuevoNombre;
	}
	string getDeporte() {
		return deporte;
	}
	void setDeporte(string nuevoDeporte) {
		deporte = nuevoDeporte;
	}
	FranjaHoraria getEstadoFranja(int indice) {
		return franjas[indice];
	}
	void setEstadoFranja(int indice, string nuevoEstado) {
		if (indice >= 0 && indice < 12) {
			franjas[indice].setEstado(nuevoEstado);
		}
	}

	//Métodos
	void mostrarDisponibilidad() {
		cout << "Disponibilidad de la cancha " << nombre << ":" << endl;
		cout << "----------------------------------------" << endl;

		for (int i = 0; i < 12; i++) {
			int hora = 8 + i; // franja 0 = 08:00, franja 11 = 19:00
			string estadoTexto;

			if (franjas[i].getEstado() == "L") {
				estadoTexto = "Libre";
			}
			else if (franjas[i].getEstado() == "O") {
				estadoTexto = "Ocupada";
			}
			else if (franjas[i].getEstado() == "M") {
				estadoTexto = "Mantenimiento";
			}

			cout << hora << ":00 [" << i << "] -> "
				<< franjas[i].getEstado() << " (" << estadoTexto << ")" << endl;
		}
	}
};

