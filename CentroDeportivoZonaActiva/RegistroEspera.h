#pragma once
#include <iostream>
#include <string>

#include "Cliente.h"
#include "Cancha.h"

using namespace std;

class RegistroEspera {
private:
    int numero;        // consecutivo
    Cliente* cliente;       // puntero al cliente interesado
    Cancha* cancha;        // puntero a la cancha solicitada
    int franja;        // posicion de la franja horaria (0 a 11)
    string estado;        // "Esperando", "Asignado" o "Cancelado"

public:
    RegistroEspera();
    RegistroEspera(int numero, Cliente* cliente, Cancha* cancha, int franja);

    int getNumero() const;
    Cliente* getCliente() const;
    Cancha* getCancha() const;
    int getFranja() const;
    string getEstado() const;

    void setNumero(int nuevoNumero);
    void setCliente(Cliente* nuevoCliente);
    void setCancha(Cancha* nuevaCancha);
    void setFranja(int nuevaFranja);
    bool setEstado(string nuevoEstado);   // solo acepta los tres estados validos

    bool estaEsperando() const;
    void mostrarInfo() const;
};