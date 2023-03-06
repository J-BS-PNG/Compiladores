#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Diccionario/diccionario.h"

struct pos {
    int x;
    int y;
};

int main(){

    /*Obtener operacion a procesar*/
    char  operacion[30];
    printf("Ingrese la operación: ");
    gets(operacion);
    printf("Ingreso: %s", operacion);
    printf("\n");

    /*Crear diccionario*/
  //  Diccionario* operadores = diccionario_nuevo();

    /*Arrays de las llaves aka los */
    char * DIGITOS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char * OPERADORES[] = {'+', '-', '*', '/', '^', '='};
    char * PUNTUACION[] = {'(',')'};
    char * IDENTIFICADORES[] = {'calc', '$'}; //tome la decisión administrativa de que  vamos a usar el $ para identificar las variables

    int x;
    int len = strlen(operacion);
    for(int i = 0; i < len; i++){
        //revisar si el caracter se encuentra en digitos    
        for(int j = 0; j < 10; j++){
            if(DIGITOS[j] == operacion[i]){
                char * num[10] = {};
                x = 0;
                while(DIGITOS[j] == operacion[i]){
                    printf("El caracter es un digito. Caracter: %c", operacion[i]);
                    printf("\n");
                    num[x] = operacion[i];
                    x++;
                    j++;
                    i++;
                }
                for (int y = 0; y < 3; y++){
                        
                    printf("%c", num[y]);
                }
                printf("\n");
                break;
            }
            if(OPERADORES[j] == operacion[i]){
                printf("El caracter es un oeprador. Caracter: %c", operacion[i]);
                printf("\n");  
                break;            
            }
            if(PUNTUACION[j] == operacion[i]){
                printf("El caracter es puntuacion. Caracter: %c", operacion[i]);
                printf("\n");   
                break;           
            }
            if(IDENTIFICADORES[j] == operacion[i]){
                printf("El caracter es IDENTIFICADOR. Caracter: %c", operacion[i]);
                printf("\n");   
                break;           
            }
        }
        
    }

    
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

    return 0;
}