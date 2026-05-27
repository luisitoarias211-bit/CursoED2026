#include <stdio.h>

void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

int main(){
    int data[] = {6, 2, 4, 1, 7, 9, 15, 3};
    int n = sizeof(data) / sizeof(data[0]);
    heapSort(data, n);
    //se imprime el arreglo ordenado
    for(int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    return 0;
}

//asegura la propiedad del monticulo en el subarbol
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

//funcion principal del ordena un arreglo usando heap sort
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // Extraer elementos del montículo uno por uno
    for (int i = n - 1; i > 0; i--) {
        //mover la raiz actual al final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        //llamar heapify en el montículo reducido
        heapify(arr, i, 0);
    }
}