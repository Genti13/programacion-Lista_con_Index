#include "lista.h"

void crearLista(tLista * p)
{
    *p = NULL;
}

int ponerOrdenado(const void * d, unsigned cantBytes, tLista * p,
                  int (*comparar)(const void *, const void *),
                  int (*acumular)(void**, unsigned *, const void *, unsigned))
{
    tNodo * nue;

    while(*p && comparar((*p)->info, d) < 0)
    {
        p = &(*p)->sig;
    }

    if(*p && comparar((*p)->info, d) == 0)
    {
        if(acumular)
        {
            if(!acumular(&(*p)->info, &(*p)->tamInfo,d,cantBytes))
            {
                return 0;
            }

            return -1;
        }
    }

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        return 0;

    }

    memcpy(nue->info,d,cantBytes);

    nue->tamInfo = cantBytes;
    nue->sig = *p;

    *p = nue;

    return 1;
}

void mostrarLista(const tLista * p,
                  void (*mostrar)(const void *, FILE *), FILE * pf)
{
    while(*p)
    {
        mostrar((*p)->info, pf);
        p=&(*p)->sig;
    }

}

int sacarPrimero(tLista * p, void * d, unsigned cantBytes)
{
    tNodo * aux = *p;

    if(*p == NULL)
    {
        return 0;
    }

    *p = aux->sig;

    memcpy(d, aux->info,minimo(aux->tamInfo, cantBytes));

    free(aux->info);
    free(aux);

    return 1;
}

int listaVacia(tLista * p)
{
    return *p == NULL;
}

int existeEnLista(const tLista * p, const void * d, unsigned int * i,
                  int (*comparar)(const void *, const void *),
                  int (*conseguirIndice)(const void *))
{
    while(*p)
    {
        if(comparar((*p)->info, d) == 0)
        {
            *i = conseguirIndice((*p)->info);
            return 1;
        }

        p = &(*p)->sig;
    }

    return 0;
}
