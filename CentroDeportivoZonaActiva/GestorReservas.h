/*Universidad nacional
Maria Emilia Gamboa Abarca
Clase coleccion que administra las reservas del sistema
*/

#pragma once
#include <string>
#include <iostream>
#include "Reserva.h"

using namespace std;

class GestorReservas {
private:
	Reserva* reservas[120];
	int total;

public:
	//Constructor y destructor
	GestorReservas();
	~GestorReservas();

	//Metodos de clase

	// Intenta crear una reserva. Devuelve false si:
	// - no hay espacio, cliente o cancha son nulos
	// - la franja inicial / cantidad de franjas es invalida (fuera de 0..11)
	// - alguna de las franjas solicitadas no esta Libre
	// Si todo es valido, marca las franjas correspondientes como "O" (Ocupada)
	// y calcula el monto usando el precio por hora de la cancha.
	bool crear(Cliente* cliente, Cancha* cancha, int franjaInicial,
		int cantidadFranjas, string fecha);

	// Cancela una reserva activa: cambia su estado a "Cancelada" y libera
	// (vuelve a "L") las franjas que tenia ocupadas. No elimina la reserva
	// del arreglo. Devuelve false si no existe o ya estaba cancelada.
	bool cancelar(int numeroReserva);

	Reserva* buscar(int numeroReserva) const;
	void listarTodas() const;
	void listarPorCliente(int idCliente) const;
	void listarPorCancha(int idCancha) const;

	int getCantidad() const;
	Reserva* getReserva(int indice) const;
};