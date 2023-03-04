#include "diccionario.h"

int main(void)
{
    Diccionario *D = diccionario_nuevo();
    diccionario_agrega(D, "Linux", "Derivado de unix");
    diccionario_agrega(D, "Windows", "MDOS");
    diccionario_muestra(D);
    diccionario_libera(D);
    return 0;
}
