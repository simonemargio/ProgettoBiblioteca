#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Error.h"
#include "Abr.h"
#include "Coda.h"
#define NUMERO_LIBRI_POPOLAMENTO 15
#define LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE 40

void F_gestione_biblioteca(){
    Biblioteca B=NULL;
    F_alloca_struttura_biblioteca(&B);
    F_popolamento(B);
    F_engine_biblioteca(B);

    // CANCELLA
    Albero AlberoLibri=B->strutturaLibriPtr;
    STAMPALIBRI(AlberoLibri);
    puts("\n\n");
    Albero AlberoStudenti=B->strutturaStudentiPtr;
    STAMPASTUDENTI(AlberoStudenti);
    puts("\n\n");
    Coda C=B->strutturaGestioneRichieste;
    STAMPACODA(C);
};

void F_engine_biblioteca(Biblioteca B){
    int sceltaMenu=0, uscitaMenu=-1;
    do{
        F_stampa_menu_gestione_biblioteca();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');
        switch(sceltaMenu){
            default:
                break;
            case 1: // Aggiungi richiesta studente
                F_aggiungi_richiesta_studente(B);
                break;
            case 2: // Stampa sottomenu gestione richieste
                F_stampa_menu_gestione_biblioteca_richiesta_studente();
                sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');
                switch(sceltaMenu){
                    default:
                        break;
                    case 1: // Prendi in carico una richiesta
                        F_prendi_in_carico_una_richiesta_studente(B);
                        break;
                    case 2: // Sollecita restituzione libri
                        puts("Bla bla bla");
                        break;
                }
                break;
            case 0:
                // VERIFICARE SE SONO PRESENTI RICHIESTE
                uscitaMenu=0;
                break;
        }
    }while(uscitaMenu!=0);
}



void F_aggiungi_richiesta_studente(Biblioteca B){
    int matricola=F_chiedi_intero("Inserisci la matricola dello studente che richiede un libro:",10,'0','9');
    Albero S=B->strutturaStudentiPtr;
    Studenti verifica_studente=F_cerca_elemento_albero(&S,&matricola,0);

    if(!verifica_studente){
        F_richiedi_informazioni_studente(&verifica_studente, matricola);
        F_inserisci_elemento_abr(&S,verifica_studente,0);
        B->strutturaStudentiPtr=S;
        printf("\nStudente (%s-%s-%d) aggiunto all'archivio della biblioteca.\n",verifica_studente->cognomePtr,verifica_studente->nomePtr,verifica_studente->matricola);
    } else{
        printf("\nStudente con matricola (%d) presente nell'archivio della biblioteca.\n",verifica_studente->matricola);
        printf("Lo studente e' registrato con i seguenti dati (%s-%s).\n",verifica_studente->cognomePtr,verifica_studente->nomePtr);
    }

    Albero L=B->strutturaLibriPtr;
    char *titoloLibroRichiesto=F_chiedi_stringa("Titolo del libro da prendere in prestito");
    Libri LibroScelto=F_cerca_elemento_albero(&L,titoloLibroRichiesto,1);

    if(LibroScelto){
        printf("\nIl libro (%s) e' presente nella biblioteca, inserisco la richiesta in coda.\n",LibroScelto->titoloPtr);
        Coda C=B->strutturaGestioneRichieste;
        F_inserimento_in_coda(&C,verifica_studente,LibroScelto);
        B->strutturaGestioneRichieste=C;
    } else printf("\nIl libro (%s) non e' presente nell'archivio libi della biblioteca. Richiesta annullata.\n",titoloLibroRichiesto);

}

void F_richiedi_informazioni_studente(Studenti *S, int matricola){
    (*S)=(struct struttura_gestione_studenti*)malloc(sizeof(struct struttura_gestione_studenti));
    printf("Studente con matricola (%d) non presente nell'archivio della biblioteca.\nSi prega di aggiungerlo.",matricola);
    char *nome=F_chiedi_stringa("nome dello studente:");
    char *cognome=F_chiedi_stringa("cognome dello studente:");
    (*S)->matricola=matricola;
    (*S)->nomePtr=nome;
    (*S)->cognomePtr=cognome;
}


void F_prendi_in_carico_una_richiesta_studente(Biblioteca B){
    Coda C=B->strutturaGestioneRichieste;
    if(!F_struttura_vuota(C)){
        Libri L=C->libroPtr;
        Studenti S=C->studentePrt;
        if(F_struttura_vuota(L)) F_error(4);
        if(F_struttura_vuota(S)) F_error(5);
        printf("\nPrendo in carico la richiesta dello studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);

        if(L->copie!=0){
            L->copie=L->copie-1;
            printf("\nLa richiesta del libro (%s) e' stata accettata.\n\n",L->titoloPtr);
            F_elimina_elemento_coda_in_testa(&C);
            B->strutturaGestioneRichieste=C;
        }
        else{ // La richiesta viene sospesa e lo studente viene inserito in coda
            printf("\nIl libro (%s) richiesto dallo studente non e' disponibile. Pertanto la richiesta verra' messa in coda.\n",L->titoloPtr);
            F_elimina_elemento_coda_in_testa(&C);
            F_inserimento_in_coda(&C,S,L);
            B->strutturaGestioneRichieste=C;
        }
    }else puts("\nNon sono presenti richieste da prendere in carico.");
}

void F_popolamento(Biblioteca B){
    int sceltaMenu=0;

    F_stampa_menu_popolamento();
    sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');
    switch(sceltaMenu){
        default:
            break;
        case 1:
            F_popolamento_da_terminale(B,NUMERO_LIBRI_POPOLAMENTO);
            break;
        case 2:
            F_popolamento_automatico(B,NUMERO_LIBRI_POPOLAMENTO);
            break;
        case 0:
            exit(0);  // QUI VANNO DEALLOCATE LE STRUTTURE
    }
}

void F_alloca_struttura_biblioteca(Biblioteca *B){
    (*B)=(struct struttura_gestione_biblioteca*)malloc(sizeof(struct struttura_gestione_biblioteca));
    if(F_struttura_vuota(*B)) F_error(1);
    (*B)->strutturaLibriPtr=NULL;
    (*B)->strutturaStudentiPtr=NULL;
    (*B)->strutturaGestioneRichieste=NULL;
}

int F_struttura_vuota(void *S){
    return (!S);
}

void F_popolamento_da_terminale(Biblioteca B, int numeroLibri){
    if(numeroLibri!=0){
        Libri nuovo_libro=NULL; Albero T=B->strutturaLibriPtr;
        printf("Inserimento del libro numero (%d)",numeroLibri);
        char *titolo=F_chiedi_stringa("Inserisci il titolo del libro");
        char *autore=F_chiedi_stringa("Inserisci l'autore del libro");
        int copie=F_chiedi_intero("Inserisci il numero di copie del libro:",3,'1','9');
        F_alloca_struttura_libro(&nuovo_libro);
        F_inserisci_informazioni_libro(&nuovo_libro,titolo,autore,copie);
        F_inserisci_elemento_abr(&T,nuovo_libro,1);
        B->strutturaLibriPtr=T;
        F_popolamento_da_terminale(B,numeroLibri-1);
    }
}

char *F_chiedi_stringa(char *s){
    /* DICHIARAZIONE VARIABILI */
    char *tmp=NULL,c='*';
    void *stringa_uscita=NULL;
    int i=0;

    tmp=(char *)malloc((LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE)*sizeof(char));

    printf("\nInserisci %s (MAX:%d):",s,LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE);

    for(i=0; (i<LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE && (c= (char) getchar()) != '\n' && c != EOF); i++){
        tmp[i]=c;
    }
    tmp[i]='\0';

    stringa_uscita=malloc(i*sizeof(char)); // Allocazione del giusto spazio per stringhe minori di DIM_STRINGA
    strcpy(stringa_uscita,tmp); // Copia della stringa nello spazio abitio al suo contenimento
    free(tmp);

    return stringa_uscita;
}

void F_popolamento_automatico(Biblioteca B, int numeroLibri){
    if(numeroLibri!=0){
        F_popolamento_automatico_libro(B,numeroLibri);
        F_popolamento_automatico(B,numeroLibri-1);
    }
}

void F_popolamento_automatico_libro(Biblioteca B, int sceltaLibro){
    Libri nuovo_libro=NULL;
    Albero T=B->strutturaLibriPtr;
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
            copie=2;
            break;
        case 3:
            titolo="Blockchain";
            autore="Gianluca Chiap";
            copie=1;
            break;
        case 4:
            titolo="L'ultima equazione";
            autore="Mark Alpert";
            copie=1;
            break;
        case 5:
            titolo="Lego";
            autore="Napoleon";
            copie=1;
            break;
        case 6:
            titolo="I Grafi sono belli";
            autore="Antonio";
            copie=4;
            break;
        case 7:
            titolo="Algebra";
            autore="Cutolo";
            copie=1;
            break;
        case 8:
            titolo="Tredici";
            autore="Hannah Backer";
            copie=1;
            break;
        case 9:
            titolo="Thinking in Java";
            autore="Bonatti";
            copie=1;
            break;
        case 10:
            titolo="Steve Jobs";
            autore="Walter Isaacson";
            copie=2;
            break;
        case 11:
            titolo="Elon Musk";
            autore="Ashlee Vance";
            copie=3;
            break;
        case 12:
            titolo="Essential";
            autore="The minimalist";
            copie=1;
            break;
        case 13:
            titolo="L'arte dell'inganno";
            autore="Kevin Mitnick";
            copie=1;
            break;
        case 14:
            titolo="Cronache del mondo emerso";
            autore="Licia Troisi";
            copie=1;
            break;
        case 15:
            titolo="Il linguaggio C";
            autore="Paul Daniel";
            copie=1;
            break;
    }
    F_alloca_struttura_libro(&nuovo_libro);
    F_inserisci_informazioni_libro(&nuovo_libro,titolo,autore,copie);
    F_inserisci_elemento_abr(&T,nuovo_libro,1);
    B->strutturaLibriPtr=T;
}


//CANCELLA
void STAMPALIBRI(Albero L){
    if(L){
        STAMPALIBRI(L->sxPtr);
        Libri a=L->datiBibliotecaPtr;
        printf("Titolo:|%s|-Autore:|%s|-Copie:|%d|\n",a->titoloPtr,a->autorePtr,a->copie);
        STAMPALIBRI(L->dxPtr);
    }
}

//CANCELLA
void STAMPASTUDENTI(Albero S){
    if(S){
        STAMPASTUDENTI(S->sxPtr);
        Studenti a=S->datiBibliotecaPtr;
        printf("Nome:|%s|-Cognome:|%s|-Matricola:|%d|\n",a->nomePtr,a->cognomePtr,a->matricola);
        STAMPASTUDENTI(S->dxPtr);
    }
}

//CANCELLA
void STAMPACODA(Coda C){
    if(C){
        Studenti S=C->studentePrt;
        Libri L=C->libroPtr;
        printf("Coda matricola|%d|Cognome|%s|Titolo|%s|\n",S->matricola,S->cognomePtr,L->titoloPtr);
        STAMPACODA(C->nextPrt);
    }
}

int F_cofronto_titolo_libri(char *s1, char *s2){
    return strcmp(s1,s2);
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
    puts("1] Soddisfa una richiesta");
    puts("2] Sollecita la consegna");
    puts("\n0] Indietro");
}