#include <stdio.h>
#include <stdlib.h>
#include "viaje.h"

/* resultado: 0 = ok, -1 = codigo duplicado, -2 = fallo de memoria */

static int maximo(int a, int b) {
    return a > b ? a : b;
}

int avl_altura(const NodoViaje *nodo) {
    return nodo == NULL ? 0 : nodo->altura;
}

static int factorBalance(const NodoViaje *nodo) {
    return nodo == NULL ? 0 : avl_altura(nodo->izquierdo) - avl_altura(nodo->derecho);
}

static NodoViaje *rotarDerecha(NodoViaje *y) {
    NodoViaje *x = y->izquierdo;
    NodoViaje *t2 = x->derecho;

    x->derecho = y;
    y->izquierdo = t2;

    y->altura = maximo(avl_altura(y->izquierdo), avl_altura(y->derecho)) + 1;
    x->altura = maximo(avl_altura(x->izquierdo), avl_altura(x->derecho)) + 1;

    return x;
}

static NodoViaje *rotarIzquierda(NodoViaje *x) {
    NodoViaje *y = x->derecho;
    NodoViaje *t2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = t2;

    x->altura = maximo(avl_altura(x->izquierdo), avl_altura(x->derecho)) + 1;
    y->altura = maximo(avl_altura(y->izquierdo), avl_altura(y->derecho)) + 1;

    return y;
}

NodoViaje *avl_insertar(NodoViaje *raiz, int codigoViaje, int capacidadMaxima, int *resultado) {
    if (raiz == NULL) {
        NodoViaje *nuevo = (NodoViaje *)malloc(sizeof(NodoViaje));
        if (nuevo == NULL) {
            *resultado = -2;
            return NULL;
        }
        nuevo->codigoViaje = codigoViaje;
        nuevo->capacidadMaxima = capacidadMaxima;
        nuevo->pasajerosEmbarcados = 0;
        nuevo->altura = 1;
        nuevo->izquierdo = NULL;
        nuevo->derecho = NULL;
        *resultado = 0;
        return nuevo;
    }

    if (codigoViaje < raiz->codigoViaje) {
        raiz->izquierdo = avl_insertar(raiz->izquierdo, codigoViaje, capacidadMaxima, resultado);
    } else if (codigoViaje > raiz->codigoViaje) {
        raiz->derecho = avl_insertar(raiz->derecho, codigoViaje, capacidadMaxima, resultado);
    } else {
        *resultado = -1; /* codigo de viaje duplicado */
        return raiz;
    }

    if (*resultado != 0) {
        return raiz;
    }

    raiz->altura = 1 + maximo(avl_altura(raiz->izquierdo), avl_altura(raiz->derecho));
    int balance = factorBalance(raiz);

    /* Caso izquierda-izquierda */
    if (balance > 1 && codigoViaje < raiz->izquierdo->codigoViaje) {
        return rotarDerecha(raiz);
    }
    /* Caso derecha-derecha */
    if (balance < -1 && codigoViaje > raiz->derecho->codigoViaje) {
        return rotarIzquierda(raiz);
    }
    /* Caso izquierda-derecha */
    if (balance > 1 && codigoViaje > raiz->izquierdo->codigoViaje) {
        raiz->izquierdo = rotarIzquierda(raiz->izquierdo);
        return rotarDerecha(raiz);
    }
    /* Caso derecha-izquierda */
    if (balance < -1 && codigoViaje < raiz->derecho->codigoViaje) {
        raiz->derecho = rotarDerecha(raiz->derecho);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

NodoViaje *avl_buscar(NodoViaje *raiz, int codigoViaje) {
    if (raiz == NULL || raiz->codigoViaje == codigoViaje) {
        return raiz;
    }
    if (codigoViaje < raiz->codigoViaje) {
        return avl_buscar(raiz->izquierdo, codigoViaje);
    }
    return avl_buscar(raiz->derecho, codigoViaje);
}

void avl_mostrarInOrder(const NodoViaje *raiz) {
    if (raiz == NULL) {
        return;
    }
    avl_mostrarInOrder(raiz->izquierdo);
    printf("  Viaje %d | Capacidad maxima: %d | Embarcados: %d | Altura nodo: %d\n",
           raiz->codigoViaje, raiz->capacidadMaxima, raiz->pasajerosEmbarcados, raiz->altura);
    avl_mostrarInOrder(raiz->derecho);
}

void avl_liberar(NodoViaje *raiz) {
    if (raiz == NULL) {
        return;
    }
    avl_liberar(raiz->izquierdo);
    avl_liberar(raiz->derecho);
    free(raiz);
}

int avl_contarViajes(const NodoViaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + avl_contarViajes(raiz->izquierdo) + avl_contarViajes(raiz->derecho);
}

long avl_sumarEmbarcados(const NodoViaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return raiz->pasajerosEmbarcados + avl_sumarEmbarcados(raiz->izquierdo) + avl_sumarEmbarcados(raiz->derecho);
}

void avl_actualizarEmbarcados(NodoViaje *raiz, int codigoViaje, int delta) {
    NodoViaje *nodo = avl_buscar(raiz, codigoViaje);
    if (nodo != NULL) {
        nodo->pasajerosEmbarcados += delta;
    }
}
