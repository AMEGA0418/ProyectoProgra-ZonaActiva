#pragma once
#include <iostream>
#include <string>
#include "Reserva.h"

using namespace std;

class GestorReservas{
	//Abtributos: Reserva* reservas[120], int total
private:
	Reserva * reservas[120];
	int total;
public:
	//Constructores
	GestorReservas() {
		total = 0;
		for (int i = 0; i < 120; i++) reservas[i] = nullptr;
	}
	GestorReservas(Reserva * *reservas, int total) {
		this->total = total;
		for (int i = 0; i < total; i++) {
			this->reservas[i] = reservas[i];
		}
		for (int i = total; i < 120; i++) {
				this->reservas[i] = nullptr;
			}
	}

	//Metodos de clase
	bool crear(Cliente* cliente, Cancha* cancha, int franjaInicial,
		int cantidadFranjas, string fecha) {
		// Validaciones básicas
		if (total >= 120) return false;
		if (cliente == nullptr || cancha == nullptr) return false;

		// Crear una reserva simple usando la estructura Reserva existente
		int id = total + 1;
		reservas[total] = new Reserva(id, cliente, cancha, franjaInicial, fecha);
		total++;
		return true;
	}

	bool cancelar(int numeroReserva) {
		// Buscar y eliminar la reserva por su numero
		for (int i = 0; i < total; i++) {
			if (reservas[i] != nullptr && reservas[i]->getId() == numeroReserva) {
				delete reservas[i];
				// desplazar hacia la izquierda
				for (int j = i; j < total - 1; j++) reservas[j] = reservas[j + 1];
				reservas[total - 1] = nullptr;
				total--;
				return true;
			}
		}
		return false;
	}

	Reserva* buscar(int numeroReserva) const {
		for (int i = 0; i < total; i++) {
			if (reservas[i] != nullptr && reservas[i]->getId() == numeroReserva) {
				return reservas[i];
			}
		}
		return nullptr;
	}

	void listarPorCliente(int idCliente) const {
		bool encontro = false;
		for (int i = 0; i < total; i++) {
			if (reservas[i] == nullptr) continue;
			Cliente* c = reservas[i]->getCliente();
			if (c != nullptr && c->getID() == idCliente) {
				reservas[i]->mostrarInfo();
				encontro = true;
			}
		}
		if (!encontro) {
			cout << "El cliente no tiene reservas registradas." << endl;
		}
	}

	void listarPorCancha(int idCancha) const {
		bool encontro = false;
		for (int i = 0; i < total; i++) {
			if (reservas[i] == nullptr) continue;
			Cancha* c = reservas[i]->getCancha();
			if (c != nullptr) {
				//sale error, porque aun no esta la clase cancha ni el metodo: getID()
				if (c->getID() == idCancha) {
					reservas[i]->mostrarInfo();
					encontro = true;
				}
			}
		}
		if (!encontro) {
			cout << "La cancha no tiene reservas registradas." << endl;
		}
	}

	int getCantidad() const {
		return total;
	}
};

