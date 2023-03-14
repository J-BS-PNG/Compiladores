#ifndef ESTRUCTURALEXICO_H
#define ESTRUCTURALEXICO_H

typedef struct Token
{
    char* token;
    char* tipo;   
    int posY;
    float val;

    struct Token* past;
    struct Token* next;
    

}Tokens;

Tokens* crear_token(char* pToken, char* pTipo, int pPosY, float pVal);

Tokens* agregar_token(Tokens* tablaTokens, char* pToken, char* pTipo, int pPosY, float pVal);

void printToken(Tokens* tablaTokens);

Tokens* getPastToken(Tokens* tablaTokens);

Tokens* getNextToken(Tokens* tablaTokens);

Tokens* comeToFirstValue(Tokens* tablaTokens);

void printAllTokens(Tokens *tablaTokens);

#endif // ESTRUCTURALEXICO_H