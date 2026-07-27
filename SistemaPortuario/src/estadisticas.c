#include <stdio.h>
#include "estadisticas.h"

void estadisticas_mostrarTodas(const ColaDestinos *cola) {
    if (cola->frente == NULL) {
        printf("  No hay destinos registrados todavia.\n");
        return;
    }

    long totalPasajeros = 0;
    long totalEnEspera = 0;
    long totalEmbarcados = 0;
    long totalViajes = 0;
    long totalEmbarcadosEnViajes = 0;

    Destino *destinoMayor = cola->frente;
    Destino *destinoMenor = cola->frente;

    Destino *actual = cola->frente;
    while (actual != NULL) {
        int enEspera = colaPasajeros_contarEnEspera(&actual->colaPasajeros);
        int embarcados = colaPasajeros_contarEmbarcados(&actual->colaPasajeros);
        int viajesDestino = avl_contarViajes(actual->raizViajes);

        totalPasajeros += actual->colaPasajeros.cantidad;
        totalEnEspera += enEspera;
        totalEmbarcados += embarcados;
        totalViajes += viajesDestino;
        totalEmbarcadosEnViajes += avl_sumarEmbarcados(actual->raizViajes);

        if (enEspera > colaPasajeros_contarEnEspera(&destinoMayor->colaPasajeros)) {
            destinoMayor = actual;
        }
        if (enEspera < colaPasajeros_contarEnEspera(&destinoMenor->colaPasajeros)) {
            destinoMenor = actual;
        }

        actual = actual->siguiente;
    }

    double promedioEspera = (double)totalEnEspera / cola->cantidad;
    double promedioEmbarcadosPorViaje = totalViajes > 0 ? (double)totalEmbarcadosEnViajes / totalViajes : 0.0;

    printf("  Promedio de pasajeros en espera por destino: %.2f\n", promedioEspera);
    printf("  Promedio de pasajeros embarcados por viaje: %.2f\n", promedioEmbarcadosPorViaje);
    printf("  Destino con mayor cantidad de pasajeros en espera: [%d] %s (%d)\n",
        destinoMayor->codigo, destinoMayor->nombre,
        colaPasajeros_contarEnEspera(&destinoMayor->colaPasajeros));
    printf("  Destino con menor cantidad de pasajeros en espera: [%d] %s (%d)\n",
        destinoMenor->codigo, destinoMenor->nombre,
        colaPasajeros_contarEnEspera(&destinoMenor->colaPasajeros));
    printf("  Cantidad total de pasajeros registrados: %ld\n", totalPasajeros);
    printf("  Cantidad total de pasajeros embarcados: %ld\n", totalEmbarcados);
}