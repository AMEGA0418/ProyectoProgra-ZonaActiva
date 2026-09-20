#include "FranjaHoraria.h"

using namespace std;

FranjaHoraria::FranjaHoraria() {
    numero = 0;
    estado = 'L';
}

FranjaHoraria::FranjaHoraria(int numero, char estado) {
    this->numero = numero;
    this->estado = 'L';
    setEstado(estado);
}

int FranjaHoraria::getNumero() const { return numero; }

void FranjaHoraria::setNumero(int nuevoNumero) { numero = nuevoNumero; }

char FranjaHoraria::getEstado() const { return estado; }

// Solo se aceptan los tres estados validos del enunciado
bool FranjaHoraria::setEstado(char nuevoEstado) {
    if (nuevoEstado == 'L' || nuevoEstado == 'O' || nuevoEstado == 'M') {
        estado = nuevoEstado;
        return true;
    }
    return false;
}

bool FranjaHoraria::estaLibre() const { return estado == 'L'; }
bool FranjaHoraria::estaOcupada() const { return estado == 'O'; }
bool FranjaHoraria::enMantenimiento() const { return estado == 'M'; }

int FranjaHoraria::getHoraInicio() const { return 8 + numero; }
int FranjaHoraria::getHoraFin() const { return 9 + numero; }

// Arma el texto de la hora agregando el cero a la izquierda cuando hace falta
string FranjaHoraria::getRangoHora() const {
    int inicio = getHoraInicio();
    int fin = getHoraFin();
    string textoInicio = "";
    string textoFin = "";

    if (inicio < 10) textoInicio = "0";
    textoInicio = textoInicio + to_string(inicio);

    if (fin < 10) textoFin = "0";
    textoFin = textoFin + to_string(fin);

    return textoInicio + ":00 - " + textoFin + ":00";
}

string FranjaHoraria::getEstadoTexto() const {
    if (estado == 'L') return "Libre";
    if (estado == 'O') return "Ocupada";
    if (estado == 'M') return "Mantenimiento";
    return "Desconocido";
}