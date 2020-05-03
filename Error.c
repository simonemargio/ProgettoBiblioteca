#include <stdio.h>
#include <stdlib.h>
#include "Error.h"


void F_error(int e){
    puts("\nERRORE:");
    switch(e){
        default:
            puts("generico.");
            break;
        case 1:
            puts("allocazione struttura biblioteca.");
            break;
        case 2:
            puts("allocazione struttura libri.");
            break;
        case 3:
            puts("allocazione struttura albero.");
            break;
        case 4:
            puts("struttura gestione richieste: struttura libro non presente");
            break;
        case 5:
            puts("struttura gestione richieste: struttura studente non presente");
            break;
        case 6:
            puts("allocazione struttura studente.");
            break;
        case 7:
            puts("allocazione stringa.");
            break;
        case 8:
            puts("allocazione stringa per interi.");
            break;
        case 9:
            puts("allocazione struttura elemento coda.");
            break;

    }
    puts("Uscita forzata.");
    exit(e);
}