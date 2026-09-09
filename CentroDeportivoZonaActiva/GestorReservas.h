#pragma once
#include <iostream>
#include <string>
#include "Reserva.h"
#include "Cliente.h"
#include "Cancha.h"

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
	bool crearReserva(Cliente* cliente, Cancha* cancha, int numeroFranja) {
		if (cliente == nullptr || cancha == nullptr || numeroFranja <= 0) return false;
		if (total >= 120) return false;
		int id = total + 1;
		reservas[total] = new Reserva(id, cliente, cancha, numeroFranja, "");
		total++;
		return true;
	}
	bool cancelarReserva(int id) {
		for (int i = 0; i < total; i++) {
			if (reservas[i] != nullptr && reservas[i]->getId() == id) {
				delete reservas[i];
				// desplazar el resto hacia la izquierda
				for (int j = i; j < total - 1; j++) {
					reservas[j] = reservas[j + 1];
				}
				reservas[total - 1] = nullptr;
				total--;
				return true;
			}
		}
		return false;
	}
	Reserva buscarReserva(int id) {
		for (int i = 0; i < total; i++) {
			if (reservas[i] != nullptr && reservas[i]->getId() == id) {
				return *reservas[i];
			}
		}
		return Reserva();
	}
	void listarReservasPorCliente(int idCliente) {
		bool encontrado = false;
		cout << "Reservas del cliente con ID " << idCliente << ":" << endl;
		for (int i = 0; i < total; i++) {
			if (reservas[i] != nullptr && reservas[i]->getCliente() != nullptr && reservas[i]->getCliente()->getID() == idCliente) {
				reservas[i]->mostrarInfo();
				encontrado = true;
			}
		}
		if (!encontrado) {
			cout << "No se encontraron reservas para el cliente." << endl;
		}
	}
	void listarReservasPorCancha(int idCancha) {
		bool encontrado = false;
		cout << "Reservas de la cancha con ID " << idCancha << ":" << endl;
		for (int i = 0; i < total; i++) {
			if (reservas[i] != nullptr && reservas[i]->getCancha() != nullptr && reservas[i]->getCancha()->getID() == idCancha) {
				reservas[i]->mostrarInfo();
				encontrado = true;
			}
		}
		if (!encontrado) {
			cout << "No se encontraron reservas para la cancha." << endl;
		}
	}
	int getCantidadDeReservas() {
		return total;
	}
};

