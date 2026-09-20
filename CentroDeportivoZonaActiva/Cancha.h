//Universidad nacional
//fecha:07/09/2026
//Andrey David Arias Pérez
//Clase para crear como tal la cancha 

#pragma once
#include <iostream>
#include <string>
#include"FranjaHoraria.h"

using namespace std;

class Cancha {
public:
	static const int TOTAL_FRANJAS = 12;

private:
	int codigo;       // codigo unico de la cancha
	string nombre;
	string deporte;
	double precioHora;   // precio de alquiler por hora
	FranjaHoraria franjas[TOTAL_FRANJAS];  // arreglo unidimensional de 12 posiciones

public:
    // Constructores
    Cancha();
    Cancha(int codigo, string nombre, string deporte, double precioHora);

    // Getters y setters
    int getCodigo() const;
    void setCodigo(int nuevoCodigo);
    string getNombre() const;
    void setNombre(string nuevoNombre);
    string getDeporte() const;
    void setDeporte(string nuevoDeporte);
    double getPrecioHora() const;
    bool setPrecioHora(double nuevoPrecio);   // false si el precio es negativo

    // Manejo del arreglo de franjas
    bool indiceValido(int indice) const;
    FranjaHoraria getFranja(int indice) const;
    char          getEstadoFranja(int indice) const; // ' ' si el indice es invalido
    bool setEstadoFranja(int indice, char estado);

    // Consultas sobre rangos de franjas consecutivas
    bool rangoValido(int franjaInicial, int cantidad) const;
    bool rangoLibre(int franjaInicial, int cantidad) const;
    int primeraFranjaNoLibre(int franjaInicial, int cantidad) const; // -1 si todas libres

    // Reservar / liberar un bloque de franjas consecutivas
    bool ocuparRango(int franjaInicial, int cantidad);
    bool liberarRango(int franjaInicial, int cantidad);

    // Mantenimiento: no se puede poner M sobre una franja ocupada (O)
    bool ponerMantenimiento(int indice);
    bool quitarMantenimiento(int indice);   // devuelve la franja a Libre

    // Estadisticas de la cancha
    int contarFranjasPorEstado(char estado) const;
    double porcentajeOcupacion() const;     // franjas ocupadas sobre 12, en porcentaje

    // Salidas por consola
    void mostrarInfo() const;
    void mostrarDisponibilidad() const;
};