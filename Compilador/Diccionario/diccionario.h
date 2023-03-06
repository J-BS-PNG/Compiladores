#ifndef DICCIONARIO_H
#define DICCIONARIO_H

typedef struct Pareja Pareja;
typedef struct Diccionario Diccionario;

//Estructura de llave valor
struct Pareja{
    const char *llave;
    const char *valor;
};
//Diccionario con datos de la pareja y el tamaño del diccionario.

struct Diccionario
{
    Pareja **pareja;
    int tamanno;
};

//Crea un diccionario
Diccionario *diccionario_nuevo(void);

//obtener un valor
char *diccionario_obtenerValor(Diccionario *D, char *llave);

//Agrega datos al diccionario dando la llave y el valor
void diccionario_agrega(Diccionario *D, const char *llave, const char *valor);

//Enseña por consola los datos del diccionario
void diccionario_muestra(const Diccionario *D);

//Hace que el tamaño del diccionario cresca
void diccionario_aumenta(Diccionario **D, int unidades);

//
void diccionario_copia(const Diccionario *Do, Diccionario *Dd, int unidades);

//Libera la memoria
void diccionario_libera(Diccionario *D);


//inicializacion
void diccionario_inicializa_contenido(Diccionario *D);

#endif // DICCIONARIO_H