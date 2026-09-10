#pragma once
#include<iostream>
#include<string>
#include"GestorCanchas.h"
#include"GestorReservas.h"
#include"listaEspera.h"
using namespace std;

class Reportes {
	//Esta clase no posee aributos, ya que su función es únicamente 
	// servir como base para otras clases que generen reportes específicos.
public:
	// Constructor
	// este metodo muestra el reporte de las canchas ocupadas
	void GenerarOcupacion(GestorCanchas* gestorCanchas) {
		int ocupacion = 0;

		for (int i = 0; i < gestor->getCantidad(); i++) {

			Cancha* cancha = gestor->getCancha(i);

			for (int j = 0; j < 12; j++) {

				FranjaHoraria franja = cancha->getFranja(j);

				if (franja.getEstado() == "O") {
					ocupacion++;
				}
			}
		}

		cout << "Franjas ocupadas: " << ocupacion << endl;
	}

	void GenerarReservasPorCliente(GestorClientes* gestorClientes, GestorReservas* gestorReservas) {

		cout << "----RESERVAS POR CLIENTE----" << endl;

		if (gestorClientes == nullptr) {
			cout << "No hay gestor de clientes" << endl;
			return;
	}
		if gestorClientes->getCantidad() == 0) {
			cout << "No hay clientes registrados" << endl;
			return;
	}
	for (int i = 0; i < gestorClientes->getCantidad(); i++) {

		Cliente* cliente = gestorClientes->getCliente(i);

		if (cliente != nullptr) {
			cout << endl;
			cout << "Cliente: " << cliente->getNombre() << endl;
			cout << "ID: " << cliente->getId() << endl;
			cout << "Reservas:" << endl;

			gestorReservas->listarPorCliente(cliente->getId());

			cout << "-------------------------" << endl;
		}
	}

	void GenerarResumenDiario(GestorReservas* gestorReservas) {

		cout << "----RESUMEN DIARIO DE RESERVAS----" << endl;

		if (gestorReservas == nullptr) {
			cout << "No hay gestor de reservas" << endl;
			return;
		}
		int cantidadReservas = gestorReservas->getCantidad();

		cout << "Cantidad de reservas para hoy: " << cantidadReservas << endl;

		if (cantidadReservas == 0) {
			cout << "No hay canchas reservadas" << endl;

		}
	}
	

	void GenerarListaEspera(ListaEspera* listaEspera) {
		cout << "----LISTA DE ESPERA----" << endl;
		if (listaEspera == nullptr) {
			cout << "No hay lista de espera" << endl;
			return;
		}
		int cantidadEspera = listaEspera->getCantidad();
		cout << "Cantidad de clientes en lista de espera: " << cantidadEspera << endl;

		if (cantidadEspera == 0) {
			cout << "No hay clientes en lista de espera" << endl;
			return;
		}
		listaEspera->Mostrar();
	}
	

};

