#include <stdio.h>
#include <stdlib.h>



int contiene(char *arr[], char componenteLexico[]){
    //printf(componenteLexico);
    for (int i = 0; i < sizeof(arr); i++){
        printf(arr[i]);
        /*if(arr[i] == componenteLexico){
            return 1; //true
        }*/
    }
    return 0; //false
};


int main(){
    /*Obtener operacion*/
    char comando[20];
    printf("Igrese la operacion");
    scanf("%s", comando);
    printf( "%s\n", comando);

    /*Crear diccionario*/
    //Diccionario* operadores = diccionario_nuevo();

    /*Arrays de las llaves aka los */
    char *DIGITOS[1][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char *OPERADORES[1][6] = {"+", "-", "*", "/", "^", "="};
    char *PUNTUACION[1][2] = {"(", ")"};
    char *IDENTIFICADORES[4][2] = {"calc", "$"}; //tome la decisión administrativa de que  vamos a usar el $ para identificar las variables
    

   //printf(strlen(comando));
    
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