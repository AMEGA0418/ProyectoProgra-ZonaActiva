#pragma once
#include<iostream>
#include<string>
#include "GestorCanchas.h"
#include "GestorClientes.h"
#include "GestorReservas.h"
#include "ListaEspera.h"
using namespace std;

class Reportes {
	//Esta clase no posee aributos, ya que su función es únicamente 
	// servir como base para otras clases que generen reportes específicos.
public:
	// Constructor
	Reportes();
	//Metodos
    void canchaConMasReservas(GestorCanchas* gestorCanchas,
        GestorReservas* gestorReservas) const;

    // 2. Cliente con mayor cantidad de reservas activas (con detalle)
    void clienteConMasReservas(GestorClientes* gestorClientes,
        GestorReservas* gestorReservas) const;

    // 3. Ingreso total generado por las reservas activas (con detalle)
    void ingresoTotal(GestorReservas* gestorReservas) const;

    // 4. Porcentaje de ocupacion de cada cancha (con detalle)
    void porcentajeOcupacion(GestorCanchas* gestorCanchas) const;

    // 5. Horas con mayor y menor cantidad de reservas (con detalle)
    void horasMayorMenorDemanda(GestorReservas* gestorReservas) const;

    // Reporte adicional de apoyo: estado del listado de espera
    void resumenListaEspera(ListaEspera* listaEspera) const;
};