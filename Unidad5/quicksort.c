#include <stdio.h>

void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void swap(int *a, int *b);

int main()
{
    int data[] = {6, 2, 4, 1, 5, 8, 12, 3, 9, 7};
    int n = sizeof(data) / sizeof(data[0]);
    quicksort(data, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", data[i]);
    }

    return 0;
}

void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

// Función para particionar el arreglo
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // se elige el ultimo arreglo como pivote
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            printf("Pivote: %d  Intercambiando %d y %d\n", pivot, arr[i], arr[j]);
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[high]);
    return i;
}

// intercambia dos elementos
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}