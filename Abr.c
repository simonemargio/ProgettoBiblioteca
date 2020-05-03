#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Error.h"
#include "Abr.h"

/*
 *  Descrizione: inserimento libro nell'albero
 *  Dettagli: si crea l'abr seguendo come valore
 *            discriminante il titolo del libro
 *  Parametri in: T->albeo
 *                libroDaInserire->struttura del libro
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_popolamento_da_terminale
 *             Biblioteca->F_popolamento_automatico_libro
 *
*/
void F_inserisci_libro_abr(AlberoLibro *T, Libro libroDaInserire){
    /*
     * Si confrontano i titoli dei libri e si scorre l'albero a destra
     * o sinitra fino a trovare la posizione "vuota" dove inserire il libro.
     * Se si aggiunge lo stesso libro allora si incremeneta il numero di copie
     * del libro stesso
     *
     */
    if(F_struttura_vuota(*T)){
        F_alloca_struttura_libro_abr(T);
        (*T)->nodoLibroPtr=libroDaInserire;
    }else{
        Libro libroAlbero=(*T)->nodoLibroPtr;
        int confrontoLibri=F_cofronto_titolo_libri(libroDaInserire->titoloPtr,libroAlbero->titoloPtr);
        if(confrontoLibri<0) F_inserisci_libro_abr((&(*T)->sxPtr),libroDaInserire);
        else if(confrontoLibri==0) libroAlbero->copie=libroAlbero->copie+1;
        else F_inserisci_libro_abr((&(*T)->dxPtr),libroDaInserire);
    }
}

/*
 *  Descrizione: alloca nodo libro
 *  Dettagli: //
 *  Parametri in: T->labero libri
 *  Parametri out: //
 *  Chiamante: Abr->F_inserisci_libro_abr
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
 *  Descrizione: inserimento studente nell'albero
 *  Dettagli: si crea l'abr seguendo come valore
 *            discriminante la matricola dello studente
 *  Parametri in: T->albero studenti
 *                studenteDaInserire->struttura dello studente da inserire
 *                nell'albero
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_verifica_registrazione_studente_biblioteca
 *
*/
void F_inserisci_studente_abr(AlberoStudente *T, Studente studenteDaInserire){
    /*
     * Si confrontano le matricole degli studenti e si scorre l'albero a destra
     * o sinitra fino a trovare la posizione "vuota" dove inserire lo studente.
     * Non puo' essere aggiunto uno studente con la medesima matricola di un
     * altro in quando viene fatta prima sempre una ricerca se lo studente e'
     * gia' presente nell'albero
     *
     */
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
 *  Descrizione: alloca nodo studente
 *  Dettagli: //
 *  Parametri in: T->albero studenti
 *  Parametri out: //
 *  Chiamante: Abr->F_inserisci_studente_abr
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
 *  Descrizione: cerca uno studente
 *  Dettagli: cerca tramite matricola lo studente nello
 *            albero degli studenti
 *  Parametri in: T->albero studenti
 *                matricolaDaCercare->matricola dello stu-
 *                dente da trovare
 *  Parametri out: Studente->studente trovato
 *                 NULL->altrimenti
 *  Chiamante: Biblioteca->F_verifica_registrazione_studente_biblioteca
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
 *  Descrizione: cerca un libro
 *  Dettagli: cerca tramite titolo il libro nell'albero
 *            dei libri
 *  Parametri in: T->albero libri
 *                libroDaCercare->libro da trovare
 *  Parametri out: Libro->libro trovato
 *                 NULL->libro non presente
 *  Chiamante: Biblioteca->F_aggiungi_richiesta_studente_restituzione_libro
 *             Biblioteca->F_aggiungi_richiesta_studente_prestito_libro
 *
*/
Libro F_cerca_libro_abr(AlberoLibro *T, char *libroDaCercare){
    if(F_albero_vuoto(*T)) return NULL;
    else{
        Libro libroAlbero=(*T)->nodoLibroPtr;
        int confrontoTitoli=strcmp(libroDaCercare,libroAlbero->titoloPtr);
        if(confrontoTitoli==0){ /* Libro presente in biblioteca */
            return libroAlbero;
        }else{
            if(confrontoTitoli<0) return F_cerca_libro_abr((&(*T)->sxPtr),libroDaCercare);
            else return F_cerca_libro_abr((&(*T)->dxPtr), libroDaCercare);
        }
    }
}

/*
 *  Descrizione: verifica se l'albero e' vuoto
 *  Dettagli: //
 *  Parametri in: T->qualsiasi struttura (qui AlberoLibro e
 *                AlberoStudente)
 *  Parametri out: 1->vuoto
 *                 0->altimenti
 *  Chiamante: Abr->F_cerca_libro_abr
 *             Abr->F_cerca_studente_abr
 *
*/
int F_albero_vuoto(void *T){
    return (!T);
}

/*
 *  Descrizione: deallocazione dell'albero libri
 *  Dettagli: //
 *  Parametri in: T->albero libri
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_dealloca_strutture
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
 *  Descrizione: deallocazione dell'albero studenti
 *  Dettagli: //
 *  Parametri in: T->albero studenti
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_dealloca_strutture
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