#ifndef PROGETTOBIBLIOTECA_BIBLIOTECA_H
#define PROGETTOBIBLIOTECA_BIBLIOTECA_H

#include "Abr.h"

struct struttura_gestione_biblioteca{
    void *strutturaLibriPtr;
    void *strutturaStudentiPtr;
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
void F_popolamento_da_terminale(Biblioteca B);
void F_popolamento_automatico_libro(Biblioteca B, int sceltaLibro);
int F_struttura_vuota(void *S);
void F_alloca_struttura_libro(Libri *L);
void F_inserisci_informazioni_libro(Libri *L,char *titolo,char *autore, int copie);
int F_cofronto_titolo_libri(char *s1, char *s2);


// CANCELLA
void STAMPALIBRI(Albero L);

#endif //PROGETTOBIBLIOTECA_BIBLIOTECA_H
