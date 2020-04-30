#include "Biblioteca.h"
#include <string.h>
#include <stdio.h>


void F_test();

int main() {
   // F_test();
    F_gestione_biblioteca();
    return 0;
}


void F_test(){
    char *a="Simone", *b="Sa";
    int r=strcmp(a,b);
    if(r>0) puts("1");
    else puts("2");
}