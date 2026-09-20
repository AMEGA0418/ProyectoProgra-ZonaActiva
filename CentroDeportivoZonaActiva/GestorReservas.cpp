#include "GestorReservas.h"

using namespace std;

// Definicion de la constante estatica de la clase
const int GestorReservas::MAX_RESERVAS;

GestorReservas::GestorReservas() {
    total = 0;
    consecutivo = 0;
    for (int i = 0; i < MAX_RESERVAS; i++) reservas[i] = nullptr;
}

GestorReservas::~GestorReservas() {
    for (int i = 0; i < total; i++) {
        delete reservas[i];
        reservas[i] = nullptr;
    }
}

bool GestorReservas::estaLleno() const { return total >= MAX_RESERVAS; }

Reserva* GestorReservas::crear(Cliente* cliente, Cancha* cancha, int franjaInicial,
    int cantidadFranjas, string fecha) {
    if (estaLleno()) return nullptr;
    if (cliente == nullptr || cancha == nullptr) return nullptr;
    if (!cancha->rangoValido(franjaInicial, cantidadFranjas)) return nullptr;
    if (!cancha->rangoLibre(franjaInicial, cantidadFranjas)) return nullptr;

    // Cambio de disponibilidad L -> O
    cancha->ocuparRango(franjaInicial, cantidadFranjas);

    double monto = cancha->getPrecioHora() * cantidadFranjas;
    consecutivo++;
    Reserva* nueva = new Reserva(consecutivo, cliente, cancha, franjaInicial,
        cantidadFranjas, fecha, monto);
    reservas[total] = nueva;
    total++;
    return nueva;
}

bool GestorReservas::cancelar(int numeroReserva) {
    Reserva* r = buscar(numeroReserva);
    if (r == nullptr) return false;
    if (!r->estaActiva()) return false;   // solo se cancelan las activas

    Cancha* c = r->getCancha();
    if (c != nullptr) {
        // Cambio de disponibilidad O -> L
        c->liberarRango(r->getFranjaInicial(), r->getCantidadFranjas());
    }
    r->cancelar();
    return true;
}

Reserva* GestorReservas::buscar(int numeroReserva) const {
    for (int i = 0; i < total; i++) {
        if (reservas[i] != nullptr && reservas[i]->getNumero() == numeroReserva) {
            return reservas[i];
        }
    }
    return nullptr;
}

Reserva* GestorReservas::getReserva(int indice) const {
    if (indice >= 0 && indice < total) return reservas[indice];
    return nullptr;
}

int GestorReservas::getCantidad() const { return total; }

int GestorReservas::contarActivasPorCancha(int codigoCancha) const {
    int contador = 0;
    for (int i = 0; i < total; i++) {
        Reserva* r = reservas[i];
        if (r == nullptr || !r->estaActiva() || r->getCancha() == nullptr) continue;
        if (r->getCancha()->getCodigo() == codigoCancha) contador++;
    }
    return contador;
}

int GestorReservas::contarActivasPorCliente(int idCliente) const {
    int contador = 0;
    for (int i = 0; i < total; i++) {
        Reserva* r = reservas[i];
        if (r == nullptr || !r->estaActiva() || r->getCliente() == nullptr) continue;
        if (r->getCliente()->getID() == idCliente) contador++;
    }
    return contador;
}

// Cuenta cuantas reservas activas usan una hora especifica (0 a 11)
int GestorReservas::contarActivasEnFranja(int indiceFranja) const {
    int contador = 0;
    for (int i = 0; i < total; i++) {
        Reserva* r = reservas[i];
        if (r == nullptr || !r->estaActiva()) continue;
        if (r->usaFranja(indiceFranja)) contador++;
    }
    return contador;
}

void GestorReservas::listarTodas() const {
    if (total == 0) {
        cout << "No hay reservas registradas." << endl;
        return;
    }
    cout << "----- RESERVAS REGISTRADAS (" << total << ") -----" << endl;
    for (int i = 0; i < total; i++) {
        if (reservas[i] != nullptr) {
            reservas[i]->mostrarInfo();
            cout << "-------------------------------------------" << endl;
        }
    }
}

void GestorReservas::listarPorCliente(int idCliente) const {
    bool encontro = false;
    for (int i = 0; i < total; i++) {
        Reserva* r = reservas[i];
        if (r == nullptr || r->getCliente() == nullptr) continue;
        if (r->getCliente()->getID() == idCliente) {
            r->mostrarInfo();
            cout << "-------------------------------------------" << endl;
            encontro = true;
        }
    }
    if (!encontro) cout << "El cliente no tiene reservas registradas." << endl;
}

void GestorReservas::listarPorCancha(int codigoCancha) const {
    bool encontro = false;
    for (int i = 0; i < total; i++) {
        Reserva* r = reservas[i];
        if (r == nullptr || r->getCancha() == nullptr) continue;
        if (r->getCancha()->getCodigo() == codigoCancha) {
            r->mostrarInfo();
            cout << "-------------------------------------------" << endl;
            encontro = true;
        }
    }
    if (!encontro) cout << "La cancha no tiene reservas registradas." << endl;
}