#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destino.h"

void colaDestinos_inicializar(ColaDestinos *cola) {
    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}

void colaDestinos_liberar(ColaDestinos *cola) {
    Destino *actual = cola->frente;
    while (actual != NULL) {
        Destino *siguiente = actual->siguiente;
        colaPasajeros_liberar(&actual->colaPasajeros);
        avl_liberar(actual->raizViajes);
        free(actual);
        actual = siguiente;
    }
    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}

int colaDestinos_existeCodigo(const ColaDestinos *cola, int codigo) {
    return colaDestinos_buscarPorCodigo(cola, codigo) != NULL;
}

int colaDestinos_registrar(ColaDestinos *cola, int codigo, const char *nombre, const char *empresa) {
    if (colaDestinos_existeCodigo(cola, codigo)) {
        return -1; /* codigo duplicado */
    }

    Destino *nuevo = (Destino *)malloc(sizeof(Destino));
    if (nuevo == NULL) {
        return -2; /* fallo de memoria */
    }

    nuevo->codigo = codigo;
    strncpy(nuevo->nombre, nombre, LONGITUD_NOMBRE - 1);
    nuevo->nombre[LONGITUD_NOMBRE - 1] = '\0';
    strncpy(nuevo->empresa, empresa, LONGITUD_EMPRESA - 1);
    nuevo->empresa[LONGITUD_EMPRESA - 1] = '\0';
    colaPasajeros_inicializar(&nuevo->colaPasajeros);
    nuevo->raizViajes = NULL;
    nuevo->siguiente = NULL;

    if (cola->final == NULL) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
    cola->cantidad++;
    return 0;
}

Destino *colaDestinos_buscarPorCodigo(const ColaDestinos *cola, int codigo) {
    Destino *actual = cola->frente;
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void colaDestinos_mostrarTodos(const ColaDestinos *cola) {
    if (cola->frente == NULL) {
        printf("  (sin destinos registrados)\n");
        return;
    }
    Destino *actual = cola->frente;
    while (actual != NULL) {
        printf("  [%d] %s - Empresa: %s | Pasajeros en espera: %d | Viajes programados: %d\n",
            actual->codigo, actual->nombre, actual->empresa,
            colaPasajeros_contarEnEspera(&actual->colaPasajeros),
            avl_contarViajes(actual->raizViajes));
        actual = actual->siguiente;
    }
}

int colaDestinos_modificar(ColaDestinos *cola, int codigo, const char *nuevoNombre, const char *nuevaEmpresa) {
    Destino *destino = colaDestinos_buscarPorCodigo(cola, codigo);
    if (destino == NULL) {
        return -1; /* destino no encontrado */
    }
    if (nuevoNombre != NULL && nuevoNombre[0] != '\0') {
        strncpy(destino->nombre, nuevoNombre, LONGITUD_NOMBRE - 1);
        destino->nombre[LONGITUD_NOMBRE - 1] = '\0';
    }
    if (nuevaEmpresa != NULL && nuevaEmpresa[0] != '\0') {
        strncpy(destino->empresa, nuevaEmpresa, LONGITUD_EMPRESA - 1);
        destino->empresa[LONGITUD_EMPRESA - 1] = '\0';
    }
    return 0;
}

int colaDestinos_contarPasajerosEnEspera(const ColaDestinos *cola, int codigo) {
    Destino *destino = colaDestinos_buscarPorCodigo(cola, codigo);
    if (destino == NULL) {
        return -1;
    }
    return colaPasajeros_contarEnEspera(&destino->colaPasajeros);
}

void colaDestinos_mostrarViajes(const ColaDestinos *cola, int codigo) {
    Destino *destino = colaDestinos_buscarPorCodigo(cola, codigo);
    if (destino == NULL) {
        printf("  Destino no encontrado.\n");
        return;
    }
    if (destino->raizViajes == NULL) {
        printf("  (sin viajes programados para este destino)\n");
        return;
    }
    avl_mostrarInOrder(destino->raizViajes);
}