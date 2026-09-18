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
    
    }
    void menuReservas() {
    
    }
    void menuReportes() {
    
    }
};
