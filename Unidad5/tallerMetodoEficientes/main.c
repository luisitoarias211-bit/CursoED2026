/*Luis Alberto Gonzalez Arias
Valentina Alomia Montaño
Maria Isabel Sierra Garcia
Jose Angel Perea
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//capacidad maxima de los contenedores
#define MAX_CONTENEDORES 30

void mostrarContenedores(const double pesos[], int tam);
void registrarPesos(double pesos[], int *tam);
void generarPesosAleatorios(double pesos[], int *tam);
void copiarArreglo(const double origen[], double destino[], int tam);
void swap(double *a, double *b);

void quickSort(double pesos[], int bajo, int alto);
int partition(double pesos[], int bajo, int alto);
void mergeSort(double pesos[], int izquierda, int derecha);
void merge(double pesos[], int izquierda, int medio, int derecha);
void heapSort(double pesos[], int tam);
void heapify(double pesos[], int tam, int i);
int busquedaBinaria(const double pesos[], int tam, double pesoBuscar);

int main(){
    double pesosOriginal[MAX_CONTENEDORES]; //mantiene el estado incial de los registros
    double pesosTrabjo[MAX_CONTENEDORES]; //arreglo de trabajo para ordenamientos
    int tam = 0; //cantidad de contenedores en el patio
    int opcion;
    int ordenado = 0; //bandera para verificar si el arreglo esta ordenado

    srand(time(NULL)); //semilla para generar numeros aleatorios

    do{
        printf("\n===========================================\n");
        printf("SISTEMA DE ORGANIZACION DE CONTENEDORES \n");
        printf("\n===========================================\n");
        printf("1. Registar peso de contenedores manualmente\n");
        printf("2. Generar pesos aleatorios de contenedores\n");
        printf("3. Mostar contenedores registrados\n");
        printf("4. Ordenar contenedor Metodo 1\n");
        printf("5. Ordenar contenedor Metodo 2\n");
        printf("6. Ordenar contenedor Metodo 3\n");
        printf("7. Buscar contenedor\n");
        printf("8. Salir\n");
        printf("\n===========================================\n");
        printf("Seleccione una opcion: ");
        printf("\n===========================================\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                registrarPesos(pesosOriginal, &tam);
                copiarArreglo(pesosOriginal, pesosTrabjo, tam);
                ordenado = 0; //reinicia bandera de ordenamiento al registrar nuevos datos
                break;
            case 2:
                generarPesosAleatorios(pesosOriginal, &tam);
                copiarArreglo(pesosOriginal, pesosTrabjo, tam);
                ordenado = 0;
                break;
            case 3:
                if (tam == 0) {
                    printf("\n El patio de carga esta vacio.\n");
                } else {
                    mostrarContenedores(pesosOriginal, tam);
                }
                break;
            case 4:
                if (tam == 0) {
                    printf("\n No hay contenedores para ordenar.\n");
                } else {
                    copiarArreglo(pesosOriginal, pesosTrabjo, tam); //restauramos el arreglo de trabajo al estado original
                    quickSort(pesosTrabjo, 0, tam - 1);
                    printf("\n Contenedores ordenados con QuickSort:\n");
                    mostrarContenedores(pesosTrabjo, tam);
                    ordenado = 1; //marca el arreglo como ordenado
                }
                break;
            case 5:
                if (tam == 0) {
                    printf("\n No hay contenedores para ordenar.\n");
                } else {
                    copiarArreglo(pesosOriginal, pesosTrabjo, tam);
                    mergeSort(pesosTrabjo, 0, tam - 1);
                    printf("\n Contenedores ordenados con MergeSort:\n");
                    mostrarContenedores(pesosTrabjo, tam);
                    ordenado = 1;
                }
                break;
            case 6:
                if (tam == 0) {
                    printf("\n No hay contenedores para ordenar.\n");
                } else {
                    copiarArreglo(pesosOriginal, pesosTrabjo, tam);
                    heapSort(pesosTrabjo, tam);
                    printf("\nContenedores ordenados con HeapSort:\n");
                    mostrarContenedores(pesosTrabjo, tam);
                    ordenado = 1;
                }
                break;
            case 7:
                if (tam == 0){
                    printf("\n El patio esta vacio, no se puede buscar.\n");
                }else{
                    if (!ordenado) {
                        printf("\n El arreglo no esta ordenado.\n");
                        printf("\n Por seguridad se aplicara quickSort antes de buscar.\n");
                        quickSort(pesosTrabjo, 0, tam - 1);
                        ordenado = 1;
                    }
                    double pesoBuscar;
                    printf("\nIngrese el peso del contenedor a buscar (kg): ");
                    scanf("%lf", &pesoBuscar);
                    int indice = busquedaBinaria(pesosTrabjo, tam, pesoBuscar);
                    if (indice != -1) {
                        printf("\nContenedor encontrado en el indice %d con peso %.2f kg.\n", indice);
                    }else {
                        printf("\nContenedor con peso %.2f kg no encontrado en el patio.\n", pesoBuscar);
                    }
                }
                break;
            case 8:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while(opcion != 8);
    return 0;
}

void swap(double *a, double *b) {
    double temporal = *a;
    *a = *b;
    *b = temporal;
}

void mostrarContenedores(const double pesos[], int tam) {
    printf("Contenedores en patio (%d/%d): \n", tam, MAX_CONTENEDORES);
    for (int i = 0; i < tam; i++) {
        printf("[%d]: %.2f kg\t", i, pesos[i]);
        // Salto de linea estetico cada 4 contenedores mostrados
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

void registrarPesos(double pesos[], int *tam) {
    int cantidad;
    printf("\n Cuantos contenedores desea registrar? (Max %d): ", MAX_CONTENEDORES);
    scanf("%d", &cantidad);

    if (cantidad < 1 || cantidad > MAX_CONTENEDORES) {
        printf(" Cantidad invalida.\n");
        return;
    }
    *tam = cantidad; // Asigna la cantidad leida al puntero del tamaño global
    for (int i = 0; i < *tam; i++) {
        printf("Ingrese el peso del contenedor %d (kg): ", i + 1);
        scanf("%lf", &pesos[i]);
    }
    printf(" Registro manual completado.\n");
}

void generarPesosAleatorios(double pesos[], int *tam) {
    printf("\n Cuantos contenedores desea generar automaticamente? (Max %d): ", MAX_CONTENEDORES);
    scanf("%d", tam);

    if (*tam < 1 || *tam > MAX_CONTENEDORES) {
        *tam = 0;
        printf(" Cantidad invalida.\n");
        return;
    }

    for (int i = 0; i < *tam; i++) {
        // Genera una parte entera entre 1000 y 45000 + una parte flotante entre .00 y .99
        pesos[i] = 1000.0 + (rand() % 44001) + ((rand() % 100) / 100.0);
    }
    printf(" Pesos generados aleatoriamente.\n");
}

void copiarArreglo(const double origen[], double destino[], int tam) {
    for (int i = 0; i < tam; i++) {
        destino[i] = origen[i];
    }
}

int partition(double pesos[], int bajo, int alto) {
    double pivote = pesos[alto]; // Tomamos el ultimo elemento como pivote
    int i = (bajo - 1);          // Índice del elemento mas pequeño

    for (int j = bajo; j <= alto - 1; j++) {
        // Si el elemento actual es menor que el pivote, se mueve a la izquierda
        if (pesos[j] < pivote) {
            i++;
            swap(&pesos[i], &pesos[j]);
        }
    }
    // Coloca el pivote en su posicion real intermedia correcta
    swap(&pesos[i + 1], &pesos[alto]);
    return (i); // Retorna el indice divisor del pivote
}

void quickSort(double pesos[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = partition(pesos, bajo, alto); // Encuentra el indice de partición
        quickSort(pesos, bajo, pi - 1);        // Ordena recursivamente la mitad izquierda
        quickSort(pesos, pi + 1, alto);        // Ordena recursivamente la mitad derecha
    }
}

void merge(double pesos[], int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    // Asignacion dinamica de memoria estandar para las estructuras temporales
    double *L = (double *)malloc(n1 * sizeof(double));
    double *R = (double *)malloc(n2 * sizeof(double));

    // Copia de los datos hacia los subarreglos espejo L y R
    for (int i = 0; i < n1; i++) L[i] = pesos[izquierda + i];
    for (int j = 0; j < n2; j++) R[j] = pesos[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    // Combina los subarreglos de vuelta al arreglo principal en orden ascendente
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pesos[k] = L[i];
            i++;
        } else {
            pesos[k] = R[j];
            j++;
        }
        k++;
    }
    // Copia los elementos restantes que hayan quedado en L
    while (i < n1) {
        pesos[k] = L[i];
        i++; k++;
    }
    // Copia los elementos restantes que hayan quedado en R
    while (j < n2) {
        pesos[k] = R[j];
        j++; k++;
    }
    // Liberacion estricta de memoria asignada dinamicamente para prevenir fugas
    free(L);
    free(R);
}

void mergeSort(double pesos[], int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2; // Previene desbordamiento de enteros
        mergeSort(pesos, izquierda, medio);                // Divide la mitad izquierda
        mergeSort(pesos, medio + 1, derecha);              // Divide la mitad derecha
        merge(pesos, izquierda, medio, derecha);           // Junta y estructura ambas soluciones
    }
}

void heapify(double pesos[], int tam, int i) {
    int mayor = i;              // Inicializar el nodo raiz como el mas grande
    int izquierdo = 2 * i + 1;  // Posicion del hijo izquierdo en memoria lineal
    int derecho = 2 * i + 2;    // Posicion del hijo derecho en memoria lineal

    // Si el hijo izquierdo es mayor que la raiz calculada
    if (izquierdo < tam && pesos[izquierdo] > pesos[mayor])
        mayor = izquierdo;

    // Si el hijo derecho es mayor que el valor mas grande actual
    if (derecho < tam && pesos[derecho] > pesos[mayor])
        mayor = derecho;

    // Si el elemento mayor encontrado no es la raiz del subárbol
    if (mayor != i) {
        swap(&pesos[i], &pesos[mayor]);
        heapify(pesos, tam, mayor); // Rebalancea recursivamente el subarbol afectado
    }
}

void heapSort(double pesos[], int tam) {
    // Reorganiza el arreglo original para formar el Max-Heap inicial
    for (int i = tam / 2 - 1; i >= 0; i--)
        heapify(pesos, tam, i);

    // Extrae de manera secuencial los elementos del árbol binario
    for (int i = tam - 1; i > 0; i--) {
        swap(&pesos[0], &pesos[i]); // Mueve la raiz actual al final del arreglo
        heapify(pesos, i, 0);            // Reestablece el Max-Heap sobre el arbol reducido
    }
}

int busquedaBinaria(const double pesos[], int tam, double pesoBuscar) {
    int izquierda = 0;
    int derecha = tam - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        // Evaluacion de coincidencia exacta
        if (pesos[medio] == pesoBuscar)
            return medio; // Retorna el indice absoluto del contenedor
        // Si el peso es mayor, ignoramos la mitad izquierda del arbol ordenado
        if (pesos[medio] < pesoBuscar)
            izquierda = medio + 1;
        // Si el peso es menor, ignoramos la mitad derecha
        else
            derecha = medio - 1;
    }
    return -1; // Retorna bandera de fallo si el peso no existe en el patio
}