#include "diccionario.h"
#include <stdio.h>

int main(void)
{
    Diccionario *D = diccionario_nuevo();
    diccionario_agrega(D, "Linux", "Derivado de unix");
    diccionario_agrega(D, "Windows", "MDOS");
    diccionario_muestra(D);
    const char *letra = diccionario_obtenerValor(D, "Linux");
    printf("%s", letra);
    diccionario_libera(D);
    return 0;
}
