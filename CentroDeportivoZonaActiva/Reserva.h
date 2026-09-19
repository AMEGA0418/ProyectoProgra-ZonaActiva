/*Universidad nacional 
María Emilia Gamboa Abarca 
Clase que representa una reserva de una cancha por parte de un cliente*/

#pragma once
#include <string>
#include <iostream>
#include "Cliente.h"
#include "Cancha.h"

using namespace std;

class Reserva {
private:
	int id;
	Cliente* cliente;
	Cancha* cancha;
	int franjaInicial;      // posicion (0 a 11) de la primera franja reservada
	int cantidadFranjas;    // cantidad de franjas consecutivas reservadas
	string fecha;
	double monto;           // precio por hora de la cancha * cantidadFranjas
	string estado;          // "Activa" o "Cancelada"

public:
	//Constructores
	Reserva();
	Reserva(int id, Cliente* cliente, Cancha* cancha, int franjaInicial,
		int cantidadFranjas, string fecha, double monto);

	//Getters
	int getId() const;
	Cliente* getCliente() const;
	Cancha* getCancha() const;
	int getFranjaInicial() const;
	int getCantidadFranjas() const;
	string getFecha() const;
	double getMonto() const;
	string getEstado() const;
	bool estaActiva() const;

	//Setters
	void setId(int nuevoId);
	void setCliente(Cliente* nuevoCliente);
	void setCancha(Cancha* nuevaCancha);
	void setFranjaInicial(int nuevaFranja);
	void setCantidadFranjas(int nuevaCantidad);
	void setFecha(string nuevaFecha);
	void setMonto(double nuevoMonto);

	//Metodos de clase

	// Marca la reserva como cancelada. No borra la reserva, solo cambia su estado.
	// (Devolver las franjas a "Libre" en la Cancha es responsabilidad de quien
	// gestiona la reserva -> ver GestorReservas::cancelar)
	void cancelar();

	void mostrarInfo() const;
};