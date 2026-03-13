#include <stdio.h>
#include "Area.h"
#include "Volumenes.h"

int main(){
    double a, b;
    int opc;
    do
    {
        printf("Que desea realizar.\n");
        printf("1- Area circulo.\n");
        printf("2- Area cuadrado.\n");
        printf("3- Volumen esfera.\n");
        printf("4- Volumen cubo.\n");
        printf("5- Salir.\n");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            printf("ingrese el radio: \n");
            scanf("%lf", &a);
            printf("Area del circulo %lf: ", calcularAreaCirculo(a));
            printf("-------------------------- \n");
            break;
        case 2:
            printf("ingrese el lado del cuadrado: \n");
            scanf("%lf", &b);
            printf("Area del cuadrado %lf: ", calcularAreaCuadrado(b));
            printf("-------------------------- \n");
            break;
        case 3:
            printf("ingrese el valor de la esfera: \n");
            scanf("%lf", &a);
            printf("esfera %lf: ", calcularVolumenEsfera(a));
            printf("-------------------------- \n");
            break;
        case 4:
            printf("ingrese el valor del cubo: \n");
            scanf("%lf", &b);
            printf("Cubo %lf: ", calcularVolumenCubo(b));
            printf("-------------------------- \n");
            break;
        default:
            break;
        }
    } while (opc !=5);
    
    return 0;
}