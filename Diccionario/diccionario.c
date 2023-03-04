#include "diccionario.h"
#include <stdlib.h>
#include <stdio.h>

//Crea un diccionario
Diccionario *diccionario_nuevo(void){
    Diccionario *D = (Diccionario *) malloc(sizeof(Diccionario));
    D->pareja = NULL;
    D->tamanno = 0;
    return D;
}

//Agrega datos al diccionario dando la llave y el valor
void diccionario_agrega(Diccionario *D, const char *llave, const char *valor){
    diccionario_aumenta(&D, 1);
    D->pareja[D->tamanno - 1]->llave = llave;
    D->pareja[D->tamanno - 1]->valor = valor;

}

//Enseña por consola los datos del diccionario
void diccionario_muestra(const Diccionario *D){
    for(int i = 0; i < D->tamanno; ++i){
        printf("%s: %s\n", D->pareja[i]->llave, D->pareja[i]->valor);
    }
}

//Hace que el tamaño del diccionario cresca
void diccionario_aumenta(Diccionario **D, int unidades){
    Diccionario *E = diccionario_nuevo();
    E->tamanno = (**D).tamanno;
    E->pareja =  (Pareja**) calloc (E->tamanno, sizeof(Pareja));
    diccionario_inicializa_contenido(E);
    diccionario_copia(*D, E, E->tamanno);
    diccionario_libera(*D);
    *D = diccionario_nuevo();
    (**D).tamanno = E->tamanno + unidades;
    (**D).pareja = (Pareja **) calloc((**D).tamanno, sizeof(Pareja));
    diccionario_inicializa_contenido(*D);
    diccionario_copia(E, *D, E->tamanno);
    diccionario_libera(E);

}

//
void diccionario_copia(const Diccionario *Do, Diccionario *Dd, int unidades){
    for (int  i = 0; i < unidades; ++i)
    {
        Dd->pareja[i]->llave = Do->pareja[i]->llave;
        Dd->pareja[i]->valor = Do->pareja[i]->valor;
    }
    
}

//Libera la memoria
void diccionario_libera(Diccionario *D){
    for (int i = 0; i < D->tamanno; ++i)
    {
        free(D->pareja[i]);
    }
    free(D->pareja);
    free(D);
    
}

void diccionario_inicializa_contenido(Diccionario *D){
    for (int i = 0; i < D->tamanno; ++i){
        D->pareja[i] = (Pareja *) malloc(sizeof(Pareja));
        D->pareja[i]->llave = NULL;
        D->pareja[i]->valor = NULL;
    }
    
}