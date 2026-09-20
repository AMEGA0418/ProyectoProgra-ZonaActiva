#include "Cancha.h"

using namespace std;

// Definicion de la constante estatica de la clase
const int Cancha::TOTAL_FRANJAS;

Cancha::Cancha() {
    codigo = 0;
    nombre = "";
    deporte = "";
    precioHora = 0.0;
    for (int i = 0; i < TOTAL_FRANJAS; i++) {
        franjas[i] = FranjaHoraria(i, 'L');
    }
}

Cancha::Cancha(int codigo, string nombre, string deporte, double precioHora) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->deporte = deporte;
    this->precioHora = (precioHora < 0) ? 0.0 : precioHora;
    for (int i = 0; i < TOTAL_FRANJAS; i++) {
        franjas[i] = FranjaHoraria(i, 'L');
    }
}

int Cancha::getCodigo() const { return codigo; }
void Cancha::setCodigo(int nuevoCodigo) { codigo = nuevoCodigo; }
string Cancha::getNombre() const { return nombre; }
void Cancha::setNombre(string nuevoNombre) { nombre = nuevoNombre; }
string Cancha::getDeporte() const { return deporte; }
void Cancha::setDeporte(string nuevoDeporte) { deporte = nuevoDeporte; }
double Cancha::getPrecioHora() const { return precioHora; }

bool Cancha::setPrecioHora(double nuevoPrecio) {
    if (nuevoPrecio < 0) return false;   // no se aceptan valores negativos
    precioHora = nuevoPrecio;
    return true;
}

bool Cancha::indiceValido(int indice) const {
    return indice >= 0 && indice < TOTAL_FRANJAS;
}

FranjaHoraria Cancha::getFranja(int indice) const {
    if (indiceValido(indice)) return franjas[indice];
    return FranjaHoraria();
}

char Cancha::getEstadoFranja(int indice) const {
    if (indiceValido(indice)) return franjas[indice].getEstado();
    return ' ';
}

bool Cancha::setEstadoFranja(int indice, char estado) {
    if (!indiceValido(indice)) return false;
    return franjas[indice].setEstado(estado);
}

bool Cancha::rangoValido(int franjaInicial, int cantidad) const {
    if (cantidad <= 0) return false;
    if (franjaInicial < 0) return false;
    return (franjaInicial + cantidad) <= TOTAL_FRANJAS;
}

bool Cancha::rangoLibre(int franjaInicial, int cantidad) const {
    if (!rangoValido(franjaInicial, cantidad)) return false;
    for (int i = franjaInicial; i < franjaInicial + cantidad; i++) {
        if (!franjas[i].estaLibre()) return false;
    }
    return true;
}

// Sirve para saber cual franja bloquea la reserva y ofrecer la lista de espera
int Cancha::primeraFranjaNoLibre(int franjaInicial, int cantidad) const {
    if (!rangoValido(franjaInicial, cantidad)) return -1;
    for (int i = franjaInicial; i < franjaInicial + cantidad; i++) {
        if (!franjas[i].estaLibre()) return i;
    }
    return -1;
}

bool Cancha::ocuparRango(int franjaInicial, int cantidad) {
    if (!rangoLibre(franjaInicial, cantidad)) return false;
    for (int i = franjaInicial; i < franjaInicial + cantidad; i++) {
        franjas[i].setEstado('O');   // cambio L -> O al reservar
    }
    return true;
}

bool Cancha::liberarRango(int franjaInicial, int cantidad) {
    if (!rangoValido(franjaInicial, cantidad)) return false;
    for (int i = franjaInicial; i < franjaInicial + cantidad; i++) {
        if (franjas[i].estaOcupada()) {
            franjas[i].setEstado('L');   // cambio O -> L al cancelar
        }
    }
    return true;
}

bool Cancha::ponerMantenimiento(int indice) {
    if (!indiceValido(indice)) return false;
    if (franjas[indice].estaOcupada()) return false;  // regla: O no puede pasar a M
    return franjas[indice].setEstado('M');
}

bool Cancha::quitarMantenimiento(int indice) {
    if (!indiceValido(indice)) return false;
    if (!franjas[indice].enMantenimiento()) return false;
    return franjas[indice].setEstado('L');
}

int Cancha::contarFranjasPorEstado(char estado) const {
    int contador = 0;
    for (int i = 0; i < TOTAL_FRANJAS; i++) {
        if (franjas[i].getEstado() == estado) contador++;
    }
    return contador;
}

double Cancha::porcentajeOcupacion() const {
    double porcentaje = (contarFranjasPorEstado('O') * 100.0) / TOTAL_FRANJAS;
    // Se redondea a dos decimales para no depender de manipuladores de salida
    return ((int)(porcentaje * 100 + 0.5)) / 100.0;
}

void Cancha::mostrarInfo() const {
    cout << "Codigo: " << codigo
        << " | Nombre: " << nombre
        << " | Deporte: " << deporte
        << " | Precio por hora: " << precioHora << endl;
}

void Cancha::mostrarDisponibilidad() const {
    cout << "-------------------------------------------------" << endl;
    cout << " Disponibilidad de la cancha " << codigo << " - " << nombre << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Posicion   Hora             Estado" << endl;
    for (int i = 0; i < TOTAL_FRANJAS; i++) {
        // Se alinea la posicion a la derecha sin usar manipuladores
        string relleno = (i < 10) ? " " : "";
        cout << "   [" << relleno << i << "]     "
            << franjas[i].getRangoHora() << "    "
            << franjas[i].getEstado() << " ("
            << franjas[i].getEstadoTexto() << ")" << endl;
    }
    cout << "-------------------------------------------------" << endl;
    cout << " L = Libre   O = Ocupada   M = Mantenimiento" << endl;
    cout << "-------------------------------------------------" << endl;
}