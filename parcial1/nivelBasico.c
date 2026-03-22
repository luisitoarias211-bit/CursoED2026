#include <stdio.h>

#define MAX 100

int datos[MAX];
int n = 0;
int datosIngresados = 0;

// funcion para mostrar el arreglo
void mostrar(int arr[], int tam){
    for(int i=0; i<tam; i++){
        printf("%d - ", arr[i]);
    }
    printf("\n ");
}

void burbuja(int arr[], int tam) {
    int i, j, temp;
    printf("\n--- Ordenamiento Burbuja ---\n");
    for(i = 0; i < tam - 1; i++) {
        for(j = 0; j < tam - i - 1; j++) {
            // para intercanbiar los valores
            if(arr[j] > arr[j+1]) {

                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                
                printf("Intercambio: ");
                mostrar(arr, tam);
            }
        }
        printf("Pasada %d: ", i+1);
        mostrar(arr, tam);
    }
}

void seleccion(int arr[], int tam) {
    int i, j, min, temp;

    printf("\n--- Ordenamiento Seleccion---\n");

    for(i = 0; i < tam - 1; i++) {
        min = i;

        for(j = i + 1; j < tam; j++) {
            // para intercanbiar los valores
            if(arr[j] < arr[min]) {
                min = j;
            }
        }

        if(min != i) {
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;

            printf("Intercambio: ");
            mostrar(arr, tam);
        }
        printf("Pasada %d: ", i+1);
        mostrar(arr, tam);
    }
}

void insercion(int arr[], int tam) {
    int i, j, clave;

    printf("\n--- Ordenamiento Insercion ---\n");

    for(i = 1; i < tam; i++) {
        clave = arr[i];
        j = i - 1;
        // para intercanbiar los valores
        while(j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;

            arr[j + 1] = clave;
            printf("Intercambio: ");
            mostrar(arr, tam);
        }
        printf("Pasada %d: ", i+1);
        mostrar(arr, tam);
    }
}

int main(){
    int opcion, i;
    int copia[MAX];

    do{
        printf("---- Menu ----\n");
        printf("\n");
        printf("1 - ingresar los datos\n");

        if (datosIngresados){
            printf("2 - Mostrar arreglo original\n");
            printf("3 - Ordenar por Burbuja\n");
            printf("4 - Ordenar por Seleccion\n");
            printf("5 - Ordenar por Insercion\n");
        }

        printf("6 - Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion){
            case 1:
                printf("Cuantos numeros desea ingresar? ");
                scanf("%d", &n);
                if (n > 3){
                    for(i = 0; i < n; i++) {
                        printf("Dato [%d]: ", i);
                        scanf("%d", &datos[i]);

                        datosIngresados = 1;
                    }
                }else{
                    printf("los numeros tiene que ser mas de tres..\n");
                }
                break;
            case 2:
                if(datosIngresados) {
                    printf("Arreglo original: ");
                    mostrar(datos, n);
                } else {
                    printf("Primero debe ingresar datos.\n");
                }
            break;
            case 3:
                if(datosIngresados) {
                    for(i = 0; i < n; i++) copia[i] = datos[i];
                    burbuja(copia, n);
                } else {
                    printf("Primero debe ingresar datos.\n");
                }
            break;
            case 4:
                if(datosIngresados) {
                    for(i = 0; i < n; i++) copia[i] = datos[i];
                    seleccion(copia, n);
                } else {
                    printf("Primero debe ingresar datos.\n");
                }
            break;
            case 5:
                if(datosIngresados) {
                    for(i = 0; i < n; i++) copia[i] = datos[i];
                    insercion(copia, n);
                } else {
                    printf("Primero debe ingresar datos.\n");
                }
            break;
            case 6:
                printf("Saliendo del programa...\n");
            break;
        
        default:
            printf("Opcion invalida\n");
        }
        
    }while (opcion != 6);
    
    

    return 0;
}