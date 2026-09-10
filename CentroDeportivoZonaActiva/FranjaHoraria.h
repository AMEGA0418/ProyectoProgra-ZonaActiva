//Universidad nacional
//fecha:07/09/2026
//Andrey David Arias Pérez
//Clase para crear la franja que representará la disponibilidad
//o los horarios de la cancha

#pragma once
#include <iostream>
#include <string>
using namespace std;

class FranjaHoraria {
	//Atributos
private:
	int numero;
	string estado;
	//Constructor
public:
	FranjaHoraria() {
		numero = 0;
		estado = "L";
	}
	FranjaHoraria(int numero, string estado) {
		this->numero = numero;
		this->estado = estado;
	}
	//Encapsuladores
	int getNumero() {
		return numero;
	}
	void setNumero(int nuevoNumero) {
		numero = nuevoNumero;
	}
	string getEstado() {
		return estado;
	}
	void setEstado(string nuevoEstado) {
		estado = nuevoEstado;
	}
	//Métodos
	bool estaLibre() {
		return estado == "L";
	}
};

