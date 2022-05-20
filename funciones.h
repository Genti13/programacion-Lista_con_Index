#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include "tipos.h"
#include "lista.h"

void actualizarMaestro();

int cargarListaConIndices(tLista *);
int cargarListaNovedades(tLista *);

int compararID(const void *, const void *);
int compararID_novedad(const void *, const void *);
int acumularCant(void **, unsigned *, const void *, unsigned);

void actualizar(const tLista *, tLista *);
void modificarMaestro(FILE *, const tNovedad * novedad, const unsigned *);
int conseguirIndice(const void *);

void mostrarListaIndex(const void *, FILE * pf);
void mostrarListaNovedad(const void * novedad, FILE * pf);

#endif // FUNCIONES_H_INCLUDED
