/*Universidad nacional 
Fecha:09/09/2026 
Andrey David Arias PérezClase para agregar, eliminar o buscar una cancha
*/
#pragma once
#include <iostream>
#include <string>
#include "Cancha.h"
using namespace std;

class GestorCanchas {
public:
    static const int MAX_CANCHAS = 10;

private:
    Cancha** canchas;   // arreglo unidimensional dinamico de punteros a Cancha
    int total;

public:
    // Constructor
    GestorCanchas();
    ~GestorCanchas();

    // Encapsuladores
    int getCantidad() const;
    bool estaLlena() const;
    bool existeCodigo(int codigo) const;
    // Gestion de canchas
    bool agregar(Cancha* nuevaCancha);
    bool eliminar(int codigo);
    Cancha* buscar(int codigo) const;
    Cancha* getCancha(int indice) const;
    // Metodos
    bool modificarPrecio(int codigo, double nuevoPrecio);
    bool ponerMantenimiento(int codigo, int indiceFranja);
    bool quitarMantenimiento(int codigo, int indiceFranja);
    void listar() const;
    bool mostrarDisponibilidad(int codigo) const;
};