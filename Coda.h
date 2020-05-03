#ifndef PROGETTOBIBLIOTECA_CODA_H
#define PROGETTOBIBLIOTECA_CODA_H



struct struttura_elemento_coda{
    struct struttura_gestione_studente *codaStudente;
    struct struttura_gestione_libro *codaLibro;
    struct struttura_elemento_coda *nextPrt;
};

typedef struct struttura_elemento_coda *Coda;

void F_alloca_elemento_coda(Coda *C);
void F_elimina_elemento_coda_in_testa(Coda *C);
void F_inserimento_in_coda_richieste_studente(Coda *C, Studente studenteDaInserire, Libro libroDaInserire);
int F_cerca_elemento_coda(Coda *C, int matricola, char *titoloLibro);
Coda F_elimina_elemento_coda(Coda C, int matricola, char *titoloLibro);
void F_dealloca_struttura_coda(Coda *C);

#endif //PROGETTOBIBLIOTECA_CODA_H
