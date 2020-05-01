#include <stdio.h>
#include <stdlib.h>
#include "Biblioteca.h"
#include "Coda.h"


void F_alloca_elemento_coda(Coda *C){
    (*C)=(struct struttura_elemento_coda*)malloc(sizeof(struct struttura_elemento_coda));
    (*C)->studentePrt=NULL;
    (*C)->libroPtr= NULL;
    (*C)->nextPrt=NULL;
}

void F_inserimento_in_coda(Coda *C, void *studenteDaInserireInCoda, void *libroPresoDalloStutente){
    if(F_struttura_vuota(*C)){
        F_alloca_elemento_coda(C);
        (*C)->studentePrt=studenteDaInserireInCoda;
        (*C)->libroPtr=libroPresoDalloStutente;
    }else{
        F_inserimento_in_coda((&(*C)->nextPrt),studenteDaInserireInCoda,libroPresoDalloStutente);
    }
}


