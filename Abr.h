#ifndef PROGETTOBIBLIOTECA_ABR_H
#define PROGETTOBIBLIOTECA_ABR_H


#include "Biblioteca.h"

struct struttura_nodo_albero_studente{
    struct struttura_gestione_studente *nodoStudentePtr;
    struct struttura_nodo_albero_studente *sxPtr;
    struct struttura_nodo_albero_studente *dxPtr;
};

struct struttura_nodo_albero_libro{
    struct struttura_gestione_libro *nodoLibroPtr;
    struct struttura_nodo_albero_libro *sxPtr;
    struct struttura_nodo_albero_libro *dxPtr;
};

typedef struct struttura_nodo_albero_studente *AlberoStudente;
typedef struct struttura_nodo_albero_libro *AlberoLibro;
typedef struct struttura_gestione_libro *Libro;
typedef struct struttura_gestione_studente *Studente;


void F_inserisci_libro_abr(AlberoLibro *T, Libro libroDaInserire);
void F_inserisci_studente_abr(AlberoStudente *T, Studente studenteDaInserire);
void F_alloca_struttura_libro_abr(AlberoLibro *T);
void F_alloca_struttura_studente_abr(AlberoStudente *T);
Studente F_cerca_studente_abr(AlberoStudente *T, int matricolaDaCercare);
Libro F_cerca_libro_abr(AlberoLibro *T, char *libroDaCercare);
int F_albero_vuoto(void *T);
void F_dealloca_struttura_albero_libro(AlberoLibro *T);
void F_dealloca_struttura_albero_studente(AlberoStudente *T);

#endif //PROGETTOBIBLIOTECA_ABR_H
