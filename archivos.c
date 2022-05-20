#include "funciones.h"
#include "tipos.h"
#include "archivos.h"

void archivosDePrueba()
{
    tMaestro maestro[] =
    {
        {7, 85, 120.30,       10,     'O'},
        {1, 100, 35.80,       75,     'O'},
        {12, 45, 100.00,      120,    'P'}
    };

    tNovedad novedades[] =
    {
        {1,   30, 'C'},
        {7,   10, 'V'},
        {1,   50, 'V'},
        {15,  10, 'C'}
    };

    FILE * pm;
    FILE * pn;

    cargarMaestro(maestro, sizeof(maestro)/sizeof(tMaestro));
    pm = fopen(ARCHIVO_MAESTRO, LEER);
    printf("=============Archivo Maestro============\n\n");
    mostrarArchivo(pm, file_maestro);
    fclose(pm);

    printf("\n===========Archivo Novedades============\n\n");

    cargarNovedades(novedades, sizeof(novedades)/sizeof(tNovedad));
    pn = fopen(ARCHIVO_NOVEDADES, LEER);
    mostrarArchivo(pn, file_novedades);
    fclose(pn);

}
int cargarMaestro(const tMaestro * maestro, const unsigned int elementos)
{
    FILE * pf = fopen(ARCHIVO_MAESTRO, ESCRIBIR);

    if(!pf)
    {
        return 0;
    }

    fwrite(maestro, sizeof(tMaestro),elementos, pf);

    fclose(pf);

    return 1;
}

int cargarNovedades(const tNovedad * novedades, const unsigned int elementos)
{

    FILE * pf = fopen(ARCHIVO_NOVEDADES, ESCRIBIR);
    int i;
    if(!pf)
        return 1;

    for(i = 0; i<elementos; i++,novedades++)
    {
        fprintf(pf,"%02ld%02d%c\n", novedades->idProducto,
                novedades->cantidad,
                novedades->operacion);
    }

    fclose(pf);

    return 0;
}

void mostrarArchivo(FILE * pf, void (*funcion)(FILE * pf))
{
    funcion(pf);
}

void file_maestro(FILE * pf)
{
    tMaestro maestro;
    long posOriginal = ftell(pf);

    rewind(pf);

    mostrarMaestro(NULL);

    fread(&maestro, sizeof(tMaestro),1,pf);
    while(!feof(pf))
    {
        mostrarMaestro(&maestro);
        fread(&maestro, sizeof(tMaestro),1,pf);
    }

    fseek(pf,posOriginal,SEEK_SET);
}

void file_novedades(FILE * pf)
{
    char buff[TAM_LINEA+2];
    tNovedad novedades;

    mostrarNovedades(NULL);

    while(fgets(buff, sizeof(buff),pf))
    {
        trozarCampos(&novedades, buff);
        mostrarNovedades(&novedades);
    }
}

void trozarCampos(tNovedad * novedades,char * buff)
{
    char * aux = buff;

    aux += TAM_LINEA;
    *aux = '\0';

    aux -= TAM_OP;
    sscanf(aux,"%c",&novedades->operacion);
    *aux = '\0';

    aux -= TAM_CANT;
    sscanf(aux,"%02d",&novedades->cantidad);
    *aux = '\0';

    aux -= TAM_ID;
    sscanf(aux,"%02ld",&novedades->idProducto);
    *aux = '\0';

}

void mostrarMaestro(const tMaestro * maestro)
{
      if(maestro == NULL)
    {
        printf("ID\tCANT\tPRECIO\tMIN_REP\tSTATUS\n");
        return;
    }
    printf("%ld\t%d\t$%.2f\t%d\t%c\n",
           maestro->idProducto,
           maestro->cantidad,
           maestro->precioUnitario,
           maestro->minRepo,
           maestro->status);
}

void mostrarNovedades(const tNovedad * novedades)
{
    if(novedades == NULL)
    {
        printf("ID\tCANT\tOP\n");
        return;
    }
    printf("%2ld\t%2d\t%c\n", novedades->idProducto,
           novedades->cantidad,
           novedades->operacion);
}
