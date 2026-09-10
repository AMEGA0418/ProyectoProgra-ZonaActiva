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

	}
};

