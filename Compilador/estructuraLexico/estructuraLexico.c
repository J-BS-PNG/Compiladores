#include "estructuraLexico.h"
#include <stdio.h>
#include <stdlib.h>
//************************************************************************************
// Estructura que almacena los datos de los tokens
///me volé

Tokens* crear_token(char* pToken, char* pTipo, int pPosY, float pVal){
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

Tokens* agregar_token(Tokens* tablaTokens, char* pToken, char* pTipo, int pPosY, float pVal){
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
    printf(" %f \n", tablaTokens->val);


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
    if(tablaTokens->past == NULL){
        return tablaTokens;
    }else{
        return comeToFirstValue(tablaTokens->past);
    }
}

void printAllTokens(Tokens *tablaTokens){
    Tokens* iterador;
    for(iterador = tablaTokens; NULL != iterador; iterador = iterador->next){
        printToken(iterador);
    }
}

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

//************************************************************************************************
