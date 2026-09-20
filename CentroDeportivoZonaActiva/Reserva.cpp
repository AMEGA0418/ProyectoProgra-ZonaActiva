#include "Reserva.h"

using namespace std;

Reserva::Reserva()
    : numero(0), cliente(nullptr), cancha(nullptr), franjaInicial(0),
    cantidadFranjas(0), fecha(""), monto(0.0), estado("Activa") {}

Reserva::Reserva(int numero, Cliente* cliente, Cancha* cancha, int franjaInicial,
    int cantidadFranjas, string fecha, double monto)
    : numero(numero), cliente(cliente), cancha(cancha), franjaInicial(franjaInicial),
    cantidadFranjas(cantidadFranjas), fecha(fecha), monto(monto), estado("Activa") {}

int Reserva::getNumero() const { return numero; }
Cliente* Reserva::getCliente() const { return cliente; }
Cancha* Reserva::getCancha() const { return cancha; }
int Reserva::getFranjaInicial() const { return franjaInicial; }
int Reserva::getCantidadFranjas() const { return cantidadFranjas; }
string Reserva::getFecha() const { return fecha; }
double Reserva::getMonto() const { return monto; }
string Reserva::getEstado() const { return estado; }
bool Reserva::estaActiva() const { return estado == "Activa"; }

void Reserva::setNumero(int nuevoNumero) { numero = nuevoNumero; }
void Reserva::setCliente(Cliente* nuevoCliente) { cliente = nuevoCliente; }
void Reserva::setCancha(Cancha* nuevaCancha) { cancha = nuevaCancha; }
void Reserva::setFranjaInicial(int nuevaFranja) { franjaInicial = nuevaFranja; }
void Reserva::setCantidadFranjas(int nuevaCantidad) { cantidadFranjas = nuevaCantidad; }
void Reserva::setFecha(string nuevaFecha) { fecha = nuevaFecha; }
void Reserva::setMonto(double nuevoMonto) { monto = nuevoMonto; }

bool Reserva::usaFranja(int indiceFranja) const {
    return indiceFranja >= franjaInicial &&
        indiceFranja < franjaInicial + cantidadFranjas;
}

void Reserva::cancelar() { estado = "Cancelada"; }

void Reserva::mostrarInfo() const {
    cout << "Reserva No. " << numero
        << " Estado: " << estado << endl;
    cout << "   Cliente: "
        << (cliente != nullptr ? cliente->getNombre() : "N/D")
        << " (ID " << (cliente != nullptr ? cliente->getID() : 0) << ")" << endl;
    cout << "   Cancha: "
        << (cancha != nullptr ? cancha->getNombre() : "N/D")
        << " (Codigo " << (cancha != nullptr ? cancha->getCodigo() : 0) << ")" << endl;
    cout << "   Franja inicial: [" << franjaInicial << "] "
        << (8 + franjaInicial) << ":00"
        << " Franjas: " << cantidadFranjas
        << " Hasta las " << (8 + franjaInicial + cantidadFranjas) << ":00" << endl;
    cout << " Fecha: " << fecha
        << " Monto: " << monto << endl;
}