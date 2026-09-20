#pragma once
#include <iostream>
#include <string>
/*Universidad nacional 
Fecha:17/09/2026 
Samuel Morera Trigueros*/
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
    string fecha;          // unica fecha de trabajo por ejecucion

    // Utilidades de interfaz y validacion de datos de entrada
    void limpiarPantalla() const;
    void pausa() const;
    void titulo(string texto) const;
    int leerEntero(string mensaje, int minimo, int maximo) const;
    double leerDecimal(string mensaje, double minimo) const;
    string leerTexto(string mensaje) const;
    bool confirmar(string mensaje) const;

    // Apoyos para los menus
    Cancha* pedirCancha();    // pide codigo y devuelve la cancha o nullptr
    Cliente* pedirCliente();   // pide identificacion y devuelve el cliente o nullptr
    void ofrecerListaEspera(Cliente* cliente, Cancha* cancha, int franja);

public:
    SistemaZonaActiva();
    ~SistemaZonaActiva();

    void iniciar();          // pide la fecha de trabajo y abre el menu principal

    void menuPrincipal();
    void menuCanchas();
    void menuClientes();
    void menuReservas();
    void menuListaEspera();
    void menuReportes();
};
