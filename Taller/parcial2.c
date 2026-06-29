#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoCola{
    char documento[20];
    struct NodoCola* sig;
}NodoCola;

typedef struct {
    NodoCola* frente;
    NodoCola* final;
} Cola;

typedef struct NodoPila{
    char documento[20];
    char estado[20];
    struct NodoPila* sig;
}NodoPila;

typedef struct{
    NodoPila* tope;
}Pila;

void incializarCola(Cola* q);
int colaVacia(Cola* q);
void encolarPaciente(Cola* q, char* doc);
int desencolarPaciente(Cola* q, char* docDestino);
void mostrarCola(Cola* q);
void inicializarPila(Pila* s);
int pilaVacia(Pila* s);
void empujarDiagnostico(Pila* s, char* doc, int opcionEstado);
void mostrarPila(Pila* s);

int main(){
    Cola filaEspera;
    Pila historialDiagnostico;

    incializarCola(&filaEspera);
    inicializarPila(&historialDiagnostico);

    int opc;
    char docAux[20];
    int estadoAux;

    do{
        printf("\n-----------------------------------------------\n");
        printf("   SISTEMA DE GESTION HOSPITALARIA\n");
        printf("\n---------------------------------------------------\n");
        printf("1. Registrar llegada del paciente\n");
        printf("2. Atender al siguiente paciente\n");
        printf("3. Ver paciente en la cola de espera\n");
        printf("4. Ver historial de diagnostico\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        getchar(); // limpia la entrada

        switch (opc){
            case 1:
                printf("Ingresa el numero de documento del paciente: ");
                fgets(docAux, 20, stdin);
                docAux[strcspn(docAux, "\n")] = 0;//eliminar el salto de linea
                encolarPaciente(&filaEspera, docAux);
                break;
            case 2:
                if (desencolarPaciente(&filaEspera, docAux)){
                    printf("Atendiendo al paciente con documento: %s\n", docAux);
                    printf("Clasifique el estado de salud del paciente: \n");
                    printf("1.Sano \n 2.Enfermo \n 3.Grave \nSeleccion: ");
                    scanf("%d", &estadoAux);
                    //almacena el resultado directamente en la pila
                    empujarDiagnostico(&historialDiagnostico, docAux, estadoAux);
                }else{
                    printf("No hay paciente por atender en la cola.\n");
                }
                break;
            case 3:
                printf("------ Estado de la cola ------\n");
                mostrarCola(&filaEspera);
                break;
            case 4:
                printf("----- Historial en la pila------\n");
                mostrarPila(&historialDiagnostico);
                break;
            case 5:
                printf("Cerrando el sistema..\n");
                break;
            default:
                printf("Opcion no invalida");
                break;
            }
    }while (opc != 5);
    return 0;
}
void incializarCola(Cola* q){
    q->frente = NULL;
    q->final = NULL;
}

int colaVacia(Cola* q){
    return q->frente == NULL;
}

void encolarPaciente(Cola* q, char* doc){
    NodoCola* nuevo = (NodoCola*)malloc(sizeof(NodoCola));
    if(!nuevo){
        printf("Error de memoria\n");
        return;
    }
    strcpy(nuevo->documento, doc);
    nuevo->sig = NULL;

    if(colaVacia(q)){
        q->frente = nuevo;
    }else{
        q->final->sig = nuevo;
    }
    q->final = nuevo;
    printf("Paciente con Documento: %s \nregistrado en la cola de espera\n", doc);
}

int desencolarPaciente(Cola* q, char* docDestino){
    if(colaVacia(q)){
        return 0;
    }
    NodoCola* temp = q->frente;
    strcpy(docDestino, temp->documento);

    q->frente = q->frente->sig;
    if (q->frente == NULL){
        q->final = NULL;
    }
    free(temp);
    return 1;
}

void mostrarCola(Cola* q){
    if (colaVacia(q)){
        printf("No hay paciente en la cola de espera\n");
        return;
    }
    NodoCola* actual = q->frente;
    printf("\nPaciente en espera (Siguiente -> ultimo): ");
    while(actual != NULL){
        printf("[%s] ", actual->documento);
        actual = actual->sig;
    }
}

void inicializarPila(Pila* s){
    s->tope = NULL;
}

int pilaVacia(Pila* s){
    return s->tope == NULL;
}

void empujarDiagnostico(Pila* s, char* doc, int opcionEstado){
    NodoPila* nuevo = (NodoPila*)malloc(sizeof(NodoPila));
    if(!nuevo){
        printf("Error de memoria\n");
        return;
    }
    strcpy(nuevo->documento, doc);

    switch (opcionEstado){
    case 1:
        strcpy(nuevo->estado, "Sano");
        break;
    case 2:
        strcpy(nuevo->estado, "Enfermo");
        break;
    case 3:
        strcpy(nuevo->estado, "Grave");
        break;
    default:
        strcpy(nuevo->estado, "no especificado");
        break;
    }

    nuevo->sig =s->tope;
    s->tope = nuevo;
    printf("\nDiagnostico guardado en la pila: %s (%s).", nuevo->documento, nuevo->estado);
}

void mostrarPila(Pila* s){
    if (pilaVacia(s)){
        printf("\nNo hay diagnostico registrado en la pila.");
        return;
    }
    NodoPila* actual = s->tope;
    printf("\nHistorial de diagnostico (ultimo atendido primero): \n");
    printf("\n--------------------------------------------------\n");
    while (actual != NULL){
        printf("Paciente: %-15s | Estado: %s\n", actual->documento, actual->estado);
        actual = actual->sig;
    }
    printf("\n--------------------------------------------------\n");
}