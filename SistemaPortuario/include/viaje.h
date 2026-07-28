#ifndef VIAJE_H
#define VIAJE_H

/* ---------- Nodo del arbol AVL de viajes programados ---------- */
typedef struct NodoViaje {
    int codigoViaje;            /* clave del arbol */
    int capacidadMaxima;
    int pasajerosEmbarcados;    /* usado en estadisticas */
    int altura;                 /* necesaria para el balanceo AVL */
    struct NodoViaje *izquierdo;
    struct NodoViaje *derecho;
} NodoViaje;

/* ---------- Operaciones del AVL ---------- */
NodoViaje *avl_insertar(NodoViaje *raiz, int codigoViaje, int capacidadMaxima, int *resultado);
NodoViaje *avl_buscar(NodoViaje *raiz, int codigoViaje);
void avl_mostrarInOrder(const NodoViaje *raiz);
void avl_liberar(NodoViaje *raiz);
int avl_contarViajes(const NodoViaje *raiz);
int avl_altura(const NodoViaje *nodo);

/* estadisticas que recorren el arbol */
long avl_sumarEmbarcados(const NodoViaje *raiz);
void avl_actualizarEmbarcados(NodoViaje *raiz, int codigoViaje, int delta);

#endif
