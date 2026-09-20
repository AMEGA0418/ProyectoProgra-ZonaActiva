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
	int numero;            // consecutivo generado por el sistema
	Cliente* cliente;           // puntero al cliente asociado
	Cancha* cancha;            // puntero a la cancha asociada
	int franjaInicial;     // posicion 0 a 11
	int cantidadFranjas;   // franjas consecutivas reservadas
	string fecha;             // fecha unica de trabajo del sistema
	double monto;             // precio por hora * cantidad de franjas
	string estado;            // "Activa" o "Cancelada"
public:
    // Constructores
    Reserva();
    Reserva(int numero, Cliente* cliente, Cancha* cancha, int franjaInicial,
        int cantidadFranjas, string fecha, double monto);

    // Getters
    int getNumero() const;
    Cliente* getCliente() const;
    Cancha* getCancha() const;
    int getFranjaInicial() const;
    int getCantidadFranjas() const;
    string getFecha() const;
    double getMonto() const;
    string getEstado() const;
    bool estaActiva() const;

    // Setters
    void setNumero(int nuevoNumero);
    void setCliente(Cliente* nuevoCliente);
    void setCancha(Cancha* nuevaCancha);
    void setFranjaInicial(int nuevaFranja);
    void setCantidadFranjas(int nuevaCantidad);
    void setFecha(string nuevaFecha);
    void setMonto(double nuevoMonto);

    // Metodos de clase
    bool usaFranja(int indiceFranja) const;  // true si la franja esta dentro del bloque
    void cancelar();                         // solo cambia el estado
    void mostrarInfo() const;
};