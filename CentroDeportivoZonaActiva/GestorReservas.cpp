#include <iostream>
#include "GestorReservas.h"

using namespace std;

//Constructor y destructor
GestorReservas::GestorReservas() {
	total = 0;
	for (int i = 0; i < 120; i++) reservas[i] = nullptr;
}

GestorReservas::~GestorReservas() {
	for (int i = 0; i < total; i++) {
		delete reservas[i];
	}
}

//Metodos de clase
bool GestorReservas::crear(Cliente* cliente, Cancha* cancha, int franjaInicial,
	int cantidadFranjas, string fecha) {

	if (total >= 120) return false;
	if (cliente == nullptr || cancha == nullptr) return false;
	if (cantidadFranjas <= 0) return false;
	if (franjaInicial < 0 || franjaInicial + cantidadFranjas > 12) return false;

	// Verificar que todas las franjas solicitadas esten libres
	for (int i = franjaInicial; i < franjaInicial + cantidadFranjas; i++) {
		if (!cancha->getEstadoFranja(i).estaLibre()) {
			return false; // al menos una franja no esta libre
		}
	}

	// Marcar las franjas como Ocupadas
	for (int i = franjaInicial; i < franjaInicial + cantidadFranjas; i++) {
		cancha->setEstadoFranja(i, "O");
	}

	double monto = cancha->getPrecio() * cantidadFranjas;
	int id = total + 1;
	reservas[total] = new Reserva(id, cliente, cancha, franjaInicial,
		cantidadFranjas, fecha, monto);
	total++;
	return true;
}

bool GestorReservas::cancelar(int numeroReserva) {
	Reserva* r = buscar(numeroReserva);
	if (r == nullptr) return false;
	if (!r->estaActiva()) return false;

	Cancha* cancha = r->getCancha();
	if (cancha != nullptr) {
		int inicio = r->getFranjaInicial();
		int cantidad = r->getCantidadFranjas();
		for (int i = inicio; i < inicio + cantidad; i++) {
			cancha->setEstadoFranja(i, "L");
		}
	}

	r->cancelar();
	// Nota: aqui es el punto donde, en el modulo de Listado de Espera,
	// se debe revisar si hay clientes esperando por esta cancha/franja
	// para avisarles que ya quedo disponible.
	return true;
}

Reserva* GestorReservas::buscar(int numeroReserva) const {
	for (int i = 0; i < total; i++) {
		if (reservas[i] != nullptr && reservas[i]->getId() == numeroReserva) {
			return reservas[i];
		}
	}
	return nullptr;
}

void GestorReservas::listarTodas() const {
	if (total == 0) {
		cout << "No hay reservas registradas." << endl;
		return;
	}
	for (int i = 0; i < total; i++) {
		if (reservas[i] != nullptr) {
			reservas[i]->mostrarInfo();
			cout << "-------------------------" << endl;
		}
	}
}

void GestorReservas::listarPorCliente(int idCliente) const {
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

void GestorReservas::listarPorCancha(int idCancha) const {
	bool encontro = false;
	for (int i = 0; i < total; i++) {
		if (reservas[i] == nullptr) continue;
		Cancha* c = reservas[i]->getCancha();
		if (c != nullptr && c->getId() == idCancha) {
			reservas[i]->mostrarInfo();
			encontro = true;
		}
	}
	if (!encontro) {
		cout << "La cancha no tiene reservas registradas." << endl;
	}
}

int GestorReservas::getCantidad() const {
	return total;
}

Reserva* GestorReservas::getReserva(int indice) const {
	if (indice >= 0 && indice < total) {
		return reservas[indice];
	}
	return nullptr;
}