#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define ARCHIVO_MAESTRO "maestro.bin"
#define ARCHIVO_NOVEDADES "novadades.txt"
#define ARCHIVO_ERROR "error.txt"

#define LEER "rb"
#define LEER_TXT "rt"

#define ESCRIBIR "wb"
#define ESCRIBIR_TXT "wt"

#define TAM_ID 2
#define TAM_CANT 2
#define TAM_OP 1
#define TAM_LINEA 5

#include <stdio.h>
#include "tipos.h"

void archivosDePrueba();

int cargarMaestro(const tMaestro * maestro, const unsigned int elementos);
void mostrarMaestro(const tMaestro * maesstro);

int cargarNovedades(const tNovedad * novedad, const unsigned int elementos);
void mostrarNovedades(const tNovedad * novedad);

void mostrarArchivo(FILE * pf,  void (*funcion)());

void trozarCampos(tNovedad * novedades,char * buff);

void file_maestro(FILE * pf);
void file_novedades(FILE * pf);

#endif // ARCHIVOS_H_INCLUDED
