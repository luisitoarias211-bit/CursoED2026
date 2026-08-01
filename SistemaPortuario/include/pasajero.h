#ifndef PASAJERO_H
#define PASAJERO_H

/* ---------- Tipos de documento permitidos ---------- */
typedef enum
{
    CEDULA_CIUDADANIA = 1,
    PASAPORTE = 2,
    TARJETA_IDENTIDAD = 3
} TipoDocumento;

/* ---------- Estado del pasajero ---------- */
typedef enum
{
    EN_ESPERA = 0,
    EMBARCADO = 1
} EstadoPasajero;

/* ---------- Nodo de la cola FIFO de pasajeros ---------- */
typedef struct Pasajero
{
    int numeroDocumento;
    TipoDocumento tipoDocumento;
    EstadoPasajero estado;
    struct Pasajero *siguiente;
} Pasajero;

/* ---------- Cola FIFO de pasajeros (una por destino) ---------- */
typedef struct
{
    Pasajero *frente;
    Pasajero *final;
    int cantidad;
} ColaPasajeros;

/* ---------- Ciclo de vida de la cola ---------- */
void colaPasajeros_inicializar(ColaPasajeros *cola);
void colaPasajeros_liberar(ColaPasajeros *cola);

/* ---------- Validaciones ---------- */
int tipoDocumentoValido(int tipo);

/* ---------- Operaciones obligatorias ---------- */
int colaPasajeros_registrar(ColaPasajeros *cola, int numeroDocumento, int tipoDocumento);
Pasajero *colaPasajeros_consultarPrimero(ColaPasajeros *cola);
int colaPasajeros_embarcarPrimero(ColaPasajeros *cola);
void colaPasajeros_mostrarTodos(const ColaPasajeros *cola);
int colaPasajeros_contarEnEspera(const ColaPasajeros *cola);
Pasajero *colaPasajeros_buscarPorDocumento(const ColaPasajeros *cola, int numeroDocumento);
int colaPasajeros_existeDocumento(const ColaPasajeros *cola, int numeroDocumento);
int colaPasajeros_estaVacia(const ColaPasajeros *cola);
int colaPasajeros_contarEmbarcados(const ColaPasajeros *cola);

const char *tipoDocumentoTexto(TipoDocumento tipo);
const char *estadoPasajeroTexto(EstadoPasajero estado);

#endif