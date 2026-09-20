#pragma once
#include <iostream>
#include <string>

#include "RegistroEspera.h"

using namespace std;

class ListaEspera {
public:
    static const int MAX_ESPERA = 10;

private:
    RegistroEspera* espera[MAX_ESPERA];   // arreglo unidimensional de 10 campos
    int cantidad;
    int consecutivo;

public:
    ListaEspera();
    ~ListaEspera();

    // Codigos de resultado de agregar(), para poder dar mensajes claros
    enum Resultado {
        OK = 0,
        LISTA_LLENA = 1,
        DATOS_INVALIDOS = 2,
        FRANJA_INVALIDA = 3,
        FRANJA_NO_OCUPADA = 4,   // solo se espera por franjas en estado O
        FRANJA_MANTENIMIENTO = 5,
        DUPLICADO = 6            // mismo cliente, cancha y franja ya esperando
    };

    // Registra un cliente en el listado de espera
    Resultado agregar(Cliente* cliente, Cancha* cancha, int franja);

    // Cambia el estado de un registro: "Esperando", "Asignado" o "Cancelado"
    bool cambiarEstado(int numeroRegistro, string nuevoEstado);

    // Elimina fisicamente un registro por posicion del arreglo
    bool eliminar(int indice);

    RegistroEspera* buscar(int numeroRegistro) const;
    RegistroEspera* getRegistro(int indice) const;
    int getCantidad() const;
    bool estaLlena() const;

    // true si ese cliente ya espera por esa misma cancha y franja
    bool existeDuplicado(int idCliente, int codigoCancha, int franja) const;

    // Cuantos clientes siguen esperando por una cancha y franja especificas
    int contarEsperando(int codigoCancha, int franja) const;

    // Listados
    void mostrar() const;
    void mostrarPorCanchaFranja(int codigoCancha, int franja) const;

    // Se llama al cancelar una reserva: informa si hay clientes esperando
    // por esa cancha en alguna de las franjas liberadas.
    void notificarLiberacion(Cancha* cancha, int franjaInicial, int cantidadFranjas) const;
};