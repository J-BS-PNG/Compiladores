#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Diccionario/diccionario.h"

struct pos {
    int x;
    int y;
};

void append_str(char str[] , char c){
     auto char arr[2] = {c , '\0'};
     strcat(str , arr);
}


/*Arrays de las llaves aka los */
    char *DIGITOS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char *OPERADORES[] = {'+', '-', '*', '/', '^', '='};
    char *PUNTUACION[] = {'(',')',','};
    char *IDENTIFICADORES[] = {'calc', '$'}; //tome la decisión administrativa de que  vamos a usar el $ para identificar las variables

bool estaDigito(char c){
    for (int i = 0; i < 10; i++)
    {
        if(DIGITOS[i] == c){
            return true;
        }
    }
    return false;
}

bool estaOperador(char c){
    for (int i = 0; i < 6; i++)
    {
        if(OPERADORES[i] == c){
            return true;
        }
    }
    return false;
}

bool estaPuntacion(char c){
    for (int i = 0; i < 2; i++)
    {
        if(PUNTUACION[i] == c){
            return true;
        }
    }
    return false;
}

bool estaIdentificador(char c){
    for (int i = 0; i < 2; i++)
    {
        if(IDENTIFICADORES[i] == c){
            return true;
        }
    }
    return false;
}

int main(){

    /*Obtener operacion a procesar*/
    char  operacion[30];
    printf("Ingrese la operación: ");
    gets(operacion);
    printf("Ingreso: %s", operacion);
    printf("\n");

    /*Crear diccionarios e inicializarlos*/
    Diccionario *operadores_dic = diccionario_nuevo();

    diccionario_agrega(operadores_dic, "+", "op_sumar");
    diccionario_agrega(operadores_dic, "-", "op_restar");
    diccionario_agrega(operadores_dic, "/", "op_dividir");
    diccionario_agrega(operadores_dic, "*", "op_multiplicar");
    diccionario_agrega(operadores_dic, "^", "op_elevar");
    diccionario_agrega(operadores_dic, "=", "op_asignacion");

    Diccionario *puntuacion_dic = diccionario_nuevo();

    diccionario_agrega(puntuacion_dic, "(", "parentesis_abrir");
    diccionario_agrega(puntuacion_dic, ")", "parentesis_cerrar");
    diccionario_agrega(puntuacion_dic, ",", "separar");

    Diccionario *identificador_dic = diccionario_nuevo();

    diccionario_agrega(identificador_dic, "calc", "hacer_calculo");
    diccionario_agrega(identificador_dic, "$", "identificar_variable");


    char tabla[14][4];
    // columnas: token, tipo, posicion en la linea, en caso de ser variable valor

    int y; //posicion en la linea
    int len = strlen(operacion);
    char num[10];
    char *tipo; // tipo de token especifico
    for(int i = 0; i < len; i++){
        //revisar si el caracter se encuentra en digitos
        // printf("Numero: %i\n", i);
        if(estaDigito(operacion[i])){
            append_str(num, operacion[i]);
        }else if (estaOperador(operacion[i])){
            if(num != '\0'){
                //si la variable num no esta vacia guardar el numero
                printf("Numero:%s\n",num);
            }
            memset(num, 0, 10); // limpia el string
            printf("El caracter es un operador. Caracter: %c", operacion[i]);
            tipo = diccionario_obtenerValor(operadores_dic, operacion[i]);
            printf("El caracter es de tipo: %s", tipo);
            printf("\n"); 
        }else if (estaPuntacion(operacion[i])){
            if(num != '\0'){
                //si la variable num no esta vacia guardar el numero
                printf("Numero:%s\n",num);
            }
            
            printf("El caracter es puntuacion. Caracter: %c", operacion[i]);
            tipo = diccionario_obtenerValor(puntuacion_dic, operacion[i]);
            
            printf("\n");   
        }else if(estaIdentificador(operacion[i])){
            printf("El caracter es IDENTIFICADOR. Caracter: %c", operacion[i]);
            printf("\n"); 
        }

        if(i == len-1){
            printf("Numero:%s\n",num);
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