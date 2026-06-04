# Sistema de Control y Ordenamiento - Patio de Carga Portuario

Este sistema interactivo ha sido desarrollado en **C** para gestionar la optimización y organización fisica de los contenedores ubicados en una terminal de carga portuaria. El software permite simular la distribución de pesos reales y aplicar los algoritmos de ordenamiento eficientes abordados durante la **Unidad 5** de la materia Estructuras de Datos.

##  Características Principales
* **Capacidad Estricta:** Manejo dinámico de almacenamiento en un patio estático de máximo 30 contenedores.
* **Tipos de Datos Reales:** Almacenamiento de pesos de precision con punto decimal flotante (`double`) en kilogramos.
* **Aislamiento de Pruebas:** Preservacion del estado del arreglo original. Cada ordenamiento limpia el entorno de ejecución clonando los datos brutos a una matriz de trabajo.
* **Control de Estado:** Asegura que no se realicen busquedas binarias sobre colecciones de datos corruptas o desorganizadas de forma nativa.

## 🛠️ Algoritmos Implementados (Unidad 5)

El sistema evalia y ejecuta tres de los principales algoritmos de ordenamiento eficientes con complejidad algoritmica promedio de $O(n \log n)$:

1.  **QuickSort:** Algoritmo por estrategia "Divide y Venceras" usando segmentación por pivote final.
2.  **MergeSort:** Algoritmo recursivo de división secuencial y ensamble dinámico mediante gestión manual de memoria en Heap.
3.  **HeapSort:** Algoritmo basado en la representación logica de arboles binarios mediante estructuras de monticulos maximos.
4.  **Busqueda Binaria:** Algoritmo de localizacion optima con complejidad temporal $O(\log n)$.
