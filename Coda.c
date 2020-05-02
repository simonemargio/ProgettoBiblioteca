#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Coda.h"


void F_alloca_elemento_coda(Coda *C){
    (*C)=(struct struttura_elemento_coda*)malloc(sizeof(struct struttura_elemento_coda));
    (*C)->codaLibro=NULL;
    (*C)->codaStudente= NULL;
    (*C)->nextPrt=NULL;
}

void F_inserimento_in_coda_richieste_studente(Coda *C, Studente studenteDaInserire, Libro libroDaInserire){
    if(F_struttura_vuota(*C)) {
        F_alloca_elemento_coda(C);
        (*C)->codaLibro=libroDaInserire;
        (*C)->codaStudente=studenteDaInserire;
    }else{
        F_inserimento_in_coda_richieste_studente((&(*C)->nextPrt),studenteDaInserire,libroDaInserire);
    }
}

void F_elimina_elemento_coda_in_testa(Coda *C){
    if(!F_struttura_vuota(*C)){
        Coda elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPrt;
        free(elementoDaEliminare);
    }
}


int F_cerca_elemento_coda(Coda *C, int matricola, char *titoloLibro){
    if(F_struttura_vuota(*C)) return 0;
    Studente S=(*C)->codaStudente;
    Libro L=(*C)->codaLibro;
    int confrontoTitoliLibro=strcmp(L->titoloPtr,titoloLibro);
    if(S->matricola==matricola && confrontoTitoliLibro==0) return 1;
    return F_cerca_elemento_coda((&(*C)->nextPrt),matricola,titoloLibro);
}

Coda F_elimina_elemento_coda(Coda C, int matricola, char *titoloLibro){
    if(!F_struttura_vuota(C)){
        Studente S=C->codaStudente;
        Libro L=C->codaLibro;
        int confrontoTitoliLibro=strcmp(L->titoloPtr,titoloLibro);
        if(S->matricola==matricola && confrontoTitoliLibro==0){
            Coda salvaNextPtr=C->nextPrt;
            free(C);
            return salvaNextPtr;
        } else C->nextPrt=F_elimina_elemento_coda(C->nextPrt,matricola,titoloLibro);
    }
    return C;
}