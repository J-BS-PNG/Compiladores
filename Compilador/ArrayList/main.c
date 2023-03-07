#include "arraylist.h"
#include <stdio.h>

int main()
{
    arraylist *mylist = arraylist_create();
    arraylist *dato = arraylist_create();
    arraylist_add(dato, "Hola");
    arraylist_add(mylist, dato);
    void *l = arraylist_pop(mylist);
    char *pal;
    pal = (char *)l;
    printf("%s", pal);
    return 0;
}
