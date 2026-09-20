#include "GestorClientes.h"

using namespace std;

// Definicion de la constante estatica de la clase
const int GestorClientes::MAX_CLIENTES;

GestorClientes::GestorClientes() {
    total = 0;
    for (int i = 0; i < MAX_CLIENTES; i++) clientes[i] = nullptr;
}

GestorClientes::~GestorClientes() {
    for (int i = 0; i < total; i++) {
        delete clientes[i];
        clientes[i] = nullptr;
    }
}

bool GestorClientes::estaLleno() const { return total >= MAX_CLIENTES; }

bool GestorClientes::existeID(int id) const { return buscar(id) != nullptr; }

bool GestorClientes::agregar(Cliente* nuevoCliente) {
    if (nuevoCliente == nullptr) return false;
    if (estaLleno()) return false;
    if (existeID(nuevoCliente->getID())) return false;   // identificacion duplicada
    clientes[total] = nuevoCliente;
    total++;
    return true;
}

bool GestorClientes::eliminar(int id) {
    for (int i = 0; i < total; i++) {
        if (clientes[i] != nullptr && clientes[i]->getID() == id) {
            delete clientes[i];
            for (int j = i; j < total - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            clientes[total - 1] = nullptr;
            total--;
            return true;
        }
    }
    return false;
}

Cliente* GestorClientes::buscar(int id) const {
    for (int i = 0; i < total; i++) {
        if (clientes[i] != nullptr && clientes[i]->getID() == id) return clientes[i];
    }
    return nullptr;
}

Cliente* GestorClientes::getCliente(int indice) const {
    if (indice >= 0 && indice < total) return clientes[indice];
    return nullptr;
}

int GestorClientes::getCantidad() const { return total; }

void GestorClientes::listar() const {
    if (total == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }
    cout << "----- CLIENTES REGISTRADOS (" << total << ") -----" << endl;
    for (int i = 0; i < total; i++) {
        if (clientes[i] != nullptr) clientes[i]->mostrarLinea();
    }
}
