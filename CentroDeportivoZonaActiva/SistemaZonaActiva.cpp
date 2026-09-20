#include "SistemaZonaActiva.h"
#include <cstdlib> //para limpiar la pantalla con system("cls") o system("clear")
//Universidad Nacional de Costa Rica 
//Fecha: 17/09/26
//Samuel Morera Trigueros  
using namespace std;

// ---------------- Constructor y destructor ----------------

SistemaZonaActiva::SistemaZonaActiva() {
    gestorCanchas = new GestorCanchas();
    gestorClientes = new GestorClientes();
    gestorReservas = new GestorReservas();
    listaEspera = new ListaEspera();
    reportes = new Reportes();
    fecha = "";
}

SistemaZonaActiva::~SistemaZonaActiva() {
    delete listaEspera;      // primero los que solo guardan referencias
    delete gestorReservas;
    delete gestorClientes;
    delete gestorCanchas;
    delete reportes;
}

// ---------------- Utilidades de interfaz ----------------

// Limpia realmente la consola antes de mostrar cada menu, para que la
// interfaz se vea ordenada y no se acumule el historial de pantallas
// anteriores. cls en Windows, clear en Linux/Mac.
void SistemaZonaActiva::limpiarPantalla() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void SistemaZonaActiva::pausa() const {
    cout << endl << "Presione ENTER para continuar...";
    cin.get();
}

void SistemaZonaActiva::titulo(string texto) const {
    limpiarPantalla();
    cout << "===========================================" << endl;
    cout << "  " << texto << endl;
    cout << "  Fecha de trabajo: " << fecha << endl;
    cout << "===========================================" << endl << endl;
}

// Lee un entero validando el tipo de dato y el rango permitido
int SistemaZonaActiva::leerEntero(string mensaje, int minimo, int maximo) const {
    int valor = 0;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(10000, '\n');
            if (valor >= minimo && valor <= maximo) return valor;
            cout << "Valor fuera de rango (" << minimo << " a " << maximo << ")." << endl;
        }
        else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Debe digitar un numero entero." << endl;
        }
    }
}

// Lee un decimal validando el tipo de dato y que no sea menor al minimo
double SistemaZonaActiva::leerDecimal(string mensaje, double minimo) const {
    double valor = 0.0;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(10000, '\n');
            if (valor >= minimo) return valor;
            cout << "El valor no puede ser menor que " << minimo << "." << endl;
        }
        else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Debe digitar un numero." << endl;
        }
    }
}

string SistemaZonaActiva::leerTexto(string mensaje) const {
    string texto = "";
    while (true) {
        cout << mensaje;
        getline(cin, texto);
        if (!texto.empty()) return texto;
        cout << "El dato no puede quedar vacio." << endl;
    }
}

bool SistemaZonaActiva::confirmar(string mensaje) const {
    string respuesta;
    cout << mensaje << " (s/n): ";
    getline(cin, respuesta);
    return respuesta == "s" || respuesta == "S";
}

// ---------------- Apoyos ----------------

Cancha* SistemaZonaActiva::pedirCancha() {
    if (gestorCanchas->getCantidad() == 0) {
        cout << "No hay canchas registradas." << endl;
        return nullptr;
    }
    gestorCanchas->listar();
    int codigo = leerEntero("Codigo de la cancha: ", 1, 999999);
    Cancha* c = gestorCanchas->buscar(codigo);
    if (c == nullptr) cout << "No existe una cancha con ese codigo." << endl;
    return c;
}

Cliente* SistemaZonaActiva::pedirCliente() {
    if (gestorClientes->getCantidad() == 0) {
        cout << "No hay clientes registrados." << endl;
        return nullptr;
    }
    int id = leerEntero("Identificacion del cliente: ", 1, 999999999);
    Cliente* cl = gestorClientes->buscar(id);
    if (cl == nullptr) cout << "No existe un cliente con esa identificacion." << endl;
    return cl;
}

// Se ofrece cuando una franja solicitada esta ocupada
void SistemaZonaActiva::ofrecerListaEspera(Cliente* cliente, Cancha* cancha, int franja) {
    if (cliente == nullptr || cancha == nullptr) return;
    if (cancha->getEstadoFranja(franja) != 'O') return;

    cout << "La franja [" << franja << "] " << (8 + franja) << ":00 esta ocupada." << endl;
    if (!confirmar("Desea registrar al cliente en el listado de espera?")) return;

    ListaEspera::Resultado r = listaEspera->agregar(cliente, cancha, franja);
    switch (r) {
    case ListaEspera::OK:
        cout << "Cliente agregado al listado de espera." << endl; break;
    case ListaEspera::LISTA_LLENA:
        cout << "El listado de espera esta lleno (maximo 10)." << endl; break;
    case ListaEspera::DUPLICADO:
        cout << "Ese cliente ya esta esperando por esa cancha y franja." << endl; break;
    case ListaEspera::FRANJA_MANTENIMIENTO:
        cout << "Las franjas en mantenimiento no generan espera." << endl; break;
    case ListaEspera::FRANJA_NO_OCUPADA:
        cout << "Solo se puede esperar por franjas ocupadas." << endl; break;
    default:
        cout << "No se pudo registrar en el listado de espera." << endl; break;
    }
}

// ---------------- Menus ----------------

void SistemaZonaActiva::iniciar() {
    cout << "===========================================" << endl;
    cout << "     CENTRO DEPORTIVO ZONA ACTIVA" << endl;
    cout << "===========================================" << endl << endl;
    cout << "El sistema trabaja con una sola fecha por ejecucion." << endl;
    fecha = leerTexto("Digite la fecha de trabajo (dd/mm/aaaa): ");
    menuPrincipal();
}

void SistemaZonaActiva::menuPrincipal() {
    int opcion = 0;
    do {
        titulo("CENTRO DEPORTIVO ZONA ACTIVA");
        cout << "1. Gestion de canchas" << endl;
        cout << "2. Gestion de clientes" << endl;
        cout << "3. Gestion de reservas" << endl;
        cout << "4. Gestion de listado de espera" << endl;
        cout << "5. Reportes y estadisticas" << endl;
        cout << "6. Salir" << endl << endl;
        opcion = leerEntero("Seleccione una opcion: ", 1, 6);

        switch (opcion) {
        case 1: menuCanchas();     break;
        case 2: menuClientes();    break;
        case 3: menuReservas();    break;
        case 4: menuListaEspera(); break;
        case 5: menuReportes();    break;
        case 6:
            cout << endl << "Saliendo del sistema..." << endl;
            break;
        }
    } while (opcion != 6);
}

void SistemaZonaActiva::menuCanchas() {
    int opcion = 0;
    do {
        titulo("GESTION DE CANCHAS");
        cout << "1. Registrar una cancha" << endl;
        cout << "2. Mostrar todas las canchas" << endl;
        cout << "3. Buscar una cancha por codigo" << endl;
        cout << "4. Modificar el precio de una cancha" << endl;
        cout << "5. Mostrar la disponibilidad de una cancha" << endl;
        cout << "6. Colocar una franja en mantenimiento" << endl;
        cout << "7. Retirar el mantenimiento de una franja" << endl;
        cout << "8. Volver al menu principal" << endl << endl;
        opcion = leerEntero("Seleccione una opcion: ", 1, 8);
        cout << endl;

        if (opcion == 1) {
            if (gestorCanchas->getCantidad() >= GestorCanchas::MAX_CANCHAS) {
                cout << "No se pueden registrar mas canchas (maximo 10)." << endl;
                pausa();
                continue;
            }
            int codigo = leerEntero("Codigo unico de la cancha: ", 1, 999999);
            if (gestorCanchas->existeCodigo(codigo)) {
                cout << "Ya existe una cancha con ese codigo." << endl;
                pausa();
                continue;
            }
            string nombre = leerTexto("Nombre de la cancha: ");
            string deporte = leerTexto("Tipo de deporte: ");
            double precio = leerDecimal("Precio de alquiler por hora: ", 0.0);

            Cancha* nueva = new Cancha(codigo, nombre, deporte, precio);
            if (gestorCanchas->agregar(nueva)) {
                cout << "Cancha registrada correctamente." << endl;
            }
            else {
                cout << "No se pudo registrar la cancha." << endl;
                delete nueva;    // se libera si no entro a la coleccion
            }
            pausa();
        }
        else if (opcion == 2) {
            gestorCanchas->listar();
            pausa();
        }
        else if (opcion == 3) {
            if (gestorCanchas->getCantidad() == 0) {
                cout << "No hay canchas registradas." << endl;
            }
            else {
                int codigo = leerEntero("Codigo de la cancha a buscar: ", 1, 999999);
                Cancha* c = gestorCanchas->buscar(codigo);
                if (c != nullptr) c->mostrarInfo();
                else cout << "Busqueda sin resultado." << endl;
            }
            pausa();
        }
        else if (opcion == 4) {
            Cancha* c = pedirCancha();
            if (c != nullptr) {
                cout << "Precio actual: " << c->getPrecioHora() << endl;
                double precio = leerDecimal("Nuevo precio por hora: ", 0.0);
                if (c->setPrecioHora(precio)) cout << "Precio actualizado." << endl;
                else cout << "El precio no es valido." << endl;
            }
            pausa();
        }
        else if (opcion == 5) {
            Cancha* c = pedirCancha();
            if (c != nullptr) c->mostrarDisponibilidad();
            pausa();
        }
        else if (opcion == 6) {
            Cancha* c = pedirCancha();
            if (c != nullptr) {
                c->mostrarDisponibilidad();
                int f = leerEntero("Posicion de la franja (0 a 11): ", 0, 11);
                if (c->ponerMantenimiento(f)) {
                    cout << "Franja colocada en mantenimiento (M)." << endl;
                }
                else {
                    cout << "No se puede colocar en mantenimiento: la franja esta "
                        << "ocupada (O)." << endl;
                }
            }
            pausa();
        }
        else if (opcion == 7) {
            Cancha* c = pedirCancha();
            if (c != nullptr) {
                c->mostrarDisponibilidad();
                int f = leerEntero("Posicion de la franja (0 a 11): ", 0, 11);
                if (c->quitarMantenimiento(f)) {
                    cout << "Mantenimiento retirado. La franja quedo libre (L)." << endl;
                }
                else {
                    cout << "Esa franja no esta en mantenimiento." << endl;
                }
            }
            pausa();
        }
    } while (opcion != 8);
}

void SistemaZonaActiva::menuClientes() {
    int opcion = 0;
    do {
        titulo("GESTION DE CLIENTES");
        cout << "1. Registrar un cliente" << endl;
        cout << "2. Mostrar el listado de clientes" << endl;
        cout << "3. Buscar un cliente por identificacion" << endl;
        cout << "4. Mostrar las reservas de un cliente" << endl;
        cout << "5. Volver al menu principal" << endl << endl;
        opcion = leerEntero("Seleccione una opcion: ", 1, 5);
        cout << endl;

        if (opcion == 1) {
            if (gestorClientes->getCantidad() >= GestorClientes::MAX_CLIENTES) {
                cout << "No se pueden registrar mas clientes (maximo 100)." << endl;
                pausa();
                continue;
            }
            int id = leerEntero("Numero de identificacion: ", 1, 999999999);
            if (gestorClientes->existeID(id)) {
                cout << "Ya existe un cliente con esa identificacion." << endl;
                pausa();
                continue;
            }
            string nombre = leerTexto("Nombre completo: ");
            string telefono = leerTexto("Numero de telefono: ");
            string correo = leerTexto("Correo electronico: ");

            Cliente* nuevo = new Cliente(id, nombre, telefono, correo);
            if (gestorClientes->agregar(nuevo)) {
                cout << "Cliente registrado correctamente." << endl;
            }
            else {
                cout << "No se pudo registrar el cliente." << endl;
                delete nuevo;
            }
            pausa();
        }
        else if (opcion == 2) {
            gestorClientes->listar();
            pausa();
        }
        else if (opcion == 3) {
            Cliente* cl = pedirCliente();
            if (cl != nullptr) cl->mostrarInfo();
            pausa();
        }
        else if (opcion == 4) {
            Cliente* cl = pedirCliente();
            if (cl != nullptr) {
                cout << endl << "Reservas del cliente " << cl->getNombre() << ":" << endl;
                gestorReservas->listarPorCliente(cl->getID());
            }
            pausa();
        }
    } while (opcion != 5);
}

void SistemaZonaActiva::menuReservas() {
    int opcion = 0;
    do {
        titulo("GESTION DE RESERVAS");
        cout << "1. Registrar una reserva" << endl;
        cout << "2. Mostrar todas las reservas" << endl;
        cout << "3. Buscar una reserva por numero" << endl;
        cout << "4. Mostrar las reservas de una cancha" << endl;
        cout << "5. Cancelar una reserva" << endl;
        cout << "6. Volver al menu principal" << endl << endl;
        opcion = leerEntero("Seleccione una opcion: ", 1, 6);
        cout << endl;

        if (opcion == 1) {
            Cliente* cl = pedirCliente();
            if (cl == nullptr) { pausa(); continue; }

            Cancha* c = pedirCancha();
            if (c == nullptr) { pausa(); continue; }

            c->mostrarDisponibilidad();
            int inicio = leerEntero("Franja inicial (0 a 11): ", 0, 11);
            int maximo = Cancha::TOTAL_FRANJAS - inicio;
            int cantidad = leerEntero("Cantidad de franjas consecutivas (1 a " +
                to_string(maximo) + "): ", 1, maximo);

            int bloqueada = c->primeraFranjaNoLibre(inicio, cantidad);
            if (bloqueada != -1) {
                cout << endl << "No se puede registrar la reserva." << endl;
                cout << "La franja [" << bloqueada << "] esta en estado "
                    << c->getEstadoFranja(bloqueada) << "." << endl;
                if (c->getEstadoFranja(bloqueada) == 'O') {
                    ofrecerListaEspera(cl, c, bloqueada);
                }
                pausa();
                continue;
            }

            Reserva* nueva = gestorReservas->crear(cl, c, inicio, cantidad, fecha);
            if (nueva != nullptr) {
                cout << endl << "Reserva registrada correctamente." << endl;
                nueva->mostrarInfo();
            }
            else {
                cout << "No se pudo registrar la reserva (limite alcanzado o datos "
                    << "invalidos)." << endl;
            }
            pausa();
        }
        else if (opcion == 2) {
            gestorReservas->listarTodas();
            pausa();
        }
        else if (opcion == 3) {
            if (gestorReservas->getCantidad() == 0) {
                cout << "No hay reservas registradas." << endl;
            }
            else {
                int numero = leerEntero("Numero de reserva: ", 1, 999999);
                Reserva* r = gestorReservas->buscar(numero);
                if (r != nullptr) r->mostrarInfo();
                else cout << "Busqueda sin resultado." << endl;
            }
            pausa();
        }
        else if (opcion == 4) {
            Cancha* c = pedirCancha();
            if (c != nullptr) gestorReservas->listarPorCancha(c->getCodigo());
            pausa();
        }
        else if (opcion == 5) {
            if (gestorReservas->getCantidad() == 0) {
                cout << "No hay reservas registradas." << endl;
                pausa();
                continue;
            }
            int numero = leerEntero("Numero de reserva a cancelar: ", 1, 999999);
            Reserva* r = gestorReservas->buscar(numero);
            if (r == nullptr) {
                cout << "Busqueda sin resultado." << endl;
                pausa();
                continue;
            }
            if (!r->estaActiva()) {
                cout << "Esa reserva ya esta cancelada." << endl;
                pausa();
                continue;
            }

            Cancha* c = r->getCancha();
            int inicio = r->getFranjaInicial();
            int cantidad = r->getCantidadFranjas();

            if (gestorReservas->cancelar(numero)) {
                cout << "Reserva cancelada. Las franjas volvieron a estado L." << endl;
                // Aviso de clientes en espera por esa cancha y franja
                listaEspera->notificarLiberacion(c, inicio, cantidad);
            }
            else {
                cout << "No se pudo cancelar la reserva." << endl;
            }
            pausa();
        }
    } while (opcion != 6);
}

void SistemaZonaActiva::menuListaEspera() {
    int opcion = 0;
    do {
        titulo("GESTION DEL LISTADO DE ESPERA");
        cout << "1. Registrar un cliente en el listado de espera" << endl;
        cout << "2. Mostrar todo el listado de espera" << endl;
        cout << "3. Mostrar la espera de una cancha y franja" << endl;
        cout << "4. Cambiar el estado de un registro" << endl;
        cout << "5. Volver al menu principal" << endl << endl;
        opcion = leerEntero("Seleccione una opcion: ", 1, 5);
        cout << endl;

        if (opcion == 1) {
            Cliente* cl = pedirCliente();
            if (cl == nullptr) { pausa(); continue; }
            Cancha* c = pedirCancha();
            if (c == nullptr) { pausa(); continue; }

            c->mostrarDisponibilidad();
            int f = leerEntero("Posicion de la franja deseada (0 a 11): ", 0, 11);

            ListaEspera::Resultado r = listaEspera->agregar(cl, c, f);
            if (r == ListaEspera::OK) {
                cout << "Cliente registrado en el listado de espera." << endl;
            }
            else if (r == ListaEspera::FRANJA_NO_OCUPADA) {
                cout << "Esa franja no esta ocupada, el cliente puede reservarla "
                    << "directamente." << endl;
            }
            else if (r == ListaEspera::FRANJA_MANTENIMIENTO) {
                cout << "Las franjas en mantenimiento no generan registros de espera."
                    << endl;
            }
            else if (r == ListaEspera::DUPLICADO) {
                cout << "Ese cliente ya esta en espera por esa cancha y franja." << endl;
            }
            else if (r == ListaEspera::LISTA_LLENA) {
                cout << "El listado de espera esta lleno (maximo 10)." << endl;
            }
            else {
                cout << "No se pudo registrar en el listado de espera." << endl;
            }
            pausa();
        }
        else if (opcion == 2) {
            listaEspera->mostrar();
            pausa();
        }
        else if (opcion == 3) {
            Cancha* c = pedirCancha();
            if (c != nullptr) {
                int f = leerEntero("Posicion de la franja (0 a 11): ", 0, 11);
                listaEspera->mostrarPorCanchaFranja(c->getCodigo(), f);
            }
            pausa();
        }
        else if (opcion == 4) {
            if (listaEspera->getCantidad() == 0) {
                cout << "No hay registros en el listado de espera." << endl;
                pausa();
                continue;
            }
            listaEspera->mostrar();
            int numero = leerEntero("Numero de registro: ", 1, 999999);
            RegistroEspera* r = listaEspera->buscar(numero);
            if (r == nullptr) {
                cout << "Busqueda sin resultado." << endl;
                pausa();
                continue;
            }
            cout << "1. Esperando" << endl;
            cout << "2. Asignado" << endl;
            cout << "3. Cancelado" << endl;
            int est = leerEntero("Nuevo estado: ", 1, 3);
            string nuevo = (est == 1) ? "Esperando" : (est == 2) ? "Asignado" : "Cancelado";
            if (listaEspera->cambiarEstado(numero, nuevo)) {
                cout << "Estado actualizado a " << nuevo << "." << endl;
            }
            else {
                cout << "No se pudo cambiar el estado." << endl;
            }
            pausa();
        }
    } while (opcion != 5);
}

void SistemaZonaActiva::menuReportes() {
    int opcion = 0;
    do {
        titulo("REPORTES Y ESTADISTICAS");
        cout << "1. Cancha con mayor cantidad de reservas" << endl;
        cout << "2. Cliente con mayor cantidad de reservas" << endl;
        cout << "3. Ingreso total generado por las reservas" << endl;
        cout << "4. Porcentaje de ocupacion de cada cancha" << endl;
        cout << "5. Horas con mayor y menor cantidad de reservas" << endl;
        cout << "6. Resumen del listado de espera" << endl;
        cout << "7. Volver al menu principal" << endl << endl;
        opcion = leerEntero("Seleccione una opcion: ", 1, 7);
        cout << endl;

        switch (opcion) {
        case 1: reportes->canchaConMasReservas(gestorCanchas, gestorReservas); pausa(); break;
        case 2: reportes->clienteConMasReservas(gestorClientes, gestorReservas); pausa(); break;
        case 3: reportes->ingresoTotal(gestorReservas); pausa(); break;
        case 4: reportes->porcentajeOcupacion(gestorCanchas); pausa(); break;
        case 5: reportes->horasMayorMenorDemanda(gestorReservas); pausa(); break;
        case 6: reportes->resumenListaEspera(listaEspera); pausa(); break;
        }
    } while (opcion != 7);
}
