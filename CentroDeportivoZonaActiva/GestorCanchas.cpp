#include "GestorCanchas.h"

using namespace std;

// Definicion de la constante estatica de la clase
const int GestorCanchas::MAX_CANCHAS;

// El arreglo de punteros se reserva en memoria dinamica
GestorCanchas::GestorCanchas() {
    canchas = new Cancha * [MAX_CANCHAS];
    total = 0;
    for (int i = 0; i < MAX_CANCHAS; i++) {
        canchas[i] = nullptr;
    }
}

// Se liberan las canchas y luego el arreglo dinamico
GestorCanchas::~GestorCanchas() {
    for (int i = 0; i < total; i++) {
        delete canchas[i];
        canchas[i] = nullptr;
    }
    delete[] canchas;
    canchas = nullptr;
}

bool GestorCanchas::estaLlena() const { return total >= MAX_CANCHAS; }

bool GestorCanchas::existeCodigo(int codigo) const {
    return buscar(codigo) != nullptr;
}

bool GestorCanchas::agregar(Cancha* nuevaCancha) {
    if (nuevaCancha == nullptr) return false;
    if (estaLlena()) return false;
    if (existeCodigo(nuevaCancha->getCodigo())) return false;  // no se repiten codigos
    canchas[total] = nuevaCancha;
    total++;
    return true;
}

bool GestorCanchas::eliminar(int codigo) {
    for (int i = 0; i < total; i++) {
        if (canchas[i] != nullptr && canchas[i]->getCodigo() == codigo) {
            delete canchas[i];
            for (int j = i; j < total - 1; j++) {   // se corre el hueco
                canchas[j] = canchas[j + 1];
            }
            canchas[total - 1] = nullptr;
            total--;
            return true;
        }
    }
    return false;
}

Cancha* GestorCanchas::buscar(int codigo) const {
    for (int i = 0; i < total; i++) {
        if (canchas[i] != nullptr && canchas[i]->getCodigo() == codigo) {
            return canchas[i];
        }
    }
    return nullptr;
}

Cancha* GestorCanchas::getCancha(int indice) const {
    if (indice >= 0 && indice < total) return canchas[indice];
    return nullptr;
}

int GestorCanchas::getCantidad() const { return total; }

bool GestorCanchas::modificarPrecio(int codigo, double nuevoPrecio) {
    Cancha* c = buscar(codigo);
    if (c == nullptr) return false;
    return c->setPrecioHora(nuevoPrecio);
}

bool GestorCanchas::ponerMantenimiento(int codigo, int indiceFranja) {
    Cancha* c = buscar(codigo);
    if (c == nullptr) return false;
    return c->ponerMantenimiento(indiceFranja);
}

bool GestorCanchas::quitarMantenimiento(int codigo, int indiceFranja) {
    Cancha* c = buscar(codigo);
    if (c == nullptr) return false;
    return c->quitarMantenimiento(indiceFranja);
}

void GestorCanchas::listar() const {
    if (total == 0) {
        cout << "No hay canchas registradas." << endl;
        return;
    }
    cout << "----- CANCHAS REGISTRADAS (" << total << ") -----" << endl;
    for (int i = 0; i < total; i++) {
        if (canchas[i] != nullptr) canchas[i]->mostrarInfo();
    }
}

bool GestorCanchas::mostrarDisponibilidad(int codigo) const {
    Cancha* c = buscar(codigo);
    if (c == nullptr) return false;
    c->mostrarDisponibilidad();
    return true;
}