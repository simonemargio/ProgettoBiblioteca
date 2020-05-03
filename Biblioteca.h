#ifndef PROGETTOBIBLIOTECA_BIBLIOTECA_H
#define PROGETTOBIBLIOTECA_BIBLIOTECA_H
#include "Abr.h"
#include "Coda.h"

/*
 * Descrizione: struttura principale per la gestione biblioteca
 * Dettagli: tutte le informazioni che ruotano attorno alla biblioteca vengono
 *           gestite tramite questa struttura
 * Contenuto: strutturaStudentiPtr: punta all'albero contentente l'informazione
 *            degli studenti che vengono registrati nella biblioteca
 *            strutturaLibriPtr: punta all'albero contenente l'informazione di
 *            tutti i libri che sono stati inseriri nella biblioteca
 *            codaRichiestrPtr: punta alla lista di tutte le richieste di ogni
 *            studente che vuole prendere in prestito un libro
 *            codaRestituzioniPtr: punta alla lista di tutte le richieste di ogni
 *            studente che vuole restituire un libro
 *            codaLibriPresiInPrestitoPtr: punta alla lista di tutti gli studenti
 *            a cui e' stato dato in prestito un libro
 */
struct struttura_gestione_biblioteca{
    struct struttura_nodo_albero_studente *strutturaStudentiPtr;
    struct struttura_nodo_albero_libro *strutturaLibriPtr;
    struct struttura_elemento_coda *codaRichiestePtr;
    struct struttura_elemento_coda *codaRestituzioniPtr;
    struct struttura_elemento_coda *codaLibriPresiInPrestitoPtr;
};

/*
 * Descrizione: struttura che definisce un libro
 * Dettagli: rappresenta l'informazione che ogni nodo dell'albero
 *           struttura_nodo_albero_libro dispone
 * Contenuto: titoloPtr: titolo del libro
 *            autorePtr: nome dell'autore del libro
 *            copie: numero di copie di quel libro presenti
 */
struct struttura_gestione_libro{
    char *titoloPtr;
    char *autorePtr;
    int copie;
};

/*
 * Descrizione: struttura che definisce uno studente
 * Dettagli: rappresenta l'informazione che ogni nodo dell'albero
 *           struttura_nodo_albero_studente dispone
 * Contenuto: matricola: matricola associata allo studente
 *            nomePtr: nome dello studente
 *            cognomePtr: cognome dello studente
 */
struct struttura_gestione_studente{
    int  matricola;
    char *nomePtr;
    char *cognomePtr;
};


typedef struct struttura_gestione_libro *Libro;
typedef struct struttura_gestione_studente *Studente;
typedef struct struttura_gestione_biblioteca *Biblioteca;

/* gestione della biblioteca */
void F_gestione_biblioteca();

/*  alloca la struttura principale */
void F_alloca_struttura_biblioteca(Biblioteca *B);

/* funzioni di menu mostrate all'utente */
void F_stampa_menu_popolamento();
void F_stampa_menu_gestione_biblioteca();
void F_stampa_menu_gestione_biblioteca_richiesta_studente();
void F_stampa_menu_gestione_biblioteca_richiesta_o_restituzione_libro();
void F_stampa_menu_gestione_biblioteca_presa_in_carico_richiesta_consegna_o_restituzione_libro();

/* scelta sul tipo di popolamento da effettuare */
void F_popolamento(Biblioteca B);

/* prende in intero da terminale */
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);

/* richiama la funzione per il popolamento automatico */
void F_popolamento_automatico(Biblioteca B, int numeroLibri);

/* permette il popolamento dei libri */
void F_popolamento_da_terminale(Biblioteca B, int numeroLibri);

/* popola la biblioteca con libri predefiniti */
void F_popolamento_automatico_libro(Biblioteca B, int sceltaLibro);

/* verifica se una struttura e' vuota */
int F_struttura_vuota(void *S);

/* alloca la struttura per un libro */
void F_alloca_struttura_libro(Libro *L);

/* inserisce le informazioni di un libro */
void F_inserisci_informazioni_libro(Libro *L,char *titolo,char *autore, int copie);

/* confronto di due stringhe */
int F_cofronto_titolo_libri(char *s1, char *s2);

/* prende in ingresso una stringa */
char *F_chiedi_stringa(char *s);

/* gestione di tutte le funzionalita' della biblioteca */
void F_engine_biblioteca(Biblioteca B);

/* selezione per la richiesta di libri */
void F_aggiungi_richiesta_studente(Biblioteca B);

/*  gestite le richieste fatte dagli studenti */
void F_prendi_in_carico_una_richiesta_studente(Biblioteca B);

/* registra uno studente */
void F_richiedi_informazioni_studente(Studente *S, int matricola);

/* sollecita la restituzione dei libri */
void F_sollecita_restituzione_libri(Biblioteca B);

/* gestione libri da prendere in prestito */
void F_aggiungi_richiesta_studente_prestito_libro(Biblioteca B);

/* gestione libri da restituire */
void F_aggiungi_richiesta_studente_restituzione_libro(Biblioteca B);

/* verifica se uno studente e' registrato */
Studente F_verifica_registrazione_studente_biblioteca(Biblioteca B);

/* gestisce la consegna di un libro */
void F_consegna_libro_allo_studente(Biblioteca B);

/* gestisce la restituzione di un libro */
void F_studente_restituisce_libro(Biblioteca B);

/* verifica la presenza di richieste in coda */
int F_verifica_richieste(Biblioteca B);

/* sollecita la restizione dei libri */
void F_sollecita_restituzione_libri_presi_in_prestito(Coda *C);

/* sollecita la restizione dei libri */
void F_sollecita_restituzione_libri_richiesti(Coda *C);

/* sollecita la restizione dei libri */
void F_sollecita_restituzione_libri_restituzioni(Coda *C);

/* deallocazione di tutte le strutture */ //
void F_dealloca_strutture(Biblioteca B);



#endif //PROGETTOBIBLIOTECA_BIBLIOTECA_H
