#include "Volumenes.h"
#include "Area.h" // se necesita el el numero PI
#include <math.h>

double calcularVolumenEsfera(double radio) {
    return (4.0 / 3.0) * PI * pow(radio, 3);
}

double calcularVolumenCubo(double lado) {
    return pow(lado, 3);
}