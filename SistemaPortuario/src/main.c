#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destino.h"
#include "estadisticas.h"

static void limpiarBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descartar */
    }
}

static int leerEntero(const char *mensaje) {
    int valor;
    printf("%s", mensaje);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida. Intente de nuevo: ");
        limpiarBufferEntrada();
    }
    limpiarBufferEntrada();
    return valor;
}

static void leerTexto(const char *mensaje, char *destino, int longitud) {
    printf("%s", mensaje);
    if (fgets(destino, longitud, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

static void mostrarMenu(void) {
    printf("\n===== Terminal Portuario Turistico de Buenaventura =====\n");
    printf("1. Registrar destino\n");
    printf("2. Registrar pasajero\n");
    printf("3. Mostrar pasajeros por destino\n");
    printf("4. Registrar viaje programado\n");
    printf("5. Buscar viaje\n");
    printf("6. Mostrar arbol de viajes\n");
    printf("7. Realizar embarque\n");
    printf("8. Consultar pasajero (donde esta: espera/embarcado - a donde)\n");
    printf("9. Mostrar todos los destinos\n");
    printf("10. Modificar un destino\n");
    printf("11. Ver estadisticas generales\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

static void opcionRegistrarDestino(ColaDestinos *destinos) {
    int codigo = leerEntero("Codigo del destino: ");
    char nombre[LONGITUD_NOMBRE];
    char empresa[LONGITUD_EMPRESA];
    leerTexto("Nombre del destino: ", nombre, LONGITUD_NOMBRE);
    leerTexto("Empresa que lo gestiona: ", empresa, LONGITUD_EMPRESA);

    int resultado = colaDestinos_registrar(destinos, codigo, nombre, empresa);
    if (resultado == -1) {
        printf("Error: ya existe un destino con ese codigo.\n");
    } else if (resultado == -2) {
        printf("Error: no fue posible reservar memoria.\n");
    } else {
        printf("Destino registrado correctamente.\n");
    }
}

static void opcionRegistrarPasajero(ColaDestinos *destinos) {
    int codigoDestino = leerEntero("Codigo del destino: ");
    Destino *destino = colaDestinos_buscarPorCodigo(destinos, codigoDestino);
    if (destino == NULL) {
        printf("Error: destino no encontrado.\n");
        return;
    }

    int documento = leerEntero("Numero de documento: ");
    printf("Tipo de documento (1=Cedula, 2=Pasaporte, 3=Tarjeta de Identidad): ");
    int tipo = leerEntero("");

    int resultado = colaPasajeros_registrar(&destino->colaPasajeros, documento, tipo);
    if (resultado == -1) {
        printf("Error: tipo de documento no permitido.\n");
    } else if (resultado == -2) {
        printf("Error: el pasajero ya esta registrado en esta cola.\n");
    } else if (resultado == -3) {
        printf("Error: no fue posible reservar memoria.\n");
    } else {
        printf("Pasajero registrado correctamente en la cola de %s.\n", destino->nombre);
    }
}

static void opcionMostrarPasajeros(ColaDestinos *destinos) {
    int codigoDestino = leerEntero("Codigo del destino: ");
    Destino *destino = colaDestinos_buscarPorCodigo(destinos, codigoDestino);
    if (destino == NULL) {
        printf("Error: destino no encontrado.\n");
        return;
    }
    printf("Pasajeros de %s:\n", destino->nombre);
    colaPasajeros_mostrarTodos(&destino->colaPasajeros);
}

static void opcionRegistrarViaje(ColaDestinos *destinos) {
    int codigoDestino = leerEntero("Codigo del destino: ");
    Destino *destino = colaDestinos_buscarPorCodigo(destinos, codigoDestino);
    if (destino == NULL) {
        printf("Error: destino no encontrado.\n");
        return;
    }

    int codigoViaje = leerEntero("Codigo unico del viaje: ");
    int capacidad = leerEntero("Capacidad maxima: ");

    int resultado = 0;
    destino->raizViajes = avl_insertar(destino->raizViajes, codigoViaje, capacidad, &resultado);
    if (resultado == -1) {
        printf("Error: ya existe un viaje con ese codigo en este destino.\n");
    } else if (resultado == -2) {
        printf("Error: no fue posible reservar memoria.\n");
    } else {
        printf("Viaje registrado y arbol balanceado (AVL) correctamente.\n");
    }
}

static void opcionBuscarViaje(ColaDestinos *destinos) {
    int codigoDestino = leerEntero("Codigo del destino: ");
    Destino *destino = colaDestinos_buscarPorCodigo(destinos, codigoDestino);
    if (destino == NULL) {
        printf("Error: destino no encontrado.\n");
        return;
    }
    int codigoViaje = leerEntero("Codigo del viaje a buscar: ");
    NodoViaje *encontrado = avl_buscar(destino->raizViajes, codigoViaje);
    if (encontrado == NULL) {
        printf("Viaje no encontrado en este destino.\n");
    } else {
        printf("Viaje encontrado -> Codigo: %d | Capacidad maxima: %d | Embarcados: %d\n",
               encontrado->codigoViaje, encontrado->capacidadMaxima, encontrado->pasajerosEmbarcados);
    }
}

static void opcionMostrarArbol(ColaDestinos *destinos) {
    int codigoDestino = leerEntero("Codigo del destino: ");
    printf("Viajes programados (recorrido in-order por codigo):\n");
    colaDestinos_mostrarViajes(destinos, codigoDestino);
}

static void opcionRealizarEmbarque(ColaDestinos *destinos) {
    int codigoDestino = leerEntero("Codigo del destino: ");
    Destino *destino = colaDestinos_buscarPorCodigo(destinos, codigoDestino);
    if (destino == NULL) {
        printf("Error: destino no encontrado.\n");
        return;
    }

    Pasajero *primero = colaPasajeros_consultarPrimero(&destino->colaPasajeros);
    if (primero == NULL) {
        printf("No hay pasajeros en espera para este destino.\n");
        return;
    }
    printf("Proximo pasajero en la fila: Documento %d\n", primero->numeroDocumento);

    int codigoViaje = leerEntero("Codigo del viaje en el que embarca: ");
    NodoViaje *viaje = avl_buscar(destino->raizViajes, codigoViaje);
    if (viaje == NULL) {
        printf("Error: ese viaje no existe para este destino.\n");
        return;
    }
    if (viaje->pasajerosEmbarcados >= viaje->capacidadMaxima) {
        printf("Error: el viaje ya alcanzo su capacidad maxima.\n");
        return;
    }

    colaPasajeros_embarcarPrimero(&destino->colaPasajeros);
    avl_actualizarEmbarcados(destino->raizViajes, codigoViaje, 1);
    printf("Embarque realizado correctamente.\n");
}

static void opcionConsultarPasajero(ColaDestinos *destinos) {
    int documento = leerEntero("Numero de documento a consultar: ");
    Destino *actual = destinos->frente;
    while (actual != NULL) {
        Pasajero *encontrado = colaPasajeros_buscarPorDocumento(&actual->colaPasajeros, documento);
        if (encontrado != NULL) {
            printf("Pasajero encontrado -> Destino: %s | Estado: %s\n",
                   actual->nombre, estadoPasajeroTexto(encontrado->estado));
            return;
        }
        actual = actual->siguiente;
    }
    printf("Pasajero no encontrado en ninguna fila.\n");
}

static void opcionModificarDestino(ColaDestinos *destinos) {
    int codigo = leerEntero("Codigo del destino a modificar: ");
    char nombre[LONGITUD_NOMBRE];
    char empresa[LONGITUD_EMPRESA];
    leerTexto("Nuevo nombre (enter para no cambiar): ", nombre, LONGITUD_NOMBRE);
    leerTexto("Nueva empresa (enter para no cambiar): ", empresa, LONGITUD_EMPRESA);

    int resultado = colaDestinos_modificar(destinos, codigo, nombre, empresa);
    if (resultado == -1) {
        printf("Error: destino no encontrado.\n");
    } else {
        printf("Destino actualizado correctamente.\n");
    }
}

int main(void) {
    ColaDestinos destinos;
    colaDestinos_inicializar(&destinos);

    int opcion;
    do {
        mostrarMenu();
        opcion = leerEntero("");

        switch (opcion) {
            case 1: opcionRegistrarDestino(&destinos); break;
            case 2: opcionRegistrarPasajero(&destinos); break;
            case 3: opcionMostrarPasajeros(&destinos); break;
            case 4: opcionRegistrarViaje(&destinos); break;
            case 5: opcionBuscarViaje(&destinos); break;
            case 6: opcionMostrarArbol(&destinos); break;
            case 7: opcionRealizarEmbarque(&destinos); break;
            case 8: opcionConsultarPasajero(&destinos); break;
            case 9: colaDestinos_mostrarTodos(&destinos); break;
            case 10: opcionModificarDestino(&destinos); break;
            case 11: estadisticas_mostrarTodas(&destinos); break;
            case 0: printf("Cerrando el sistema...\n"); break;
            default: printf("Opcion invalida.\n"); break;
        }
    } while (opcion != 0);

    colaDestinos_liberar(&destinos);
    return 0;
}