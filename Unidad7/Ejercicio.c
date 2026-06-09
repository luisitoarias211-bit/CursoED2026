#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//estructura para almacenar la informacion de cada usuario
typedef struct {
    char cedula[20];
    char genero[15];
    int dia, mes, anio;
    int esPrioridad;//1 si es prioridad, 0 si es normal
} Usuario;

//estructura para el nodo de la lista y la cola
typedef struct Nodo{
    Usuario usuario;
    struct Nodo* siguiente;
}Nodo;

//estructura para la cola
typedef struct {
    Nodo* frente;
    Nodo* final;
} Cola;

//funcion para calcular la edad del usuario
int calcularEdad(int dia, int mes, int anio) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int anioActual = tm.tm_year + 1900;
    int mesActual = tm.tm_mon + 1;
    int diaActual = tm.tm_mday;
    int edad = anioActual - anio;
    //condicion para ajustar la edad si el usuario no ha cumplido años en el año actual
    if (mesActual < mes || (mesActual == mes && diaActual < dia)) {
        edad--;//si el mes actual es menor que el mes de nacimiento, se resta un año a la edad
    }
    return edad;
}

//funcion auxiliar para reservar memoria y esctructurar un nuevo nodo
Nodo* crearNodo(Usuario usuario) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));//reserva espacio en el heap para un nuevo nodo
    nuevo->usuario = usuario;//asigna el usuario al nodo
    nuevo->siguiente = NULL;//inicializa el puntero siguiente a NULL
    return nuevo;
}

//funcion para modificar la cabeza original
void insertarLista(Nodo** cabeza, Usuario usuario){
    Nodo* nuevo = crearNodo(usuario);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        Nodo* temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

//funcion para mostrar la lista de usuarios registrados
void mostrarLista(Nodo* cabeza){
    if (cabeza == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    Nodo* temp = cabeza;
    while (temp != NULL) {
        int edad = calcularEdad(temp->usuario.dia, temp->usuario.mes, temp->usuario.anio);
        printf("CC: %s | Genero: %s | Edad: %d anos | Tipo: %s\n",
            temp->usuario.cedula, temp->usuario.genero, edad, temp->usuario.esPrioridad ? "Prioritario" : "Normal");
        temp = temp->siguiente;
    }
}
//funciones para la cola
void inicializarCola(Cola* cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

//funcion para insertar al final de la cola
void encolar(Cola* cola, Usuario usuario) {
    Nodo* nuevo = crearNodo(usuario);
    if (cola->final == NULL) {
        cola->frente = cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
}

//recorre e imprime los usuarios en la cola, mostrando su cedula, genero y edad
void mostrarCola(Cola* cola) {
    if (cola->frente == NULL){
        printf("La cola esta vacia.\n");
        return;
    }
    Nodo* temp = cola->frente;
    while (temp != NULL) {
        int edad = calcularEdad(temp->usuario.dia, temp->usuario.mes, temp->usuario.anio);
        printf("CC: %s | Genero: %s | Edad: %d anos\n",
            temp->usuario.cedula, temp->usuario.genero, edad);
        temp = temp->siguiente;
    }
}

int main(){
    Nodo* historialGeneral = NULL;
    Cola colaPrioridad, colaNormal;
    inicializarCola(&colaPrioridad);
    inicializarCola(&colaNormal);

    int n;
    int opc;

    do{
        printf("\n==========Sistema De Gestion========\n");
        printf("1- Registrar Usuario\n");
        printf("2- Mostrar Historial General\n");
        printf("3- Mostrar Cola de Prioridad\n");
        printf("4- Mostrar Cola Normal\n");
        printf("5- Salir\n");
        printf("====================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                printf("Ingrese la cantidad de usuarios a registrar: ");
                scanf("%d", &n);
                getchar(); // Limpia el buffer
                //ciclo para registar los usuarios
                for (int i = 0; i < n; i++){
                    Usuario nuevoUsuario;
                    printf("====================================\n");
                    printf("Registro del Usuario %d \n", i + 1);
                    printf("Cedula: ");
                    fgets(nuevoUsuario.cedula, sizeof(nuevoUsuario.cedula), stdin);
                    nuevoUsuario.cedula[strcspn(nuevoUsuario.cedula, "\n")] = 0; // Elimina el salto de linea

                    printf("Genero (Masculino/Femenino): ");
                    fgets(nuevoUsuario.genero, sizeof(nuevoUsuario.genero), stdin);
                    nuevoUsuario.genero[strcspn(nuevoUsuario.genero, "\n")] = 0; // Elimina el salto de linea

                    printf("Fecha de nacimiento (dd mm aaaa): ");
                    scanf("%d %d %d", &nuevoUsuario.dia, &nuevoUsuario.mes, &nuevoUsuario.anio);
                    getchar(); // Limpia el buffer
                    //evalua la edad del usuario
                    int edad = calcularEdad(nuevoUsuario.dia, nuevoUsuario.mes, nuevoUsuario.anio);
                    //strcasecmp compara dos cadenas de caracteres sin tener en cuenta mayusculas o minusculas
                    if(strcasecmp(nuevoUsuario.genero, "Femenino") == 0 || edad >= 60) {
                        nuevoUsuario.esPrioridad = 1;//cambia a verdadero 1
                        encolar(&colaPrioridad, nuevoUsuario);
                        printf("Usuario registrado en prioridad.\n");
                        printf("====================================\n");
                    } else {
                        nuevoUsuario.esPrioridad = 0;//cambia a falso 0
                        encolar(&colaNormal, nuevoUsuario);
                        printf("Usuario registrado en normal.\n");
                        printf("====================================\n");
                    }
                    insertarLista(&historialGeneral, nuevoUsuario);
                }
                break;
            case 2:
            printf("\n====================================\n");
                printf("Historial General De Afiliados: \n");
                mostrarLista(historialGeneral);
                printf("====================================\n");
                break;
            case 3:
            printf("====================================\n");
                printf("Usuarios en Cola de Prioridad:\n");
                mostrarCola(&colaPrioridad);
                printf("====================================\n");
                break;
            case 4:
            printf("\n====================================\n");
                printf("Usuarios en Cola Normal:\n");
                mostrarCola(&colaNormal);
                printf("====================================\n");
                break;
            case 5:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida...\n");
        }
    } while (opc != 5);

    return 0;
}