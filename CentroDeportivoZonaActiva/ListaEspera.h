#pragma once
#include<iostream>
#include<string>
#include"Cliente.h"
#include"Cancha.h"
#include"FranjaHoraria.h"
using namespace std;
class ListaEspera{
private:
	Cliente* espera[10];
	int* canchasSolicitadas[10]; 
	int* franjasSolicitadas[10]; 
	int cantidad;
public:
	// Constructor
	ListaEspera() {
		cantidad = 0;
		for (int i = 0; i < 10; i++) {
			espera[i] = nullptr;
			canchasSolicitadas[i] = nullptr;
			franjasSolicitadas[i] = nullptr;
		}
	}
	// Encapsulador
	int getCantidad() {
		return cantidad;
	}
	// Agregar un cliente a la lista de espera
	bool agregar(Cliente* nuevoCliente, int* canchas, int* franjas) {
		if (cantidad < 10) {
			espera[cantidad] = nuevoCliente;
			canchasSolicitadas[cantidad] = canchas;
			franjasSolicitadas[cantidad] = franjas;
			cantidad++;
			return true;
		}
		return false; // ya no hay espacio
	}
	void Eliminar(int indice) {
		if (indice < 0 || indice >= cantidad) {
			return; // índice inválido
		}
		delete espera[indice]; // libera la memoria del puntero
		delete[] canchasSolicitadas[indice]; // libera la memoria del arreglo de canchas
		delete[] franjasSolicitadas[indice]; // libera la memoria del arreglo de franjas
		// Recorremos el resto para "recorrer" el hueco
		for (int i = indice; i < cantidad - 1; i++) {
			espera[i] = espera[i + 1];
			canchasSolicitadas[i] = canchasSolicitadas[i + 1];
			franjasSolicitadas[i] = franjasSolicitadas[i + 1];
		}
		espera[cantidad - 1] = nullptr;
		canchasSolicitadas[cantidad - 1] = nullptr;
		franjasSolicitadas[cantidad - 1] = nullptr;
		cantidad--;
	}
	bool promover(GestorReservas* gestorReservas) {
		if (cantidad == 0) {
			return false;
		}
		// Lógica para promover un cliente de la lista de espera
		return true;
	}
	void Mostrar() {
		cout << "----LISTA DE ESPERA----" << endl;
		if (cantidad == 0) {
			cout << "No hay clientes en lista de espera" << endl;
			return;
		}
		for (int i = 0; i < cantidad; i++) {
			cout << "Cliente: " << espera[i]->getNombre() << endl;
			cout << "Canchas solicitadas: ";
			for (int j = 0; j < 10; j++) {
				if (canchasSolicitadas[i][j] != -1) { // Asumiendo que -1 indica que no hay más canchas
					cout << canchasSolicitadas[i][j] << " ";
				}
			}
			cout << endl;
			cout << "Franjas solicitadas: ";
			for (int j = 0; j < 10; j++) {
				if (franjasSolicitadas[i][j] != -1) { // Asumiendo que -1 indica que no hay más franjas
					cout << franjasSolicitadas[i][j] << " ";
				}
			}
			cout << endl;
		}
	}
	int getCantidad() {
		return cantidad;
	}
};


