#pragma once
// Universidad nacional
//fecha:17/09/2026
//Andrey David Arias Pérez
// Emilia 
//Samuel Morera Trigueros
//------------MENU---------------   
#include <iostream>
#include <string>
#include "GestorCanchas.h"
#include "GestorClientes.h"
#include "GestorReservas.h"
#include "ListaEspera.h"
#include "Reportes.h"

using namespace std;

class SistemaZonaActiva {
private:
    GestorCanchas* gestorCanchas;
    GestorClientes* gestorClientes;
    GestorReservas* gestorReservas;
    ListaEspera* listaEspera;
    Reportes* reportes;
    string fecha;

public:
    SistemaZonaActiva();
    ~SistemaZonaActiva();

    void iniciar();
    void menuPrincipal();
    void menuCanchas();
    void menuClientes();
    void menuReservas();
    void menuReportes();
};
