#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void F_inserisci_elemento_abr(Albero *T,void *LibroOStudente, int tipoStruttura){
    if(F_struttura_vuota(*T)){
        F_alloca_struttura_albero(T);
        (*T)->datiBibliotecaPtr=LibroOStudente;
    }else{
        if(tipoStruttura){ // Libri
            Libri LibroAlbero=(*T)->datiBibliotecaPtr, LibroDaAggiungere=LibroOStudente;
            int confrontoLibri=F_cofronto_titolo_libri(LibroDaAggiungere->titoloPtr,LibroAlbero->titoloPtr);
            if(confrontoLibri>0) F_inserisci_elemento_abr((&(*T)->sxPtr),LibroOStudente,tipoStruttura);
            else if(confrontoLibri==0) LibroAlbero->copie=LibroAlbero->copie+1; // Si aggiunge lo stesso libro, si incrementa il numero di copie
            else F_inserisci_elemento_abr((&(*T)->dxPtr),LibroOStudente,tipoStruttura);
        }else{ // Studenti
            Studenti StudentiAlbero=(*T)->datiBibliotecaPtr, StudenteDaAggiungere=LibroOStudente;
            if(StudenteDaAggiungere->matricola < StudentiAlbero->matricola) F_inserisci_elemento_abr((&(*T)->sxPtr),LibroOStudente,tipoStruttura);
            else F_inserisci_elemento_abr((&(*T)->dxPtr),LibroOStudente,tipoStruttura);
        }
    }
}

void *F_cerca_elemento_albero(Albero *T, void *valoreDaCercare, int tipoStruttura){
    if(F_albero_vuoto(*T)) return NULL;
    else{
        if(tipoStruttura){ // Cerca libro e numero di copie presenti
            char *libroDaCercare=NULL; Libri LibroAlbero=(*T)->datiBibliotecaPtr;
            libroDaCercare=(char*)valoreDaCercare;
            int confrontoTitoli=strcmp(libroDaCercare,LibroAlbero->titoloPtr);
         //   printf("\n|%s|%s|%d|\n",libroDaCercare,LibroAlbero->titoloPtr,confrontoTitoli);
         if(confrontoTitoli==0){ // Libro presente in biblioteca
                return LibroAlbero;
            }else{
                if(confrontoTitoli<0) return F_cerca_elemento_albero((&(*T)->dxPtr), valoreDaCercare,tipoStruttura);
                else return F_cerca_elemento_albero((&(*T)->sxPtr), valoreDaCercare,tipoStruttura);
            }
        }else{ // Cerca matricola dello studente se presente nell'archivio
            int matricolaDaCercare=0; Studenti StudentiAlbero=(*T)->datiBibliotecaPtr;
            memcpy(&matricolaDaCercare,valoreDaCercare,sizeof(int));
           // printf("\n|%d||%d|\n",StudentiAlbero->matricola,matricolaDaCercare);
            if(StudentiAlbero->matricola==matricolaDaCercare) return StudentiAlbero;
            if(matricolaDaCercare<StudentiAlbero->matricola) return F_cerca_elemento_albero((&(*T)->sxPtr), valoreDaCercare,tipoStruttura);
            else return F_cerca_elemento_albero((&(*T)->dxPtr), valoreDaCercare,tipoStruttura);
        }
    }
}

int F_albero_vuoto(Albero T){
    return (!T);
}