#pragma once
// Universidad nacional
//fecha:17/09/2026
//Andrey David Arias Pérez
// Emilia 
//Samuel Morera Trigueros
//------------MENU---------------   
#include <iostream>
#include <string>
#include "GestorCanchas.h"
#include "GestorClientes.h"
#include "GestorReservas.h"
#include "ListaEspera.h"
#include "Reportes.h"

using namespace std;

class SistemaZonaActiva {
private:
    GestorCanchas* gestorCanchas;
    GestorClientes* gestorClientes;
    GestorReservas* gestorReservas;
    ListaEspera* listaEspera;
    Reportes* reportes;
    string fecha;

public:
    SistemaZonaActiva();
    ~SistemaZonaActiva();

    void iniciar();


    void menuPrincipal() {
        int opcion;
        do {
            system("cls");

            cout << "========================================"<< endl;
            cout << "     CENTRO DEPORTIVO ZONA ACTIVA" << endl;
            cout << "========================================" << endl;
            cout << "1. Gestion de canchas" << endl;
            cout << "2. Gestion de clientes" << endl;
            cout << "3. Gestion de reservas" << endl;
            cout << "4. Gestion de listado de espera" << endl;
            cout << "5. Reportes y estadisticas" << endl;
            cout << "6. Salir" << endl<< endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
            case 1: menuCanchas();   break;
            case 2: menuClientes();  break;
            case 3: menuReservas();  break; 
            case 4: menuReportes();  break;
            case 5:
                system("cls");
                cout << "\nSaliendo..."<< endl;
                break;
            default:
                cout << "\nOpcion invalida." << endl;
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
        } while (opcion != 6);
}


    void menuCanchas() {
        int opcion;
        do {
            system("cls"); 

            cout << "========================================" << endl;
            cout << "        GESTION DE CANCHAS" << endl;
            cout << "========================================" << endl << endl;
            cout << "1. Agregar cancha" << endl;
            cout << "2. Eliminar cancha" << endl;
            cout << "3. Buscar cancha por codigo" << endl;
            cout << "4. Listar canchas"<< endl;
            cout << "5. Poner franja en mantenimiento" << endl;
            cout << "6. Volver al menu principal" << endl << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max()); cout << endl;

            switch (opcion) {
            case 1: {
                int id;
                string nombre, deporte;
                cout << endl << "Codigo de la cancha: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max()); cout << endl;
                cout << "Nombre de la cancha: ";
                getline(cin, nombre);
                cout << "Deporte: ";
                getline(cin, deporte);

                Cancha* nueva = new Cancha(id, nombre, deporte);
                if (gestorCanchas->agregar(nueva)) {
                    cout << endl << "Cancha agregada correctamente" << endl;
                }
                else {
                    cout << endl << "No se pudo agregar: ya no hay espacio disponible" << endl;
                    delete nueva; // liberar si no se pudo agregar
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 2: {
                cout << endl<<"Cantidad actual de canchas: " << gestorCanchas->getCantidad() << endl;
                int indice;
                cout << "Indice a eliminar (0 a " << gestorCanchas->getCantidad() - 1 << "): ";
                cin >> indice;
                cin.ignore(numeric_limits<streamsize>::max());cout << endl;

                if (gestorCanchas->eliminar(indice)) {
                    cout << endl << "Cancha eliminada correctamente." << endl;
                }
                else {
                    cout << endl << "Indice invalido" << endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 3: {
                int id;
                cout <<endl<< "Codigo de la cancha a buscar: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max()); cout << endl;

                Cancha* c = gestorCanchas->buscar(id);
                if (c != nullptr) {
                    cout <<endl << "Encontrada -> Codigo: " << c->getId()
                        << " | Nombre: " << c->getNombre()
                        << " | Deporte: " << c->getDeporte() << endl;
                }
                else {
                    cout << endl << "No se encontro una cancha con ese codigo." << endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 4:
                cout << endl;
                gestorCanchas->listar();
                cout <<endl << "Presione ENTER para continuar...";
                cin.get();
                break;
            case 5: {
                int id, franja;
                cout <<endl << "Codigo de la cancha: ";
                cin >> id;
                cout << "Numero de franja a poner en mantenimiento: ";
                cin >> franja;
                cin.ignore(numeric_limits<streamsize>::max());cout << endl;

                gestorCanchas->setMantenimiento(id, franja);
                cout <<endl << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 6:
                break;
            default:
                cout <<endl << "Opcion invalida." << endl;
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }

        } while (opcion != 6);
    }





    void menuClientes() {

        int opcion;
        do {
            system("cls"); // Limpia pantalla en cada vuelta

            cout << "========================================"<<endl;
            cout << "        GESTION DE CLIENTES"<<endl;
            cout << "========================================"<<endl<<endl;
            cout << "1. Registrar cliente" << endl;;
            cout << "2. Eliminar cliente"<<endl;
            cout << "3. Buscar cliente por ID"<<endl;
            cout << "4. Listar clientes"<<endl;
            cout << "5. Volver al menu principal"<<endl<<endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max());
            cout << endl;

            switch (opcion) {
            case 1: {
                int id;
                string nombre,telefono, correo;
                cout <<endl<< "ID del cliente: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max());cout << endl;
                cout << "Nombre del cliente: ";
                getline(cin, nombre);
                cout << endl<<"Telefono del cliente: ";
                cin >> telefono;
                cout << "Correo del cliente: ";
                getline(cin, correo);

                Cliente* nuevo = new Cliente(id, nombre, telefono, correo);
                if (gestorClientes->agregar(nuevo)) {
                    cout <<endl<< "Cliente registrado correctamente."<<endl;
                }
                else {
                    cout <<endl<< "No se pudo registrar: ya no hay espacio disponible."<<endl;
                    delete nuevo; // liberar si no se pudo agregar
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 2: {
                cout <<endl<< "Cantidad actual de clientes: " << gestorClientes->getCantidad() << endl;
                int indice;
                cout << "Indice a eliminar (0 a " << gestorClientes->getCantidad() - 1 << "): ";
                cin >> indice;
                cin.ignore(numeric_limits<streamsize>::max());cout << endl;

                if (gestorClientes->eliminar(indice)) {
                    cout <<endl<< "Cliente eliminado correctamente."<<endl;
                }
                else {
                    cout <<endl<< "Indice invalido."<<endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 3: {
                int id;
                cout << endl<<"ID del cliente a buscar: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max());cout << endl;

                Cliente* c = gestorClientes->buscar(id);
                if (c != nullptr) {
                    cout <<endl<< "Encontrado -> ID: " << c->getID()
                        << " | Nombre: " << c->getNombre()
                        << " | Correo: " << c->getCorreo() << endl;
                }
                else {
                    cout <<endl<< "No se encontro un cliente con ese ID."<<endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 4:
                cout << endl;
                gestorClientes->listar();
                cout <<endl<< "Presione ENTER para continuar...";
                cin.get();
                break;
            case 5:
                break;
            default:
                cout << endl<<"Opcion invalida."<<endl;
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }

        } while (opcion != 5);

    }



    void menuReservas() {
        int opcion;

        do {
            system("cls"); // Limpia pantalla en cada vuelta

            cout << "========================================" << endl;
            cout << "        GESTION DE RESERVAS" << endl;
            cout << "========================================" << endl << endl;
            cout << "1. Crear reserva" << endl;
            cout << "2. Cancelar reserva" << endl;
            cout << "3. Buscar reserva por numero" << endl;
            cout << "4. Listar reservas por cliente" << endl;
            cout << "5. Listar reservas por cancha" << endl;
            cout << "6. Volver al menu principal" << endl << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max());

            switch (opcion) {
            case 1: {
                int idCliente, idCancha, franjaInicial, cantidadFranjas;
                string fecha;

                cout << endl << "ID del cliente: ";
                cin >> idCliente;
                cin.ignore(numeric_limits<streamsize>::max());

                Cliente* cliente = gestorClientes->buscar(idCliente);
                if (cliente == nullptr) {
                    cout << endl << "No existe un cliente con ese ID." << endl;
                    cout << "Presione ENTER para continuar...";
                    cin.get();
                    break;
                }

                cout << "Codigo de la cancha: ";
                cin >> idCancha;
                cin.ignore(numeric_limits<streamsize>::max());

                Cancha* cancha = gestorCanchas->buscar(idCancha);
                if (cancha == nullptr) {
                    cout << endl << "No existe una cancha con ese codigo." << endl;
                    cout << "Presione ENTER para continuar...";
                    cin.get();
                    break;
                }

                cout << "Franja inicial: ";
                cin >> franjaInicial;
                cout << "Cantidad de franjas: ";
                cin >> cantidadFranjas;
                cin.ignore(numeric_limits<streamsize>::max());
                cout << "Fecha (dd/mm/aaaa): ";
                getline(cin, fecha);

                if (gestorReservas->crear(cliente, cancha, franjaInicial, cantidadFranjas, fecha)) {
                    cout << endl << "Reserva creada correctamente." << endl;
                }
                else {
                    cout << endl << "No se pudo crear la reserva (sin espacio o datos invalidos)." << endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 2: {
                int numeroReserva;
                cout << endl << "Numero de reserva a cancelar: ";
                cin >> numeroReserva;
                cin.ignore(numeric_limits<streamsize>::max());

                if (gestorReservas->cancelar(numeroReserva)) {
                    cout << endl << "Reserva cancelada correctamente." << endl;
                }
                else {
                    cout << endl << "No se encontro una reserva con ese numero." << endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 3: {
                int numeroReserva;
                cout << endl << "Numero de reserva a buscar: ";
                cin >> numeroReserva;
                cin.ignore(numeric_limits<streamsize>::max());

                Reserva* r = gestorReservas->buscar(numeroReserva);
                if (r != nullptr) {
                    cout << endl;
                    r->mostrarInfo();
                }
                else {
                    cout << endl << "No se encontro una reserva con ese numero." << endl;
                }
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 4: {
                int idCliente;
                cout << endl << "ID del cliente: ";
                cin >> idCliente;
                cin.ignore(numeric_limits<streamsize>::max());

                cout << endl;
                gestorReservas->listarPorCliente(idCliente);
                cout << endl << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 5: {
                int idCancha;
                cout << endl << "Codigo de la cancha: ";
                cin >> idCancha;
                cin.ignore(numeric_limits<streamsize>::max());
                cout << endl;
                cout << endl;
                gestorReservas->listarPorCancha(idCancha);
                cout << endl << "Presione ENTER para continuar...";
                cin.get();
                break;
            }
            case 6:
                break;
            default:
                cout << endl << "Opcion invalida." << endl;
                cout << "Presione ENTER para continuar...";
                cin.get();
                break;
            }

        } while (opcion != 6);




    }
    void menuReportes() {
    
    }



};
