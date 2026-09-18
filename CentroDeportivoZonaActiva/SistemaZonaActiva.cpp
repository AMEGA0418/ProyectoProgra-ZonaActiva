#include "SistemaZonaActiva.h"




//Universidad Nacional de Costa Rica 
//Fecha: 17/09/26
//Samuel Morera Trigueros  
SistemaZonaActiva::SistemaZonaActiva() {
    gestorCanchas = new GestorCanchas();
    gestorClientes = new GestorClientes();
    gestorReservas = new GestorReservas();
    listaEspera = new ListaEspera();
    reportes = new Reportes();
    fecha = "";
}

SistemaZonaActiva::~SistemaZonaActiva() {
    delete reportes;
    delete listaEspera;
    delete gestorReservas;
    delete gestorClientes;
    delete gestorCanchas;
}

void SistemaZonaActiva::iniciar() {
    cout << "====================================" << endl;
    cout << "       SISTEMA ZONA ACTIVA" << endl;
    cout << "====================================" << endl;
    cout << "Ingrese la fecha de trabajo (dd/mm/aaaa): ";
    cin >> fecha;

    menuPrincipal();
}

void SistemaZonaActiva::menuPrincipal() {
    int opcion;

    do {
        cout << "--------MENU PRINCIPAL--------" << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "1. Gestion de canchas" << endl;
        cout << "2. Gestion de clientes" << endl;
        cout << "3. Gestion de reservas" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuCanchas();
            break;
        case 2:
            menuClientes();
            break;
        case 3:
            menuReservas();
            break;
        case 4:
            menuReportes();
            break;
        case 5:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 5);
}

void SistemaZonaActiva::menuCanchas() {
    int opcion;

    do {
        cout << "------MENU CANCHAS------" << endl;
        cout << "1. Agregar cancha" << endl;
        cout << "2. Listar canchas" << endl;
        cout << "3. Mostrar disponibilidad" << endl;
        cout << "4. Poner franja en mantenimiento" << endl;
        cout << "5. Eliminar cancha" << endl;
        cout << "6. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            string nombre;
            string deporte;

            cout << "ID de la cancha: ";
            cin >> id;

            if (gestorCanchas->buscar(id) != nullptr) {
                cout << "Ya existe una cancha con ese ID." << endl;
                continue;
            }

            cout << "Nombre de la cancha: ";
            cin >> ws;
            getline(cin, nombre);

            cout << "Deporte: ";
            getline(cin, deporte);

            Cancha* nuevaCancha = new Cancha(id, nombre, deporte);

            if (gestorCanchas->agregar(nuevaCancha)) {
                cout << "Cancha agregada correctamente." << endl;
            }
            else {
                cout << "No hay espacio para mas canchas." << endl;
                delete nuevaCancha;
            }
        }
        else if (opcion == 2) {
            gestorCanchas->listar();
        }
        else if (opcion == 3) {
            int id;
            cout << "ID de la cancha: ";
            cin >> id;

            Cancha* cancha = gestorCanchas->buscar(id);
            if (cancha != nullptr) {
                cancha->mostrarDisponibilidad();
            }
            else {
                cout << "Cancha no encontrada." << endl;
            }
        }
        else if (opcion == 4) {
            int idCancha;
            int franja;

            cout << "ID de la cancha: ";
            cin >> idCancha;
            cout << "Indice de franja (0 a 11): ";
            cin >> franja;

            if (franja < 0 || franja > 11) {
                cout << "Franja invalida." << endl;
            }
            else {
                gestorCanchas->setMantenimiento(idCancha, franja);
                cout << "Operacion realizada." << endl;
            }
        }
        else if (opcion == 5) {
            int id;
            cout << "ID de la cancha a eliminar: ";
            cin >> id;

            int indice = -1;
            for (int i = 0; i < gestorCanchas->getCantidad(); i++) {
                Cancha* cancha = gestorCanchas->getCancha(i);
                if (cancha != nullptr && cancha->getId() == id) {
                    indice = i;
                    break;
                }
            }

            if (indice != -1 && gestorCanchas->eliminar(indice)) {
                cout << "Cancha eliminada correctamente." << endl;
            }
            else {
                cout << "Cancha no encontrada." << endl;
            }
        }
        else if (opcion != 6) {
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 6);
}
void SistemaZonaActiva::menuClientes() {
    int opcion;

    do {
        cout << "--------MENU CLIENTES--------" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Listar clientes" << endl;
        cout << "3. Buscar cliente" << endl;
        cout << "4. Eliminar cliente" << endl;
        cout << "5. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            string nombre;
            string telefono;
            string correo;

            cout << "ID del cliente: ";
            cin >> id;

            if (gestorClientes->buscar(id) != nullptr) {
                cout << "Ya existe un cliente con ese ID." << endl;
                continue;
            }

            cout << "Nombre: ";
            cin >> ws;
            getline(cin, nombre);

            cout << "Telefono: ";
            getline(cin, telefono);

            cout << "Correo: ";
            getline(cin, correo);

            Cliente* nuevoCliente = new Cliente(id, nombre, telefono, correo);

            if (gestorClientes->agregar(nuevoCliente)) {
                cout << "Cliente agregado correctamente." << endl;
            }
            else {
                cout << "No hay espacio para mas clientes." << endl;
                delete nuevoCliente;
            }
        }
        else if (opcion == 2) {
            gestorClientes->listar();
        }
        else if (opcion == 3) {
            int id;
            cout << "ID del cliente: ";
            cin >> id;

            Cliente* cliente = gestorClientes->buscar(id);
            if (cliente != nullptr) {
                cliente->mostrarInfo();
            }
            else {
                cout << "Cliente no encontrado." << endl;
            }
        }
        else if (opcion == 4) {
            int id;
            cout << "ID del cliente a eliminar: ";
            cin >> id;

            int indice = -1;
            for (int i = 0; i < gestorClientes->getCantidad(); i++) {
                Cliente* cliente = gestorClientes->getCliente(i);
                if (cliente != nullptr && cliente->getID() == id) {
                    indice = i;
                    break;
                }
            }

            if (indice != -1 && gestorClientes->eliminar(indice)) {
                cout << "Cliente eliminado correctamente." << endl;
            }
            else {
                cout << "Cliente no encontrado." << endl;
            }
        }
        else if (opcion != 5) {
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 5);
}
void SistemaZonaActiva::menuReservas() {

}

void SistemaZonaActiva::menuReportes() {

}