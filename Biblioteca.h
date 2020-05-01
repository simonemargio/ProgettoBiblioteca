#ifndef PROGETTOBIBLIOTECA_BIBLIOTECA_H
#define PROGETTOBIBLIOTECA_BIBLIOTECA_H

#include "Abr.h"

//CANCELLA
#include "Coda.h"

struct struttura_gestione_biblioteca{
    void *strutturaLibriPtr;
    void *strutturaStudentiPtr;
    void *strutturaGestioneRichieste;
};

struct struttura_gestione_libri{
    char *titoloPtr;
    char *autorePtr;
    int copie;
};

struct struttura_gestione_studenti{
    int  matricola;
    char *nomePtr;
    char *cognomePtr;
};

typedef struct struttura_gestione_libri *Libri;
typedef struct struttura_gestione_studenti *Studenti;
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
void F_alloca_struttura_libro(Libri *L);
void F_inserisci_informazioni_libro(Libri *L,char *titolo,char *autore, int copie);
int F_cofronto_titolo_libri(char *s1, char *s2);
char *F_chiedi_stringa(char *s);
void F_engine_biblioteca(Biblioteca B);
void F_aggiungi_richiesta_studente(Biblioteca B);
void F_prendi_in_carico_una_richiesta_studente(Biblioteca B);
void F_richiedi_informazioni_studente(Studenti *S, int matricola);


// CANCELLA
void STAMPALIBRI(Albero L);
void STAMPASTUDENTI(Albero S);
void STAMPACODA(Coda C);

#endif //PROGETTOBIBLIOTECA_BIBLIOTECA_H
