/*Universidad nacional
Fecha:07/09/2026
Andrey David Arias Pérez
Clase para crear la franja que representará la disponibilidad o los horarios de la cancha*/

#pragma once
#include <iostream>
#include <string>
using namespace std;

class FranjaHoraria {
	//Atributos
private:
	int numero;
	char estado;
	//Constructor
public:
	// Constructores
	FranjaHoraria();
	FranjaHoraria(int numero, char estado);
	//Encapsuladores
	int getNumero() const;
	void setNumero(int nuevoNumero);
	char getEstado() const;
	bool setEstado(char nuevoEstado);   // false si el caracter no es L, O o M
	//Métodos
	bool estaLibre() const;
	bool estaOcupada() const;
	bool enMantenimiento() const;
	int getHoraInicio() const;         // franja 0 -> 8, franja 11 -> 19
	int getHoraFin() const;            // franja 0 -> 9, franja 11 -> 20
	string getRangoHora() const;   // "08:00 - 09:00"
	string getEstadoTexto() const; // "Libre", "Ocupada", "Mantenimiento"
};
