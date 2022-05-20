#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct
{
    long int idProducto;
    int cantidad;
    float precioUnitario;
    unsigned minRepo;
    char status;
} tMaestro;

typedef struct
{
    long int idProducto;
    int cantidad;
    char operacion;
} tNovedad;

typedef struct
{
    long int clave;
    unsigned pos;
}tIndex;



#endif // TIPOS_H_INCLUDED
