#include <stdio.h>
//#include "Diccionario/Diccionario.h"

struct tipo {
    char componente_lexico[100];
    char lexema[10];
}; 




int main(){
    /*Obtener operacion*/
    char comando[20];
    printf("Igrese la operacion");
    scanf("%s", comando);
    printf( "%s\n", comando);
    /*Crear diccionario*/
    //Diccionario* operadores = diccionario_nuevo();

    /*Digitos*/
    

    /*Operaciones*/
    /*struct tipo sumar = {"op_sumar", "+"};
    struct tipo restar = {"op_restar", "-"};
    struct tipo multiplicar= {"op_multiplicar", "*"};
    struct tipo dividir = {"op_dividir", "/"};
    struct tipo elevar = {"op_elevar", "^"};
    struct tipo asignar = {"op_asignar", "="};*/

        

    /*
    Abrir archivo
    Procesar todas las lineas del documento
        Procesar cada palabra de la linea
            Si no es un " ":
                si es numero:
                    mientras sea un digito guardarlo como uno solo
                    guardarlo como numero y su posicion
                si es operador:
                    determinar que tipo de operaddor es
                    guardarlo con su tipo y posición
                si es puntuacion
                si es identificador:
                    si es var:
                        el siguiente es variable
                    
            
    */

    printf("Hello world");

    return 0;
}