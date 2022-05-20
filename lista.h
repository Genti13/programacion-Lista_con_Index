#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define minimo(X,Y) (X) >= (Y) ? (Y) : (X)

typedef struct sNodo
{
    void * info;
    unsigned tamInfo;
    struct sNodo * sig;

} tNodo;

typedef tNodo * tLista;

void crearLista(tLista * p);

int ponerOrdenado(const void * d, unsigned cantBytes, tLista * p,
                  int (*comparar)(const void *, const void *),
                  int (*acumular)(void**, unsigned *, const void *, unsigned));

void mostrarLista(const tLista * p,
                  void (*mostrar)(const void *, FILE *), FILE * pf);

int sacarPrimero(tLista * p, void * d, unsigned cantBytes);

int listaVacia(tLista *);

int existeEnLista(const tLista *, const void * d, unsigned int *i,
                  int (*comparar)(const void *, const void *),
                  int (*conseguirIndice)(const void *));

#endif // LISTA_H_INCLUDED
