#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Diccionario/diccionario.h"

//************************************************************************************
// estructura que almacena los datos de los tokens
///me volé
typedef struct 
{
    char*token;
    char* tipo;
    int* posY;
    int* val;

    struct Token* past;
    struct Token* next;

}Tokens;

Tokens* crear_token(char* pToken, char* pTipo, int* pPosY, int* pVal){
    Tokens* newToken = malloc(sizeof(Tokens));
    if(NULL != newToken){
        newToken->token = pToken;
        newToken->tipo = pTipo;
        newToken->posY = pPosY;
        newToken->val = pVal;
        newToken->past = NULL;
        newToken->next = NULL;
    }
    return newToken;

}

Tokens* agregar_token(Tokens* tablaTokens, char* pToken, char* pTipo, int* pPosY, int* pVal){
    Tokens* newToken = crear_token(pToken, pTipo, pPosY, pVal);
    if(NULL != newToken){
        tablaTokens->next = newToken;
        newToken->past = tablaTokens;
    }
    return newToken;

}

void printToken(Tokens* tablaTokens){
    printf(" %c ", tablaTokens->token);
    printf(" %s ", tablaTokens->tipo);
    printf(" %i ", tablaTokens->posY);
    printf(" %i ", tablaTokens->val);

}

Tokens* getPastToken(Tokens* tablaTokens){
    if(tablaTokens->past == NULL){
        printf("NO EXISTE TOKEN ANTERIOR, INICIO DE LA LISTA");
        return tablaTokens;
    }

    return tablaTokens->past;
}

Tokens* getNextToken(Tokens* tablaTokens){
    if(tablaTokens->next == NULL){
        printf("NO EXISTE TOKEN SIGUIENTE, FINAL DE LA LISTA");
        return tablaTokens;
    }
    
    return tablaTokens->next;
}

//************************************************************************************************
void append_str(char str[] , char c){
     auto char arr[2] = {c , '\0'};
     strcat(str , arr);
}


/*Arrays de las llaves*/
    char *DIGITOS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char *OPERADORES[] = {'+', '-', '*', '/', '^', '='};
    char *PUNTUACION[] = {'(',')',','};
    char *IDENTIFICADORES[] = {"calc", '$'}; //tome la decisión administrativa de que  vamos a usar el $ para identificar las variables


//Funciones que revisan si el token que se esta revizando existe en el lenguaje
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
    for (int i = 0; i < 3; i++)
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
//PRUEBAS TOKENS
 /*   Tokens* misTokens= crear_token(NULL, NULL, NULL, NULL);//token vacio para inicializar la estructura
    misTokens = agregar_token(misTokens, '5', "int", 0, 5);
    printToken(misTokens);
    printf("\n");

    misTokens = agregar_token(misTokens, '+', "op_suma", 1, NULL);
    printToken(misTokens);
    printf("\n");

    misTokens = agregar_token(misTokens, '8', "int", 2, 8);
    printToken(misTokens);
    printf("\n");

    misTokens =getNextToken(misTokens);
    printToken(misTokens);
    printf("\n");
    
    misTokens =getPastToken(misTokens);
    printToken(misTokens);
    printf("\n");*/

    /*Tokens* iterador;

    for(iterador = misTokens; NULL != iterador; iterador = iterador->next){
        printf("%s", iterador->token);
    }*/
/********************************************************************************************/
    //printf("%s\n", tabla[1].token);

    /*Obtener operacion a procesar*/
    char  operacion[30];
    printf("Ingrese la operación: ");
    gets(operacion);


    /*Crear diccionarios e inicializarlos*/
    Diccionario *operadores_dic = diccionario_nuevo();

    diccionario_agrega(operadores_dic, '+', "op_sumar");
    diccionario_agrega(operadores_dic, '-', "op_restar");
    diccionario_agrega(operadores_dic, '/', "op_dividir");
    diccionario_agrega(operadores_dic, '*', "op_multiplicar");
    diccionario_agrega(operadores_dic, '^', "op_elevar");
    diccionario_agrega(operadores_dic, '=', "op_asignacion");

    Diccionario *puntuacion_dic = diccionario_nuevo();

    diccionario_agrega(puntuacion_dic, '(', "parentesis_abrir");
    diccionario_agrega(puntuacion_dic, ')', "parentesis_cerrar");
    diccionario_agrega(puntuacion_dic, ',', "separar");

    Diccionario *identificador_dic = diccionario_nuevo();

    diccionario_agrega(identificador_dic, "calc", "hacer_calculo");
    diccionario_agrega(identificador_dic, '$', "identificar_variable");

    Tokens* tokenActual = crear_token(NULL, NULL, NULL, NULL); //se inicializan los token y el primero se establece como null

    int y = 0; //posicion en la linea
    int entero; //valor entero de los numeros y las variables
    int len = strlen(operacion);//tamaño de la linea
    char num[10];//variable para los numeros no se pueden ingresar numeros de mas de 10 digitos
    const char *tipo; // tipo de token especifico
    
    for(int i = 0; i < len; i++){

        if(estaDigito(operacion[i])){//si el token esta en la lista digitos
            append_str(num, operacion[i]); //seagrega a la variable num
        }
        else if (estaOperador(operacion[i])){ //si el token esta en la lista operadores
            if(num != '\0'){ 
                //si la variable num no esta vacia guardar el numero
                printf("Numero:%s\n",num);
                //convertir el numero a entero
                entero = atoi(num);
                //guardar en token
                tokenActual = agregar_token(tokenActual, num, "int", y, entero);
                printToken(tokenActual);
                //aumentar la posicion de la linea
                y++;
                entero = 0;
                memset(num, 0, 10); // limpia el string
                
            }

            //guardar en token
            //aumentar la posicion de la linea
            printf("El caracter es un operador. Caracter: %c\n", operacion[i]);
            tipo = diccionario_obtenerValor(operadores_dic, operacion[i]);//obtiene la descripcion del token
            tokenActual = agregar_token(tokenActual, operacion[i], tipo, y, NULL);
            printToken(tokenActual);
            y++;
            printf("\nEl caracter es de tipo: %s", tipo);
            printf("\n"); 
        }
        else if (estaPuntacion(operacion[i])){//si eltoken esta en la lista puntuación
            if(num != '\0'){
                //si la variable num no esta vacia guardar el numero
                printf("Numero:%s\n",num);
                //convertir el numero a entero
                entero = atoi(num);
                //guardar en token
                tokenActual = agregar_token(tokenActual, num, "int", y, entero);
                printToken(tokenActual);
                //aumentar la posicion de la linea
                y++;
                entero = 0;
                memset(num, 0, 10); // limpia el string
            }
            //guardar en token
            //aumentar la posicion de la linea
            printf("El caracter es puntuacion. Caracter: %c\n", operacion[i]);
            tipo = diccionario_obtenerValor(puntuacion_dic, operacion[i]);//obtiene la descripcion del token
            tokenActual = agregar_token(tokenActual, operacion[i], tipo, y, NULL);
            printToken(tokenActual);
            y++;
            printf("\nEl caracter es de tipo: %s", tipo);
            printf("\n");   
            
        }
        else if(estaIdentificador(operacion[i])){ ////si el token esta en la lista identificador
            if(num != '\0'){
                //si la variable num no esta vacia guardar el numero
                printf("Numero:%s\n",num);
                //convertir el numero a entero
                entero = atoi(num);
                //guardar en token
                tokenActual = agregar_token(tokenActual, num, "int", y, entero);
                printToken(tokenActual);
                //aumentar la posicion de la linea
                y++;
                entero = 0;
                memset(num, 0, 10); // limpia el string
            }
            
            //guardar en token
            //aumentar la posicion de la linea

            printf("El caracter es IDENTIFICADOR. Caracter: %c", operacion[i]);
            tipo = diccionario_obtenerValor(identificador_dic, operacion[i]); // obtiene la descripcion del token 
            y++;
            printf("\nEl caracter es de tipo: %s", tipo);
            printf("\n"); 
        }

        if(i == len-1){
            //si la variable num no esta vacia guardar el numero
            printf("Numero:%s\n",num);
            //convertir el numero a entero
            entero = atoi(num);
            //guardar en token
            tokenActual = agregar_token(tokenActual, num, "int", y, entero);
            printToken(tokenActual);
            //aumentar la posicion de la linea
            y++;
            entero = 0;
            memset(num, 0, 10); // limpia el string
        }
    }
    Tokens* iterador;
    for(iterador = tokenActual; NULL != iterador; iterador = iterador->next){
        printf("%c", iterador->token);
    }
    



    return 0;
}