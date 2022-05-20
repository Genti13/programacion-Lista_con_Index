#include "funciones.h"
#include "tipos.h"
#include "lista.h"
#include "archivos.h"

void actualizarMaestro()
{
    tLista listaIx;
    tLista listaNovedad;

    crearLista(&listaIx);
    crearLista(&listaNovedad);

    cargarListaConIndices(&listaIx);
    cargarListaNovedades(&listaNovedad);

    actualizar(&listaIx, &listaNovedad);

//    FILE * pf = fopen("Mostrar Lista.txt", "wt");
//    mostrarLista(&listaIx, mostrarListaIndex, pf);
//    fclose(pf);

//    FILE * pf = fopen("Mostrar Lista Novedad.txt", "wt");
//    mostrarLista(&listaNovedad, mostrarListaNovedad, pf);
//    fclose(pf);
}

void actualizar(const tLista * listaIx, tLista * listaNov)
{
    tNovedad novedad;
    unsigned int indice;

    FILE * pfE = fopen(ARCHIVO_ERROR, ESCRIBIR_TXT);
    FILE * pfM = fopen(ARCHIVO_MAESTRO, "r+b");

    while(!listaVacia(listaNov))
    {
        sacarPrimero(listaNov, &novedad, sizeof(tNovedad));

        if(!existeEnLista(listaIx, &novedad, &indice,
                          compararID, conseguirIndice))
        {
            mostrarListaNovedad(&novedad, pfE);//Crea un txt
        }
        else
        {
            modificarMaestro(pfM, &novedad, &indice);
        }

    }

    printf("\n=======Archivo Maestro Modificado=======\n\n");
    mostrarArchivo(pfM, file_maestro);

    fclose(pfE);
    fclose(pfM);
}

int conseguirIndice(const void * d)
{
    tIndex * index = (tIndex *) d;

    return index->pos;
}

void modificarMaestro(FILE * pfM, const tNovedad * novedad,
                      const unsigned int * indice)
{
    tMaestro maestro;
    long int orPos = ftell(pfM);

    rewind(pfM);

    fseek(pfM,(*indice)*sizeof(tMaestro),SEEK_SET);
    fread(&maestro,sizeof(tMaestro),1,pfM);

    if(novedad->operacion == 'C')
    {
        maestro.cantidad += novedad->cantidad;
    }
    else
    {
        maestro.cantidad -= novedad->cantidad;
    }

//    rewind(pfM); /***Este no da Warning***/
//    fseek(pfM,(*indice)*sizeof(tMaestro),SEEK_SET);

    fseek(pfM, -1L * sizeof(tMaestro), SEEK_CUR);
    fwrite(&maestro,sizeof(tMaestro),1,pfM);

    fseek(pfM,orPos,SEEK_SET);

}

int cargarListaConIndices(tLista * lista)
{
    tIndex index;
    tMaestro maestro;
    int i = 0;

    FILE * pf = fopen(ARCHIVO_MAESTRO, LEER);

    if(!pf)
    {
        return 1;
    }

    fread(&maestro, sizeof(tMaestro), 1, pf);

    while(!feof(pf))
    {
        index.pos = i;
        index.clave = maestro.idProducto;
        ponerOrdenado(&index, sizeof(index),lista, compararID, NULL);
        i++;

        fread(&maestro, sizeof(tMaestro), 1, pf);
    }

    fclose(pf);

    return 0;
}

int cargarListaNovedades(tLista * lista)
{
    tNovedad novedad;
    char buff[TAM_LINEA+2];

    FILE * pf = fopen(ARCHIVO_NOVEDADES, LEER_TXT);

    if(!pf)
    {
        return 0;
    }

    while(fgets(buff,sizeof(buff),pf))
    {
        trozarCampos(&novedad,buff);
        ponerOrdenado(&novedad,sizeof(novedad),lista,
                      compararID_novedad, acumularCant);
    }

    fclose(pf);

    return 1;
}

int compararID(const void * ID_1, const void * ID_2)
{
    tIndex * n1 = (tIndex *)ID_1;
    tIndex * n2 = (tIndex *)ID_2;

    return n1->clave-n2->clave;
}

int compararID_novedad(const void * ID_1, const void * ID_2)
{
    const tNovedad * n1 = (tNovedad *)ID_1;
    const tNovedad * n2 = (tNovedad *)ID_2;

    return n1->idProducto - n2->idProducto;
}

int acumularCant(void ** info_1, unsigned * tam_1,
                 const void * info_2, unsigned tam_2)

{
    tNovedad * val1 = (tNovedad *)*info_1;
    tNovedad * val2 = (tNovedad *)info_2;

    if(val2->operacion == 'C')
    {
        val1->cantidad += val2->cantidad;
    }
    else
    {
        val1->cantidad-=val2->cantidad;
    }

    return 1;
}

void mostrarListaIndex(const void * index, FILE * pf)
{
    fprintf(pf, "%ld --- %0d\n",
            ((tIndex *)index)->clave, ((tIndex *)index)->pos);
}

void mostrarListaNovedad(const void * novedad, FILE * pf)
{
    fprintf(pf, "%ld --- %0d --- %c\n",
            ((tNovedad *)novedad)->idProducto,
            ((tNovedad *)novedad)->cantidad,
            ((tNovedad *)novedad)->operacion);
}


