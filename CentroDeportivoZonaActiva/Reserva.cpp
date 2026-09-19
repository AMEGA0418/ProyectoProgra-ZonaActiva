#include <iostream>
#include "Reserva.h"

using namespace std;

//Constructores
Reserva::Reserva()
	: id(0), cliente(nullptr), cancha(nullptr), franjaInicial(0),
	cantidadFranjas(0), fecha(""), monto(0.0), estado("Activa") {}

Reserva::Reserva(int id, Cliente* cliente, Cancha* cancha, int franjaInicial,
	int cantidadFranjas, string fecha, double monto)
	: id(id), cliente(cliente), cancha(cancha), franjaInicial(franjaInicial),
	cantidadFranjas(cantidadFranjas), fecha(fecha), monto(monto), estado("Activa") {}

//Getters
int Reserva::getId() const { return id; }
Cliente* Reserva::getCliente() const { return cliente; }
Cancha* Reserva::getCancha() const { return cancha; }
int Reserva::getFranjaInicial() const { return franjaInicial; }
int Reserva::getCantidadFranjas() const { return cantidadFranjas; }
string Reserva::getFecha() const { return fecha; }
double Reserva::getMonto() const { return monto; }
string Reserva::getEstado() const { return estado; }
bool Reserva::estaActiva() const { return estado == "Activa"; }

//Setters
void Reserva::setId(int nuevoId) { id = nuevoId; }
void Reserva::setCliente(Cliente* nuevoCliente) { cliente = nuevoCliente; }
void Reserva::setCancha(Cancha* nuevaCancha) { cancha = nuevaCancha; }
void Reserva::setFranjaInicial(int nuevaFranja) { franjaInicial = nuevaFranja; }
void Reserva::setCantidadFranjas(int nuevaCantidad) { cantidadFranjas = nuevaCantidad; }
void Reserva::setFecha(string nuevaFecha) { fecha = nuevaFecha; }
void Reserva::setMonto(double nuevoMonto) { monto = nuevoMonto; }

//Metodos de clase
void Reserva::cancelar() {
	estado = "Cancelada";
}

void Reserva::mostrarInfo() const {
	cout << "==== DATOS DE LA RESERVA ====" << endl;
	cout << "Numero de reserva: " << id << endl;
	cout << "Cliente: " << (cliente != nullptr ? cliente->getNombre() : "N/A") << endl;
	cout << "Cancha: " << (cancha != nullptr ? cancha->getNombre() : "N/A") << endl;
	cout << "Franja inicial: " << franjaInicial
		<< " | Cantidad de franjas: " << cantidadFranjas << endl;
	cout << "Fecha: " << fecha << endl;
	cout << "Monto: " << monto << endl;
	cout << "Estado: " << estado << endl;
}