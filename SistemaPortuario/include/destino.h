#ifndef DESTINO_H
#define DESTINO_H

#include "pasajero.h"
#include "viaje.h"

#define LONGITUD_NOMBRE 64
#define LONGITUD_EMPRESA 64

/* ---------- Nodo de destino (a la vez nodo de la FIFO de destinos) ---------- */
typedef struct Destino {
    int codigo;
    char nombre[LONGITUD_NOMBRE];
    char empresa[LONGITUD_EMPRESA];
    double costo;
    ColaPasajeros colaPasajeros;   /* FIFO propia de pasajeros de este destino */
    NodoViaje *raizViajes;         /* raiz del AVL de viajes programados */
    struct Destino *siguiente;
} Destino;

/* ---------- FIFO de destinos ---------- */
typedef struct {
    Destino *frente;
    Destino *final;
    int cantidad;
} ColaDestinos;

void colaDestinos_inicializar(ColaDestinos *cola);
void colaDestinos_liberar(ColaDestinos *cola);

int colaDestinos_registrar(ColaDestinos *cola, int codigo, const char *nombre, const char *empresa, double costo);
Destino *colaDestinos_buscarPorCodigo(const ColaDestinos *cola, int codigo);
void colaDestinos_mostrarTodos(const ColaDestinos *cola);
int colaDestinos_modificar(ColaDestinos *cola, int codigo, const char *nuevoNombre, const char *nuevaEmpresa, double nuevoCosto);
int colaDestinos_contarPasajerosEnEspera(const ColaDestinos *cola, int codigo);
void colaDestinos_mostrarViajes(const ColaDestinos *cola, int codigo);
int colaDestinos_existeCodigo(const ColaDestinos *cola, int codigo);

#endif