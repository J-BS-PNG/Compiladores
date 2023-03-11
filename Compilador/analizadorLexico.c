#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Diccionario/diccionario.h"

//************************************************************************************
// estructura que almacena los datos de los tokens
///me volé
typedef struct 
{
    char* token;
    char* tipo;
    int* posY;
    int val;

    struct Tokens* past;
    struct Tokens* next;
    

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

Tokens* agregar_token(Tokens* tablaTokens, char* pToken, char* pTipo, int* pPosY, int pVal){
    if(tablaTokens->token == NULL){
        tablaTokens->token = pToken;
        tablaTokens->tipo = pTipo;
        tablaTokens->posY = pPosY;
        tablaTokens->val = pVal;
        return tablaTokens;
    } else {
        Tokens* newToken;
        newToken = crear_token(pToken, pTipo, pPosY, pVal);
        if(NULL != newToken){
            tablaTokens->next = newToken;
            newToken->past = tablaTokens;
        }
        return newToken;
    }

}

void printToken(Tokens* tablaTokens){
    printf(" %s ", tablaTokens->token);
    printf(" %s ", tablaTokens->tipo);
    printf(" %i ", tablaTokens->posY);
    printf(" %i \n", tablaTokens->val);

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

Tokens* comeToFirstValue(Tokens* tablaTokens){
    Tokens* aux;
    if(tablaTokens->past == NULL){
        return tablaTokens;
    }else{
        return comeToFirstValue(tablaTokens->past);
    }
}

//************************************************************************************************
char* append_str(char str[] , char c){
    char arr[2] = {c , '\0'};
    strcat(str , arr);
    return str;
}

/*Arrays de las llaves*/
    char *DIGITOS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char *OPERADORES[] = {'+', '-', '*', '/', '^', '='};
    char *PUNTUACION[] = {'(',')',','};
    char *IDENTIFICADORES[] = {"calc", '$'}; //tome la decisión administrativa de que  vamos a usar el $ para identificar las variables


//Función que revisa si es un digito valido devuelve true
//sino false
bool estaDigito(char c){
    for (int i = 0; i < 10; i++)
    {
        if(DIGITOS[i] == c){
            return true;
        }
    }
    return false;
}

//Funcón que se confirma si es un operador devuelve True
//sino false
bool estaOperador(char c){
    for (int i = 0; i < 6; i++)
    {
        if(OPERADORES[i] == c){
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
        if(PUNTUACION[i] == c){
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
        if(IDENTIFICADORES[i] == c){
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

void retToken(){
    expTokemizada = getPastToken(expTokemizada);
}

bool esNumero(){
    return false;
}

//Se declaran antes para no tener errores
float term();
float factor();
float pot();

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
    while (!strcmp(op -> token, "*") || !strcmp(op -> token, "/")){
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
    if(c->val != NULL){
        float newVal = (float)(c->val);
        return newVal;
    }else if(!strcmp(c -> token, "(")){
        float val = expr();
        if (strcmp(getToken()->token, ")")){
            printf("Error");
        }else{
            return val;
        }
    }else{
        retToken();
    }
}

/*
################################################################################
#                          FIN ANALIZADOR SINTACTICO                           #
################################################################################
*/

int main(){
//PRUEBAS TOKENS
    // Tokens* misTokens= crear_token(NULL, NULL, NULL, NULL);//token vacio para inicializar la estructura
    // misTokens = agregar_token(misTokens, "5", "int", 0, 5);
    // printToken(misTokens);
    // printf("\n");

    // misTokens = agregar_token(misTokens, "+", "op_suma", 1, NULL);
    // printToken(misTokens);
    // printf("\n");

    // misTokens = agregar_token(misTokens, "8", "int", 2, 8);
    // printToken(misTokens);
    // printf("\n");

    // misTokens =getNextToken(misTokens);
    // printToken(misTokens);
    // printf("\n");
    
    // misTokens =getPastToken(misTokens);
    // printToken(misTokens);
    // printf("\n");

    // misTokens =getPastToken(misTokens);
    // printToken(misTokens);
    // printf("\n");

    // misTokens =getPastToken(misTokens);
    // printToken(misTokens);
    // printf("\n");

    /*Tokens* iterador;

    for(iterador = misTokens; NULL != iterador; iterador = iterador->next){
        printf("%s", iterador->token);
    }*/
/********************************************************************************************/
    //printf("%s\n", tabla[1].token);

    /*Obtener operacion a procesar*/
    char  operacion[30];
    printf("Ingrese la operación: ");
    scanf("%s", &operacion);
    //gets(operacion);


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
    
    int len = strlen(operacion);//tamaño de la linea
    const char *tipo; // tipo de token especifico
    
    
    for(int i = 0; i < len; i++){
        if(estaDigito(operacion[i])){//si el token esta en la lista digitos
            char num[10] = "";//variable para los numeros no se pueden ingresar numeros de mas de 10 digitos
            int entero = 0; //valor entero de los numeros y las variables
            int j = i;
            while (j < len && estaDigito(operacion[j]))
            {
                append_str(num, operacion[j]); //seagrega a la variable num
                j++;
            }
            //convertir el numero a entero
            entero = atoi(num);

            //guardar en token
            char *numDinamico = (char*) malloc(strlen(num)*sizeof(char));
            strcpy(numDinamico, num);
            tokenActual = agregar_token(tokenActual, numDinamico, "int", y, entero);
            // printToken(tokenActual);
            //aumentar la posicion de la linea
            i = j-1;
            y++;
        }
        else if (estaOperador(operacion[i])){ //si el token esta en la lista operadores
            //guardar en token
            //aumentar la posicion de la linea
            // printf("El caracter es un operador. Caracter: %c\n", operacion[i]);
            tipo = diccionario_obtenerValor(operadores_dic, operacion[i]);//obtiene la descripcion del token
            char operadorS[2] = "";
            append_str(operadorS, operacion[i]);
            char *operadorDinamico = (char*) malloc(2*sizeof(char));
            strcpy(operadorDinamico, operadorS);
            tokenActual = agregar_token(tokenActual, operadorDinamico, tipo, y, NULL);
            // printToken(tokenActual);
            Tokens *nuevo = getPastToken(tokenActual);
            // printToken(nuevo);
            y++;
            // printf("\nEl caracter es de tipo: %s", tipo);
            // printf("\n"); 
        }
        else if (estaPuntacion(operacion[i])){//si eltoken esta en la lista puntuación
            //guardar en token
            //aumentar la posicion de la linea
            // printf("El caracter es puntuacion. Caracter: %c\n", operacion[i]);
            tipo = diccionario_obtenerValor(puntuacion_dic, operacion[i]);//obtiene la descripcion del token
            char puntuacionS[2] = "";
            append_str(puntuacionS, operacion[i]);
            char *puntuacionDinamico = (char*) malloc(2*sizeof(char));
            strcpy(puntuacionDinamico, puntuacionS);
            tokenActual = agregar_token(tokenActual, puntuacionDinamico, tipo, y, NULL);
            // printToken(tokenActual);
            y++;
            // printf("\nEl caracter es de tipo: %s", tipo);
            // printf("\n");   
            
        }
        else if(estaIdentificador(operacion[i])){ ////si el token esta en la lista identificador
            //guardar en token
            //aumentar la posicion de la linea
            // printf("El caracter es IDENTIFICADOR. Caracter: %c", operacion[i]);
            tipo = diccionario_obtenerValor(identificador_dic, operacion[i]); // obtiene la descripcion del token 
            y++;
            // printf("\nEl caracter es de tipo: %s", tipo);
            // printf("\n"); 
        }
    }
    Tokens* iterador;
    tokenActual = agregar_token(tokenActual, "#", "Final", y, NULL);
    //Imprime todos los datos de la estructura que almacena los tokens
    printf("\nPresentacon de datos\n");
    expTokemizada = comeToFirstValue(tokenActual);
    for(iterador = expTokemizada; NULL != iterador; iterador = iterador->next){
        if(!strcmp(iterador->token, "+")){
            printToken(iterador);
        }
    }
    //Parte del analizador sintactico
    float temp = expr();
    printf("\n%f", temp);
    // printf("Primero\n");
    // printToken(expTokemizada);

    return 0;
}