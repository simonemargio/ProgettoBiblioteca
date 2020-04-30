#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Error.h"

void F_gestione_biblioteca(){
    Biblioteca B=NULL;
    F_alloca_struttura_biblioteca(&B);
    F_popolamento(B);
};

void F_popolamento(Biblioteca B){
    int sceltaMenu=0,uscitaMenu=-1;
    do{
        F_stampa_menu_popolamento();
        sceltaMenu=F_chiedi_intero("Inserisci il valore numero dell'operazione:",1,'0','2');
        switch(sceltaMenu){
            default:
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: // Popolamento da terminale
                F_popolamento_da_terminale(B);
                break;
            case 2: // Popolamento automatico
                F_popolamento_automatico(B);
                break;
        }
    }while(uscitaMenu!=0);
}

void F_alloca_struttura_biblioteca(Biblioteca *B){
    (*B)=(struct struttura_gestione_biblioteca*)malloc(sizeof(struct struttura_gestione_biblioteca));
    if(F_struttura_vuota(*B)) F_error(1);
    (*B)->strutturaLibriPtr=NULL;
    (*B)->strutturaStudentiPtr=NULL;
}

int F_struttura_vuota(void *S){
    return (!S);
}

void F_popolamento_da_terminale(Biblioteca B){

}

void F_popolamento_automatico(Biblioteca B){

}

void F_popolamento_automatico_libro(Biblioteca B, int sceltaLibro){
    Libri nuovo_libro=NULL;
    char *titolo=NULL, *autore=NULL;
    int copie=0;

    switch(sceltaLibro){
        default:
            break;
        case 1:
            titolo="Halo Flood";
            autore="William Dietz";
            copie=2;
            break;
        case 2:
            titolo="Il Piccolo Principe";
            autore="Antoine De Sanit";
            copie=1;
            break;
    }
    F_alloca_struttura_libro(&nuovo_libro);
    F_inserisci_informazioni_libro(&nuovo_libro,titolo,autore,copie);


}

void F_inserisci_informazioni_libro(Libri *L,char *titolo,char *autore, int copie){
    (*L)->autorePtr=autore;
    (*L)->titoloPtr=titolo;
    (*L)->copie=copie;
}

void F_alloca_struttura_libro(Libri *L){
    (*L)=(struct struttura_gestione_libri*)malloc(sizeof(struct struttura_gestione_libri));
    if(F_struttura_vuota(L)) F_error(2);
    (*L)->autorePtr=NULL;
    (*L)->titoloPtr=NULL;
    (*L)->copie=0;
}

int F_chiedi_intero(char *s,int dim,char minimo,char massimo){
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;

    printf("%s",s);
    do{
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF ){
            if(c>=minimo && c<=massimo){
                tmp[i]=c;
                i++;
            }
        }
        intero_preso = (int) strtol(tmp, &ptr, 10);

        if(!i){
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<dim;i++)
                tmp[i]='*';
            i=0;
        }else flag=1; // Valore corretto
    }while(flag==0);

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}


void F_stampa_menu_popolamento(){
    puts("Gestione biblioteca - Popolamento");
    puts("Scegli il tipo di popolamento da efettuare:");
    puts("1] Popolamento dei libri tramite terminale (processo lungo)");
    puts("2] Popolamento dei libri automatico");
    puts("\n0] Esci");
}

void F_stampa_menu_gestione_biblioteca(){
    puts("Gestione biblioteca - Menu principale");
    puts("1] Aggiungi richiesta studente");
    puts("2] Prendi in carico una richiesta");
    puts("\n0] Termina");
}

void F_stampa_menu_gestione_biblioteca_richiesta_studente(){
    puts("Gestione biblioteca - Richiesta studente");

    puts("\n0] Indietro");
}