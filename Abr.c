#include <stdio.h>
#include <stdlib.h>
#include "Biblioteca.h"
#include "Error.h"
#include "Abr.h"


void F_alloca_struttura_albero(Albero *T){
    (*T)=(struct struttura_elemento_albero*)malloc(sizeof(struct struttura_elemento_albero));
    if(F_struttura_vuota(T)) F_error(3);
    (*T)->datiBibliotecaPtr=NULL;
    (*T)->dxPtr=NULL;
    (*T)->dxPtr=NULL;
}