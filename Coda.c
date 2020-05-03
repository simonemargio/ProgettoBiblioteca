#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Error.h"
#include "Coda.h"

/*
 *  Descrizione: alloca un elemento della coda
 *  Dettagli: ogni elemento della coda mantiene l'informazione di un libro
 *            e dello studente ad esso associato
 *  Parametri in: C->elemento della coda
 *  Parametri out: //
 *  Chiamante: Coda->F_inserimento_in_coda_richieste_studente
 *
*/
void F_alloca_elemento_coda(Coda *C){
    (*C)=(struct struttura_elemento_coda*)malloc(sizeof(struct struttura_elemento_coda));
    if(F_struttura_vuota(*C)) F_error(9);
    (*C)->codaLibro=NULL;
    (*C)->codaStudente= NULL;
    (*C)->nextPrt=NULL;
}

/*
 *  Descrizione: inserisce una elemento in coda alla coda
 *  Dettagli: preso un elemento questo viene inserito in fondo alla coda
 *  Parametri in: C->elemento della coda
 *                studenteDaInserire->struttura contentente tutte le informazioni
 *                sullo studente (nome,cognome e matricola)
 *                libroDaInserire->struttura contenente tutte le informazioni sul
 *                libro (titolo, autore e copie)
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_aggiungi_richiesta_studente_restituzione_libro
 *             Biblioteca->F_aggiungi_richiesta_studente_prestito_libro
 *             Biblioteca->F_consegna_libro_allo_studente
 *
*/
void F_inserimento_in_coda_richieste_studente(Coda *C, Studente studenteDaInserire, Libro libroDaInserire){
    if(F_struttura_vuota(*C)) {
        F_alloca_elemento_coda(C);
        (*C)->codaLibro=libroDaInserire;
        (*C)->codaStudente=studenteDaInserire;
    }else{
        F_inserimento_in_coda_richieste_studente((&(*C)->nextPrt),studenteDaInserire,libroDaInserire);
    }
}

/*
 *  Descrizione: elimina la testa della coda
 *  Dettagli: //
 *  Parametri in: C->elemento della coda
 *  Parametri out: //
 *  Chiamante: Coda->F_dealloca_struttura_coda
 *             Biblioteca->F_studente_restituisce_libro
 *             Biblioteca->F_consegna_libro_allo_studente
 *             Biblioteca->F_sollecita_restituzione_libri_richiesti
 *             Biblioteca->F_sollecita_restituzione_libri_restituzioni
 *             Biblioteca->F_sollecita_restituzione_libri_presi_in_prestito
 *
*/
void F_elimina_elemento_coda_in_testa(Coda *C){
    if(!F_struttura_vuota(*C)){
        Coda elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPrt;
        free(elementoDaEliminare);
    }
}

/*
 *  Descrizione: cerca un elemento nella coda
 *  Dettagli: verifica se lo studente che ha fatto una richiesta
 *            di restituzione di un libro abbia effettivamente chiesto
 *            in prestito quel libro
 *  Parametri in: C->elemento della coda
 *                matricola->matricola identificativa dello studente
 *                titoloLibro->titolo del libro da verificare
 *  Parametri out: 0->lo stutente non ha mai avuto in presitito il libro
 *                 1->altrimenti
 *  Chiamante: Biblioteca->F_studente_restituisce_libro
 *
*/
int F_cerca_elemento_coda(Coda *C, int matricola, char *titoloLibro){
    /*
     * Si cerca lo studente confrontando prima il titolo del libro con
     * il titolo dei libri presenti nella coda. Se viene trovato si verifica
     * che anche lo studente combaci (lo stesso libro puo' essere stato preso
     * da piu' studenti)
    */
    if(F_struttura_vuota(*C)) return 0;
    Studente S=(*C)->codaStudente;
    Libro L=(*C)->codaLibro;
    int confrontoTitoliLibro=strcmp(L->titoloPtr,titoloLibro);
    if(S->matricola==matricola && confrontoTitoliLibro==0) return 1;
    return F_cerca_elemento_coda((&(*C)->nextPrt),matricola,titoloLibro);
}

/*
 *  Descrizione: elimina un elemento nella coda
 *  Dettagli: se lo studente aveva preso in prestito un libro e decide
 *            di consegnarlo, viene eliminato dalla coda dei prestiti
 *  Parametri in: C->elemento coda
 *                matricola->matricola dello studente da eliminare
 *                titioloLibro->titolo libro
 *  Parametri out: C->nuova coda
 *  Chiamante: Biblioteca->F_studente_restituisce_libro
 *             Biblioteca->F_consegna_libro_allo_studente
 *             Biblioteca->F_sollecita_restituzione_libri_richiesti
 *             Biblioteca->F_sollecita_restituzione_libri_restituzioni
 *             Biblioteca->F_sollecita_restituzione_libri_presi_in_prestito
 *
*/
Coda F_elimina_elemento_coda(Coda C, int matricola, char *titoloLibro){
    /*
     * Medesimo discorso di confronto fatto in F_cerca_elemento_coda
     *
     */
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

/*
 *  Descrizione: dealloca l'intera coda
 *  Dettagli: //
 *  Parametri in: C->elemento coda
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_dealloca_strutture
 *
*/
void F_dealloca_struttura_coda(Coda *C){
    if(!F_struttura_vuota(*C)){
        F_dealloca_struttura_coda((&(*C)->nextPrt));
        F_elimina_elemento_coda_in_testa((&(*C)));
    }
}