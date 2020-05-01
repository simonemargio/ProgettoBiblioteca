#ifndef PROGETTOBIBLIOTECA_CODA_H
#define PROGETTOBIBLIOTECA_CODA_H

struct struttura_elemento_coda{
    void *studentePrt;
    void *libroPtr;
    struct struttura_elemento_coda *nextPrt;
};

typedef struct struttura_elemento_coda *Coda;

void F_alloca_elemento_coda(Coda *C);
void F_inserimento_in_coda(Coda *C, void *studenteDaInserireInCoda, void *libroPresoDalloStutente);
void F_elimina_elemento_coda_in_testa(Coda *C);



#endif //PROGETTOBIBLIOTECA_CODA_H
