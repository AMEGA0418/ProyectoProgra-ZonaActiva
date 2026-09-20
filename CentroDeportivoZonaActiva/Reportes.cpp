#include "Reportes.h"

using namespace std;

Reportes::Reportes() {}

void Reportes::canchaConMasReservas(GestorCanchas* gestorCanchas,
    GestorReservas* gestorReservas) const {
    cout << "===== CANCHA CON MAYOR CANTIDAD DE RESERVAS ACTIVAS =====" << endl;
    if (gestorCanchas == nullptr || gestorReservas == nullptr) return;
    if (gestorCanchas->getCantidad() == 0) {
        cout << "No hay canchas registradas." << endl;
        return;
    }

    int mayor = -1;
    // Detalle: cantidad de reservas activas por cada cancha
    cout << "Detalle por cancha:" << endl;
    for (int i = 0; i < gestorCanchas->getCantidad(); i++) {
        Cancha* c = gestorCanchas->getCancha(i);
        if (c == nullptr) continue;
        int activas = gestorReservas->contarActivasPorCancha(c->getCodigo());
        cout << "   Codigo " << c->getCodigo() << " - " << c->getNombre()
            << " -> " << activas << " reserva(s) activa(s)" << endl;
        if (activas > mayor) mayor = activas;
    }

    if (mayor <= 0) {
        cout << "Ninguna cancha tiene reservas activas." << endl;
        return;
    }

    cout << endl << "Resultado (puede haber empate):" << endl;
    for (int i = 0; i < gestorCanchas->getCantidad(); i++) {
        Cancha* c = gestorCanchas->getCancha(i);
        if (c == nullptr) continue;
        if (gestorReservas->contarActivasPorCancha(c->getCodigo()) == mayor) {
            c->mostrarInfo();
            cout << "   Reservas activas: " << mayor << endl;
            cout << "   Reservas asociadas:" << endl;
            gestorReservas->listarPorCancha(c->getCodigo());
        }
    }
}

void Reportes::clienteConMasReservas(GestorClientes* gestorClientes,
    GestorReservas* gestorReservas) const {
    cout << "===== CLIENTE CON MAYOR CANTIDAD DE RESERVAS ACTIVAS =====" << endl;
    if (gestorClientes == nullptr || gestorReservas == nullptr) return;
    if (gestorClientes->getCantidad() == 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    int mayor = -1;
    cout << "Detalle por cliente:" << endl;
    for (int i = 0; i < gestorClientes->getCantidad(); i++) {
        Cliente* cl = gestorClientes->getCliente(i);
        if (cl == nullptr) continue;
        int activas = gestorReservas->contarActivasPorCliente(cl->getID());
        cout << "   ID " << cl->getID() << " - " << cl->getNombre()
            << " -> " << activas << " reserva(s) activa(s)" << endl;
        if (activas > mayor) mayor = activas;
    }

    if (mayor <= 0) {
        cout << "Ningun cliente tiene reservas activas." << endl;
        return;
    }

    cout << endl << "Resultado (puede haber empate):" << endl;
    for (int i = 0; i < gestorClientes->getCantidad(); i++) {
        Cliente* cl = gestorClientes->getCliente(i);
        if (cl == nullptr) continue;
        if (gestorReservas->contarActivasPorCliente(cl->getID()) == mayor) {
            cl->mostrarLinea();
            cout << "   Reservas activas: " << mayor << endl;
            cout << "   Reservas asociadas:" << endl;
            gestorReservas->listarPorCliente(cl->getID());
        }
    }
}

void Reportes::ingresoTotal(GestorReservas* gestorReservas) const {
    cout << "===== INGRESO TOTAL GENERADO POR LAS RESERVAS ACTIVAS =====" << endl;
    if (gestorReservas == nullptr) return;

    double total = 0.0;
    int activas = 0;
    cout << "Detalle de las reservas activas:" << endl;
    for (int i = 0; i < gestorReservas->getCantidad(); i++) {
        Reserva* r = gestorReservas->getReserva(i);
        if (r == nullptr || !r->estaActiva()) continue;
        Cancha* c = r->getCancha();
        cout << "   Reserva No. " << r->getNumero()
            << " | Cancha: " << (c != nullptr ? c->getNombre() : "N/D")
            << " | Precio hora: " << (c != nullptr ? c->getPrecioHora() : 0.0)
            << " x " << r->getCantidadFranjas() << " franja(s)"
            << " = " << r->getMonto() << endl;
        total += r->getMonto();
        activas++;
    }

    if (activas == 0) {
        cout << "   No hay reservas activas." << endl;
    }
    cout << "-------------------------------------------" << endl;
    cout << "Reservas activas: " << activas << endl;
    cout << "INGRESO TOTAL: " << total << endl;
}

void Reportes::porcentajeOcupacion(GestorCanchas* gestorCanchas) const {
    cout << "===== PORCENTAJE DE OCUPACION DE CADA CANCHA =====" << endl;
    if (gestorCanchas == nullptr) return;
    if (gestorCanchas->getCantidad() == 0) {
        cout << "No hay canchas registradas." << endl;
        return;
    }

    for (int i = 0; i < gestorCanchas->getCantidad(); i++) {
        Cancha* c = gestorCanchas->getCancha(i);
        if (c == nullptr) continue;
        int ocupadas = c->contarFranjasPorEstado('O');
        int libres = c->contarFranjasPorEstado('L');
        int mantenimiento = c->contarFranjasPorEstado('M');
        cout << "Cancha " << c->getCodigo() << " - " << c->getNombre() << endl;
        cout << "   Ocupadas: " << ocupadas << " de " << Cancha::TOTAL_FRANJAS
            << " | Libres: " << libres
            << " | Mantenimiento: " << mantenimiento << endl;
        cout << "   Ocupacion: " << c->porcentajeOcupacion() << " %" << endl;
        cout << "-------------------------------------------" << endl;
    }
}

void Reportes::horasMayorMenorDemanda(GestorReservas* gestorReservas) const {
    cout << "===== HORAS CON MAYOR Y MENOR CANTIDAD DE RESERVAS =====" << endl;
    if (gestorReservas == nullptr) return;

    int conteo[Cancha::TOTAL_FRANJAS];
    int mayor = 0;
    int menor = 0;

    for (int f = 0; f < Cancha::TOTAL_FRANJAS; f++) {
        conteo[f] = gestorReservas->contarActivasEnFranja(f);
        if (f == 0) { mayor = conteo[f]; menor = conteo[f]; }
        if (conteo[f] > mayor) mayor = conteo[f];
        if (conteo[f] < menor) menor = conteo[f];
    }

    cout << "Detalle por hora:" << endl;
    for (int f = 0; f < Cancha::TOTAL_FRANJAS; f++) {
        string relleno = (f < 10) ? " " : "";
        cout << "   [" << relleno << f << "] " << (8 + f) << ":00 - "
            << (9 + f) << ":00 -> " << conteo[f] << " reserva(s)" << endl;
    }

    if (mayor == 0) {
        cout << endl << "No hay reservas activas para calcular la demanda." << endl;
        return;
    }

    cout << endl << "Hora(s) con MAYOR demanda (" << mayor << " reserva(s)): ";
    for (int f = 0; f < Cancha::TOTAL_FRANJAS; f++) {
        if (conteo[f] == mayor) cout << (8 + f) << ":00  ";
    }
    cout << endl;

    cout << "Hora(s) con MENOR demanda (" << menor << " reserva(s)): ";
    for (int f = 0; f < Cancha::TOTAL_FRANJAS; f++) {
        if (conteo[f] == menor) cout << (8 + f) << ":00  ";
    }
    cout << endl;
}

void Reportes::resumenListaEspera(ListaEspera* listaEspera) const {
    cout << "===== RESUMEN DEL LISTADO DE ESPERA =====" << endl;
    if (listaEspera == nullptr) return;
    cout << "Clientes registrados en espera: " << listaEspera->getCantidad()
        << " de " << ListaEspera::MAX_ESPERA << endl;
    listaEspera->mostrar();
}