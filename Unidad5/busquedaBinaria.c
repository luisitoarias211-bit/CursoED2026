#include <stdio.h>

int binarySearch(int arr[], int n, int target) {
    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if (arr[medio] == target) {
            return medio; //elemento encontrado
        } else if (arr[medio] < target) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    return -1; //no encontrado
}

int main(){
    int sortedData[] = {1,2,3,4,5,6,7,8,9,12};
    int n = sizeof(sortedData) / sizeof(sortedData[0]);
    int key = 9;
    int index = binarySearch(sortedData, n, key);
    if (index != -1) {
        printf("Elemento %d encontrado en la posicio %d\n", key, index);
    } else {
        printf("Elemento %d no encontrado\n", key);
    }
    return 0;
}