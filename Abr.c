#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Error.h"
#include "Abr.h"

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_inserisci_libro_abr(AlberoLibro *T, Libro libroDaInserire){
    if(F_struttura_vuota(*T)){
        F_alloca_struttura_libro_abr(T);
        (*T)->nodoLibroPtr=libroDaInserire;
    }else{
        Libro libroAlbero=(*T)->nodoLibroPtr;
        int confrontoLibri=F_cofronto_titolo_libri(libroDaInserire->titoloPtr,libroAlbero->titoloPtr);
        if(confrontoLibri<0) F_inserisci_libro_abr((&(*T)->sxPtr),libroDaInserire);
        else if(confrontoLibri==0) libroAlbero->copie=libroAlbero->copie+1; // Si aggiunge lo stesso libro, si incrementa il numero di copie
        else F_inserisci_libro_abr((&(*T)->dxPtr),libroDaInserire);
    }
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_alloca_struttura_libro_abr(AlberoLibro *T){
    (*T)=(struct struttura_nodo_albero_libro*)malloc(sizeof(struct struttura_nodo_albero_libro));
    if(F_struttura_vuota(T)) F_error(3);
    (*T)->nodoLibroPtr=NULL;
    (*T)->sxPtr=NULL;
    (*T)->dxPtr=NULL;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_inserisci_studente_abr(AlberoStudente *T, Studente studenteDaInserire){
    if(F_struttura_vuota(*T)){
        F_alloca_struttura_studente_abr(T);
        (*T)->nodoStudentePtr=studenteDaInserire;
    }else{
        Studente studenteAlbero=(*T)->nodoStudentePtr;
        if(studenteDaInserire->matricola < studenteAlbero->matricola) F_inserisci_studente_abr((&(*T)->sxPtr),studenteDaInserire);
        else F_inserisci_studente_abr((&(*T)->dxPtr),studenteDaInserire);
    }
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_alloca_struttura_studente_abr(AlberoStudente *T){
    (*T)=(struct struttura_nodo_albero_studente*)malloc(sizeof(struct struttura_nodo_albero_studente));
    if(F_struttura_vuota(T)) F_error(3);
    (*T)->nodoStudentePtr=NULL;
    (*T)->sxPtr=NULL;
    (*T)->dxPtr=NULL;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
Studente F_cerca_studente_abr(AlberoStudente *T, int matricolaDaCercare){
    if(F_albero_vuoto(*T)) return NULL;
    else{
        Studente studenteAlbero=(*T)->nodoStudentePtr;
        if(studenteAlbero->matricola==matricolaDaCercare) return studenteAlbero;
        if(matricolaDaCercare<studenteAlbero->matricola) return F_cerca_studente_abr((&(*T)->sxPtr), matricolaDaCercare);
        else return F_cerca_studente_abr((&(*T)->dxPtr), matricolaDaCercare);
    }
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
Libro F_cerca_libro_abr(AlberoLibro *T, char *libroDaCercare){
    if(F_albero_vuoto(*T)) return NULL;
    else{
        Libro libroAlbero=(*T)->nodoLibroPtr;
        int confrontoTitoli=strcmp(libroDaCercare,libroAlbero->titoloPtr);
        if(confrontoTitoli==0){ // Libro presente in biblioteca
            return libroAlbero;
        }else{
            if(confrontoTitoli<0) return F_cerca_libro_abr((&(*T)->sxPtr),libroDaCercare);
            else return F_cerca_libro_abr((&(*T)->dxPtr), libroDaCercare);
        }
    }
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
int F_albero_vuoto(void *T){
    return (!T);
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_dealloca_struttura_albero_libro(AlberoLibro *T){
    if(!F_struttura_vuota(*T)){
        F_dealloca_struttura_albero_libro((&(*T)->sxPtr));
        F_dealloca_struttura_albero_libro((&(*T)->dxPtr));
        Libro libro=(*T)->nodoLibroPtr;
        free(libro);
        free(*T);
    }
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_dealloca_struttura_albero_studente(AlberoStudente *T){
    if(!F_struttura_vuota(*T)){
        F_dealloca_struttura_albero_studente((&(*T)->sxPtr));
        F_dealloca_struttura_albero_studente((&(*T)->dxPtr));
        Studente studente=(*T)->nodoStudentePtr;
        free(studente);
        free(*T);
    }
}