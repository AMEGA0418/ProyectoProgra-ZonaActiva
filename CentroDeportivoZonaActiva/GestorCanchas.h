// Universidad nacional
//fecha:09/09/2026
//Andrey David Arias Pérez
//Clase para agregar, eliminar o buscar una cancha

#pragma once
#include <iostream>
#include <string>
#include "Cancha.h"
using namespace  std;

class GestorCanchas {
private:
    Cancha* canchas[10];
    int total;

public:
    // Constructor
    GestorCanchas() {
        total = 0;
        for (int i = 0; i < 10; i++) {
            canchas[i] = nullptr;
        }
    }
    // Encapsulador 
    int getCantidad() {
        return total;
    }
    //Metodos
    // Agregar una cancha (mientras haya espacio)
    bool agregar(Cancha* nuevaCancha) {
        if (total < 10) {
            canchas[total] = nuevaCancha;
            total++;
            return true;
        }
        return false; // ya no hay espacio
    }

    // Eliminar una cancha por posición
    bool eliminar(int indice) {
        if (indice < 0 || indice >= total) {
            return false; // índice inválido
        }
        delete canchas[indice]; // libera la memoria del puntero

        // Recorremos el resto para "recorrer" el hueco
        for (int i = indice; i < total - 1; i++) {
            canchas[i] = canchas[i + 1];
        }
        canchas[total - 1] = nullptr;
        total--;
        return true;
    }

    // Buscar una cancha por su código/id
    Cancha* buscar(int id) {
        for (int i = 0; i < total; i++) {
            if (canchas[i]->getId() == id) {
                return canchas[i];
            }
        }
        return nullptr; // no encontrada
    }

    // Listar todas las canchas registradas
    void listar() {
        if (total == 0) {
            cout << "No hay canchas registradas." << endl;
            return;
        }
        for (int i = 0; i < total; i++) {
            cout << "Codigo: " << canchas[i]->getId()
                << " | Nombre: " << canchas[i]->getNombre()
                << " | Deporte: " << canchas[i]->getDeporte() << endl;
        }
    }

    // Poner una franja de una cancha en Mantenimiento
    void setMantenimiento(int idCancha, int indiceFranja) {
        Cancha* c = buscar(idCancha);
        if (c != nullptr) {
            c->setEstadoFranja(indiceFranja, "M");
        }
        else {
            cout << "Cancha no encontrada." << endl;
        }
    }