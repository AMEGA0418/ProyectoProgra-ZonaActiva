#include "RegistroEspera.h"

using namespace std;

RegistroEspera::RegistroEspera()
    : numero(0), cliente(nullptr), cancha(nullptr), franja(0), estado("Esperando") {}

RegistroEspera::RegistroEspera(int numero, Cliente* cliente, Cancha* cancha, int franja)
    : numero(numero), cliente(cliente), cancha(cancha), franja(franja),
    estado("Esperando") {}

int RegistroEspera::getNumero() const { return numero; }
Cliente* RegistroEspera::getCliente() const { return cliente; }
Cancha* RegistroEspera::getCancha() const { return cancha; }
int RegistroEspera::getFranja() const { return franja; }
string RegistroEspera::getEstado() const { return estado; }

void RegistroEspera::setNumero(int nuevoNumero) { numero = nuevoNumero; }
void RegistroEspera::setCliente(Cliente* nuevoCliente) { cliente = nuevoCliente; }
void RegistroEspera::setCancha(Cancha* nuevaCancha) { cancha = nuevaCancha; }
void RegistroEspera::setFranja(int nuevaFranja) { franja = nuevaFranja; }

bool RegistroEspera::setEstado(string nuevoEstado) {
    if (nuevoEstado == "Esperando" || nuevoEstado == "Asignado" ||
        nuevoEstado == "Cancelado") {
        estado = nuevoEstado;
        return true;
    }
    return false;
}

bool RegistroEspera::estaEsperando() const { return estado == "Esperando"; }

void RegistroEspera::mostrarInfo() const {
    cout << "No. " << numero
        << " | Cliente: " << (cliente != nullptr ? cliente->getNombre() : "N/D")
        << " (ID " << (cliente != nullptr ? cliente->getID() : 0) << ")" << endl;
    cout << "      Cancha: " << (cancha != nullptr ? cancha->getNombre() : "N/D")
        << " (Codigo " << (cancha != nullptr ? cancha->getCodigo() : 0) << ")"
        << " | Franja: [" << franja << "] " << (8 + franja) << ":00 - "
        << (9 + franja) << ":00" << endl;
    cout << "      Estado: " << estado << endl;
}