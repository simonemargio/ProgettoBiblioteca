#include <stdio.h>
#include <stdlib.h>
#include "Error.h"


void F_error(int e){
    switch(e){
        default:
            puts("\nErrore generico.");
            break;
        case 1:
            puts("\nErrore allocazione struttura Biblioteca.");
            break;
        case 2:
            puts("\nErrore allocazione struttura libri");
            break;
        case 3:
            puts("\nErrore allocazione struttura albero");
            break;
        case 4:
            puts("\nErrore struttura gestione richieste: struttura libro non presente");
            break;
        case 5:
            puts("\nErrore struttura gestione richieste: struttura studente non presente");
            break;
    }
    exit(e);
}