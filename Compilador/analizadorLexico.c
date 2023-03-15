#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Diccionario/diccionario.h"
#include "estructuraLexico/estructuraLexico.h"

char* append_str(char str[] , char c){
    char arr[2] = {c , '\0'};
    strcat(str , arr);
    return str;
}

/*Arrays de las llaves*/
    char *DIGITOS[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char *OPERADORES[] = {"+", "-", "*", "/", "^", "="};
    char *PUNTUACION[] = {"(",")",","};
    char *IDENTIFICADORES[] = {"calc", "$"}; //tome la decisión administrativa de que  vamos a usar el $ para identificar las variables
    char *FUNCIONES[] = {"sin", "cos", "pi", "e"}; 
    int error = 0;



//Función que revisa si es un digito valido devuelve true
//sino false
bool estaDigito(char c){
    for (int i = 0; i < 10; i++)
    {
        if(DIGITOS[i][0] == c){
            return true;
        }
    }
    return false;
}

bool estaLetra(char c){
    if((c >= 'A' && c <= 'Z')||(c >= 'a' && c<= 'z')){
        return true;
    }
    return false;
}

//Funcón que se confirma si es un operador devuelve True
//sino false
bool estaOperador(char c){
    for (int i = 0; i < 6; i++)
    {
        if(OPERADORES[i][0] == c){
            return true;
        }
    }
    return false;
}

//Función que confirma si es puntación devuelve true
//sino devuelve false
bool estaPuntacion(char c){
    for (int i = 0; i < 3; i++)
    {
        if(PUNTUACION[i][0] == c){
            return true;
        }
    }
    return false;
}


//Función que se confirma si es un identificador devuelve true
//sino false
bool estaIdentificador(char c){
    for (int i = 0; i < 2; i++)
    {
        if(IDENTIFICADORES[i][0] == c){
            return true;
        }
    }
    return false;
}

/*
################################################################################
#                           Analizardor sintactico                             #
################################################################################
*/

Tokens *expTokemizada;

//Función para obtener tokens
Tokens *getToken(){
    if(strcmp(expTokemizada -> token, "#")){
        Tokens *token = expTokemizada;
        expTokemizada = getNextToken(expTokemizada);
        return token;
    }
    return expTokemizada;
    
}

//Retorna posicion del token
void retToken(){
    expTokemizada = getPastToken(expTokemizada);
}

bool esNumero(){
    return false;
}

//Se declaran antes para no tener errores
/*

*/
float term();
float factor();
float pot();
float errorSintactico();

float expr(){
    float val = term();
    Tokens *op = getToken();
    while(!strcmp(op -> token, "+") || !strcmp(op -> token, "-")){
        if(!strcmp(op -> token, "-")){
            val = val - term();
        }else{
            val = val + term();
        }
        op = getToken();
    }
    retToken();
    return val;
}

float term(){
    float val = factor();
    Tokens *op = getToken();
    while (!strcmp(op -> token, "*") || !strcmp(op -> token, "/" )){
        if (!strcmp(op -> token, "*")){
            val = val * factor();
        }else{
            val = val / factor();
        }
        op = getToken();
    }
    retToken();
    return val;
}

float factor(){
    float val = pot();
    Tokens *op = getToken();
    while (!strcmp(op -> token, "^")){
        val = pow(val, pot());
        op = getToken();
    }
    retToken();
    return val;
}

float pot(){
    Tokens *c = getToken();
    if(!strcmp(c ->tipo, "num")){
        float newVal = (float)(c->val);
        return newVal;
    }else if(!strcmp(c -> token, "(")){
        float val = expr();
        if (strcmp(getToken()->token, ")")){
            printf("Error");
        }else{
            return val;
        }
    }else if(!strcmp(c ->tipo, "fun")){
        float val = expr();
        if (strcmp(getToken()->token, ")")){
            printf("Error");
        }else{
            if(!strcmp(c ->token, "in(")){
                return log10(val);
            }else if(!strcmp(c ->token, "sin(")){
                return sin(val);
            }else if(!strcmp(c ->token, "cos(")){
                return cos(val);
            }else if(!strcmp(c ->token, "exp(")){
                return exp(val);
            }else{
                printf("Error");
            }
        }
    }else{
        retToken();
    }
    return 0; /// revisar
}

/*
################################################################################
#                          FIN ANALIZADOR SINTACTICO                           #
################################################################################
*/

int main(){
    /*Obtener operacion a procesar*/
    char  operacion[30];
    printf("Ingrese la operación: ");
    scanf("%s", operacion);
    //gets(operacion);


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

    Diccionario *funcion_dic = diccionario_nuevo();

    diccionario_agrega(funcion_dic, "sin(", "trigonometrica_sen"); 
    diccionario_agrega(funcion_dic, "cos(", "trigonometrica_cos");
    diccionario_agrega(funcion_dic, "exp(", "exponencial");
    diccionario_agrega(funcion_dic, "ln(", "logaritmo_natural");
    diccionario_agrega(funcion_dic, "pi", "num"); 
    diccionario_agrega(funcion_dic, "e", "num");

    Tokens* tokenActual = crear_token(NULL, NULL, 0, 0.0); //se inicializan los token y el primero se establece como null

    int y = 0; //posicion en la linea
    int comaFloat  = 0;
    
    int len = strlen(operacion);//tamaño de la linea
    const char *tipo; // tipo de token especifico
    
    for(int i = 0; i < len && error == 0; i++){
        if(estaDigito(operacion[i])){//si el token esta en la lista digitos
            char num[10] = "";//variable para los numeros no se pueden ingresar numeros de mas de 10 digitos
            float entero = 0; //valor entero de los numeros y las variables
            int j = i;
            while(j < len)
            {   
                if(estaDigito(operacion[j])){
                    append_str(num, operacion[j]); //se agrega a la variable num
                }else if(operacion[j] == '.'){
                    if(comaFloat == 0){
                        append_str(num, operacion[j]);
                        comaFloat++;
                    }
                    else{
                        error = 1;
                        break;
                    }
                    
                }else{
                    break;
                }
                j++;
            }
            //convertir el numero a entero
            entero = atof(num);
            comaFloat = 0;
            //guardar en token
            char *numDinamico = (char*) malloc(strlen(num)*sizeof(char));
            strcpy(numDinamico, num);
            tokenActual = agregar_token(tokenActual, numDinamico, "num", y, entero);
            // printToken(tokenActual);
            //aumentar la posicion de la linea
            i = j-1;
            y++;
        }
        else if (estaOperador(operacion[i])){ //si el token esta en la lista operadores
            
            // printf("El caracter es un operador. Caracter: %c\n", operacion[i]);
            char operadorS[2] = "";
            append_str(operadorS, operacion[i]);
            char *operadorDinamico = (char*) malloc(2*sizeof(char));
            strcpy(operadorDinamico, operadorS);
            tipo = diccionario_obtenerValor(operadores_dic, operadorDinamico);//obtiene la descripcion del token
            tokenActual = agregar_token(tokenActual, operadorDinamico, (char*) tipo, y, 0.0);
            // printToken(tokenActual);
            y++;

        }
        else if (estaPuntacion(operacion[i])){//si eltoken esta en la lista puntuación
            // printf("El caracter es puntuacion. Caracter: %c\n", operacion[i]);
            char puntuacionS[2] = "";
            append_str(puntuacionS, operacion[i]);
            char *puntuacionDinamico = (char*) malloc(2*sizeof(char));
            strcpy(puntuacionDinamico, puntuacionS);
            tipo = diccionario_obtenerValor(puntuacion_dic, puntuacionDinamico);//obtiene la descripcion del token
            tokenActual = agregar_token(tokenActual, puntuacionDinamico, (char*)tipo, y, 0.0);
            y++;


            
        }
        else if(estaLetra(operacion[i])){ ////si el token esta en la lista identificador
            char palabra[10] = "";//variable para los numeros no se pueden ingresar numeros de mas de 10 digitos
            //float entero = 0; //valor entero de los numeros y las variables
            int j = i;
            while(j < len)
            {   
                if(estaLetra(operacion[j])){
                    append_str(palabra, operacion[j]); //se agrega a la variable num
                }else if(estaPuntacion(operacion[j])){
                    append_str(palabra, operacion[j]);
                
                }else{
                    break;
                }
                j++;
            }
            char *funcionDinamico = (char*) malloc(10*sizeof(char));
            strcpy(funcionDinamico, palabra);
            tipo = diccionario_obtenerValor(funcion_dic, funcionDinamico);//obtiene la descripcion del token
            if(!strcmp(tipo, "num")){
                if(!strcmp(funcionDinamico, "pi")){
                    tokenActual = agregar_token(tokenActual, funcionDinamico, (char*)tipo, y, acos(-1.0));

                }else{
                    tokenActual = agregar_token(tokenActual, funcionDinamico, (char*)tipo, y, 2.718281828459045);
                }
            }else{
                tokenActual = agregar_token(tokenActual, funcionDinamico, (char*)tipo, y, 0.0);
            }
            //aumentar la posicion de la linea
            printf("%s", tipo);
            i = j-1;
            y++;

        }
    }
    tokenActual = agregar_token(tokenActual, "#", "End", y, 0.0);
    //Imprime todos los datos de la estructura que almacena los tokens
    printf("\nPresentacon de datos\n");
    expTokemizada = comeToFirstValue(tokenActual);
    printAllTokens(expTokemizada);
    
    if(error != 0){
        printf("Error");
    }else{
        float temp = expr();
        printf("\n%f", temp);
    }

    return 0;
}