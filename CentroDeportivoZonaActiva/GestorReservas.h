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
public:
    static const int MAX_RESERVAS = 120;

private:
    Reserva* reservas[MAX_RESERVAS];   // arreglo unidimensional de punteros
    int total;
    int consecutivo;              // numero de reserva generado por el sistema

public:
    GestorReservas();
    ~GestorReservas();

    // Crea la reserva si el cliente y la cancha existen, el rango de franjas es
    // valido (0 a 11, consecutivas) y todas las franjas estan libres (L).
    // Devuelve el puntero a la reserva creada o nullptr si no se pudo crear.
    Reserva* crear(Cliente* cliente, Cancha* cancha, int franjaInicial,
        int cantidadFranjas, string fecha);

    // Solo cancela reservas activas. No borra la reserva del arreglo:
    // cambia el estado a "Cancelada" y libera las franjas de la cancha.
    bool cancelar(int numeroReserva);

    Reserva* buscar(int numeroReserva) const;
    Reserva* getReserva(int indice) const;
    int getCantidad() const;
    bool estaLleno() const;

    // Conteos usados por los reportes
    int contarActivasPorCancha(int codigoCancha) const;
    int contarActivasPorCliente(int idCliente) const;
    int contarActivasEnFranja(int indiceFranja) const;

    // Listados
    void listarTodas() const;
    void listarPorCliente(int idCliente) const;
    void listarPorCancha(int codigoCancha) const;
};
