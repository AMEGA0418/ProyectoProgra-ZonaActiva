#include "ListaEspera.h"

using namespace std;

// Definicion de la constante estatica de la clase
const int ListaEspera::MAX_ESPERA;

ListaEspera::ListaEspera() {
    cantidad = 0;
    consecutivo = 0;
    for (int i = 0; i < MAX_ESPERA; i++) espera[i] = nullptr;
}

ListaEspera::~ListaEspera() {
    for (int i = 0; i < cantidad; i++) {
        delete espera[i];       // solo se borra el registro, no el cliente ni la cancha
        espera[i] = nullptr;
    }
}

bool ListaEspera::estaLlena() const { return cantidad >= MAX_ESPERA; }

int ListaEspera::getCantidad() const { return cantidad; }

bool ListaEspera::existeDuplicado(int idCliente, int codigoCancha, int franja) const {
    for (int i = 0; i < cantidad; i++) {
        RegistroEspera* r = espera[i];
        if (r == nullptr || !r->estaEsperando()) continue;
        if (r->getCliente() == nullptr || r->getCancha() == nullptr) continue;
        if (r->getCliente()->getID() == idCliente &&
            r->getCancha()->getCodigo() == codigoCancha &&
            r->getFranja() == franja) {
            return true;
        }
    }
    return false;
}

ListaEspera::Resultado ListaEspera::agregar(Cliente* cliente, Cancha* cancha, int franja) {
    if (cliente == nullptr || cancha == nullptr) return DATOS_INVALIDOS;
    if (!cancha->indiceValido(franja))           return FRANJA_INVALIDA;

    char estadoFranja = cancha->getEstadoFranja(franja);
    if (estadoFranja == 'M') return FRANJA_MANTENIMIENTO;  // M no genera espera
    if (estadoFranja != 'O') return FRANJA_NO_OCUPADA;     // solo se espera por O

    if (existeDuplicado(cliente->getID(), cancha->getCodigo(), franja)) return DUPLICADO;
    if (estaLlena()) return LISTA_LLENA;

    consecutivo++;
    espera[cantidad] = new RegistroEspera(consecutivo, cliente, cancha, franja);
    cantidad++;
    return OK;
}

bool ListaEspera::cambiarEstado(int numeroRegistro, string nuevoEstado) {
    RegistroEspera* r = buscar(numeroRegistro);
    if (r == nullptr) return false;
    return r->setEstado(nuevoEstado);
}

bool ListaEspera::eliminar(int indice) {
    if (indice < 0 || indice >= cantidad) return false;
    delete espera[indice];
    for (int i = indice; i < cantidad - 1; i++) {   // se corre el hueco
        espera[i] = espera[i + 1];
    }
    espera[cantidad - 1] = nullptr;
    cantidad--;
    return true;
}

RegistroEspera* ListaEspera::buscar(int numeroRegistro) const {
    for (int i = 0; i < cantidad; i++) {
        if (espera[i] != nullptr && espera[i]->getNumero() == numeroRegistro) {
            return espera[i];
        }
    }
    return nullptr;
}

RegistroEspera* ListaEspera::getRegistro(int indice) const {
    if (indice >= 0 && indice < cantidad) return espera[indice];
    return nullptr;
}

int ListaEspera::contarEsperando(int codigoCancha, int franja) const {
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        RegistroEspera* r = espera[i];
        if (r == nullptr || !r->estaEsperando() || r->getCancha() == nullptr) continue;
        if (r->getCancha()->getCodigo() == codigoCancha && r->getFranja() == franja) {
            contador++;
        }
    }
    return contador;
}

void ListaEspera::mostrar() const {
    cout << "----- LISTADO DE ESPERA (" << cantidad << " de " << MAX_ESPERA
        << ") -----" << endl;
    if (cantidad == 0) {
        cout << "No hay clientes en el listado de espera." << endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        if (espera[i] != nullptr) {
            espera[i]->mostrarInfo();
            cout << "-------------------------------------------" << endl;
        }
    }
}

void ListaEspera::mostrarPorCanchaFranja(int codigoCancha, int franja) const {
    cout << "----- ESPERA PARA LA CANCHA " << codigoCancha
        << " EN LA FRANJA [" << franja << "] "
        << (8 + franja) << ":00 - " << (9 + franja) << ":00 -----" << endl;
    bool encontro = false;
    for (int i = 0; i < cantidad; i++) {
        RegistroEspera* r = espera[i];
        if (r == nullptr || r->getCancha() == nullptr) continue;
        if (r->getCancha()->getCodigo() == codigoCancha && r->getFranja() == franja) {
            r->mostrarInfo();
            cout << "-------------------------------------------" << endl;
            encontro = true;
        }
    }
    if (!encontro) {
        cout << "No hay clientes esperando por esa cancha y franja." << endl;
    }
}

// Aviso que se muestra cuando se cancela una reserva
void ListaEspera::notificarLiberacion(Cancha* cancha, int franjaInicial,
    int cantidadFranjas) const {
    if (cancha == nullptr) return;
    bool hayAvisos = false;

    for (int f = franjaInicial; f < franjaInicial + cantidadFranjas; f++) {
        int enEspera = contarEsperando(cancha->getCodigo(), f);
        if (enEspera > 0) {
            if (!hayAvisos) {
                cout << endl << "*** AVISO: hay clientes esperando por franjas "
                    << "que acaban de liberarse ***" << endl;
                hayAvisos = true;
            }
            cout << "Franja [" << f << "] " << (8 + f) << ":00 - " << (9 + f)
                << ":00 -> " << enEspera << " cliente(s) en espera:" << endl;
            for (int i = 0; i < cantidad; i++) {
                RegistroEspera* r = espera[i];
                if (r == nullptr || !r->estaEsperando() || r->getCancha() == nullptr) continue;
                if (r->getCancha()->getCodigo() == cancha->getCodigo() &&
                    r->getFranja() == f && r->getCliente() != nullptr) {
                    cout << "   - Registro No. " << r->getNumero()
                        << " | " << r->getCliente()->getNombre()
                        << " | Tel: " << r->getCliente()->getTelefono() << endl;
                }
            }
        }
    }
    if (!hayAvisos) {
        cout << "No hay clientes en espera por esas franjas." << endl;
    }
}