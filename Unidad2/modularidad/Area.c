#include "Area.h"
#include <math.h>

double calcularAreaCirculo(double radio) {
    return PI * pow(radio, 2);
}

double calcularAreaCuadrado(double lado) {
    return lado * lado;
}