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

// Da aggiustare
void F_elimina_elemento_coda_in_testa(Coda *C){
    if(!F_struttura_vuota(*C)){
        puts("A");
        Coda *elementoDaEliminare=C;
        Studenti S=(*elementoDaEliminare)->studentePrt;
        printf("\nEL|%d|\n",S->matricola);

        if(!F_struttura_vuota((*C)->nextPrt)){
            (*C)=(*C)->nextPrt;
            S=(*C)->studentePrt;
            printf("\nNT|%d|\n",S->matricola);
        }
        (*elementoDaEliminare)->nextPrt=NULL;
        (*elementoDaEliminare)->studentePrt=NULL;
        (*elementoDaEliminare)->libroPtr=NULL;
        free(*elementoDaEliminare);
        puts("B");
    }

    /*puts("A");
    Coda elementoDaEliminare=(*C);
    (*C)=(*C)->nextPrt;
    puts("B");
    Studenti S=elementoDaEliminare->studentePrt;
    printf("\nEL|%d|",S->matricola);
    elementoDaEliminare->nextPrt=NULL;
    elementoDaEliminare->studentePrt=NULL;
    elementoDaEliminare->libroPtr=NULL;
    puts("C");
    free(elementoDaEliminare);
    S=(*C)->studentePrt;
    printf("\nNUOVATESTA:|%d|",S->matricola);*/
}