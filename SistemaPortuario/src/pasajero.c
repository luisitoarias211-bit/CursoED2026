#include <stdio.h>
#include <stdlib.h>
#include "pasajero.h"

void colaPasajeros_inicializar(ColaPasajeros *cola) {
    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}

void colaPasajeros_liberar(ColaPasajeros *cola) {
    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        Pasajero *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}

int tipoDocumentoValido(int tipo) {
    return tipo == CEDULA_CIUDADANIA || tipo == PASAPORTE || tipo == TARJETA_IDENTIDAD;
}

int colaPasajeros_existeDocumento(const ColaPasajeros *cola, int numeroDocumento) {
    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        if (actual->numeroDocumento == numeroDocumento) {
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

int colaPasajeros_registrar(ColaPasajeros *cola, int numeroDocumento, int tipoDocumento) {
    if (!tipoDocumentoValido(tipoDocumento)) {
        return -1; /* tipo de documento no permitido */
    }
    if (colaPasajeros_existeDocumento(cola, numeroDocumento)) {
        return -2; /* pasajero duplicado en esta cola */
    }

    Pasajero *nuevo = (Pasajero *)malloc(sizeof(Pasajero));
    if (nuevo == NULL) {
        return -3; /* fallo de memoria */
    }
    nuevo->numeroDocumento = numeroDocumento;
    nuevo->tipoDocumento = (TipoDocumento)tipoDocumento;
    nuevo->estado = EN_ESPERA;
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

Pasajero *colaPasajeros_consultarPrimero(ColaPasajeros *cola) {
    Pasajero *actual = cola->frente;
    while (actual != NULL && actual->estado == EMBARCADO) {
        actual = actual->siguiente;
    }
    return actual;
}

int colaPasajeros_embarcarPrimero(ColaPasajeros *cola) {
    Pasajero *primero = colaPasajeros_consultarPrimero(cola);
    if (primero == NULL) {
        return -1; /* no hay pasajeros en espera */
    }
    primero->estado = EMBARCADO;
    return 0;
}

void colaPasajeros_mostrarTodos(const ColaPasajeros *cola) {
    if (cola->frente == NULL) {
        printf("  (sin pasajeros registrados)\n");
        return;
    }
    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        printf("  Documento: %d | Tipo: %s | Estado: %s\n",
               actual->numeroDocumento,
               tipoDocumentoTexto(actual->tipoDocumento),
               estadoPasajeroTexto(actual->estado));
        actual = actual->siguiente;
    }
}

int colaPasajeros_contarEnEspera(const ColaPasajeros *cola) {
    int contador = 0;
    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        if (actual->estado == EN_ESPERA) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

int colaPasajeros_contarEmbarcados(const ColaPasajeros *cola) {
    int contador = 0;
    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        if (actual->estado == EMBARCADO) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

Pasajero *colaPasajeros_buscarPorDocumento(const ColaPasajeros *cola, int numeroDocumento) {
    Pasajero *actual = cola->frente;
    while (actual != NULL) {
        if (actual->numeroDocumento == numeroDocumento) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

int colaPasajeros_estaVacia(const ColaPasajeros *cola) {
    return cola->frente == NULL;
}

const char *tipoDocumentoTexto(TipoDocumento tipo) {
    switch (tipo) {
        case CEDULA_CIUDADANIA: return "Cedula de Ciudadania";
        case PASAPORTE: return "Pasaporte";
        case TARJETA_IDENTIDAD: return "Tarjeta de Identidad";
        default: return "Desconocido";
    }
}

const char *estadoPasajeroTexto(EstadoPasajero estado) {
    return estado == EMBARCADO ? "Embarcado" : "En espera";
}