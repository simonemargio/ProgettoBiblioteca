#ifndef PROGETTOBIBLIOTECA_BIBLIOTECA_H
#define PROGETTOBIBLIOTECA_BIBLIOTECA_H

#include "Abr.h"

//CANCELLA
#include "Coda.h"


struct struttura_gestione_biblioteca{
    struct struttura_nodo_albero_studente *strutturaStudentiPtr;
    struct struttura_nodo_albero_libro *strutturaLibriPtr;
    struct struttura_elemento_coda *codaRichiestePtr;
    struct struttura_elemento_coda *codaRestituzioniPtr;
    struct struttura_elemento_coda *codaLibriPresiInPrestitoPtr;
};

struct struttura_gestione_libro{
    char *titoloPtr;
    char *autorePtr;
    int copie;
};

struct struttura_gestione_studente{
    int  matricola;
    char *nomePtr;
    char *cognomePtr;
};


typedef struct struttura_gestione_libro *Libro;
typedef struct struttura_gestione_studente *Studente;
typedef struct struttura_gestione_biblioteca *Biblioteca;


void F_gestione_biblioteca();
void F_alloca_struttura_biblioteca(Biblioteca *B);
void F_stampa_menu_popolamento();
void F_stampa_menu_gestione_biblioteca();
void F_stampa_menu_gestione_biblioteca_richiesta_studente();
void F_popolamento(Biblioteca B);
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_popolamento_automatico(Biblioteca B, int numeroLibri);
void F_popolamento_da_terminale(Biblioteca B, int numeroLibri);
void F_popolamento_automatico_libro(Biblioteca B, int sceltaLibro);
int F_struttura_vuota(void *S);
void F_alloca_struttura_libro(Libro *L);
void F_inserisci_informazioni_libro(Libro *L,char *titolo,char *autore, int copie);
int F_cofronto_titolo_libri(char *s1, char *s2);
char *F_chiedi_stringa(char *s);
void F_engine_biblioteca(Biblioteca B);
void F_aggiungi_richiesta_studente(Biblioteca B);
void F_prendi_in_carico_una_richiesta_studente(Biblioteca B);
void F_richiedi_informazioni_studente(Studente *S, int matricola);
void F_sollecita_restituzione_libri(Biblioteca B);
void F_stampa_menu_gestione_biblioteca_richiesta_o_restituzione_libro();
void F_aggiungi_richiesta_studente_prestito_libro(Biblioteca B);
void F_aggiungi_richiesta_studente_restituzione_libro(Biblioteca B);
Studente F_verifica_registrazione_studente_biblioteca(Biblioteca B);
void F_stampa_menu_gestione_biblioteca_presa_in_carico_richiesta_consegna_o_restituzione_libro();
void F_consegna_libro_allo_studente(Biblioteca B);
void F_studente_restituisce_libro(Biblioteca B);
int F_verifica_richieste(Biblioteca B);

/*
// CANCELLA
void STAMPALIBRI(Albero L);
void STAMPASTUDENTI(Albero S);
void STAMPACODA(Coda C);*/

#endif //PROGETTOBIBLIOTECA_BIBLIOTECA_H
