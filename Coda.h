#ifndef PROGETTOBIBLIOTECA_CODA_H
#define PROGETTOBIBLIOTECA_CODA_H


/*
 * Descrizione: struttura della coda
 * Dettagli:    definisce le code: studenti che che chiedono di prendere un libro,
 *              studenti che devono restituire un libro, studenti che hanno in pre-
 *              stito un libro
 * Contenuto:   codaStudente: contiene le informazioni definite in: struttura_gestione_studente
 *              codaLibro: contiene le informazioni definite in: struttura_gestione_libro
 *              nexPrt: elemento della coda successivo
 */
struct struttura_elemento_coda{
    struct struttura_gestione_studente *codaStudente;
    struct struttura_gestione_libro *codaLibro;
    struct struttura_elemento_coda *nextPrt;
};

typedef struct struttura_elemento_coda *Coda;

/* alloca un elemento della coda */
void F_alloca_elemento_coda(Coda *C);

/* elimina la testa della coda */
void F_elimina_elemento_coda_in_testa(Coda *C);

/* inserisce una elemento in coda alla coda */
void F_inserimento_in_coda_richieste_studente(Coda *C, Studente studenteDaInserire, Libro libroDaInserire);

/* cerca un elemento nella coda */
int F_cerca_elemento_coda(Coda *C, int matricola, char *titoloLibro);

/* elimina un elemento nella coda */
Coda F_elimina_elemento_coda(Coda C, int matricola, char *titoloLibro);

/* dealloca l'intera coda */
void F_dealloca_struttura_coda(Coda *C);

#endif //PROGETTOBIBLIOTECA_CODA_H
