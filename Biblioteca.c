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
   /*  AlberoLibro A=B->strutturaLibriPtr;
      STAMPALIBRI(A);
    puts("\n\n");
    Albero AlberoStudenti=B->strutturaStudentiPtr;
    STAMPASTUDENTI(AlberoStudenti);
    puts("\n\n");
    Coda C=B->strutturaGestioneRichieste;
    STAMPACODA(C);*/
}

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
                        F_sollecita_restituzione_libri(B);
                        break;
                }
                break;
            case 0:
                uscitaMenu=F_verifica_richieste(B);
                break;
        }
    }while(uscitaMenu!=0);
}

int F_verifica_richieste(Biblioteca B){
    int controlloRichieste=-1;
    Coda richieste=B->codaRichiestePtr;
    Coda restituzioni=B->codaLibriPresiInPrestitoPtr;

    if(!F_struttura_vuota(richieste)) printf("\nSono presenti ancora delle richieste da prendere in carico.\n");
    if(!F_struttura_vuota(restituzioni)) printf("\nSono presenti ancora delli libri che devono essere restituiti.\nE' consigliabile sollecitare la restituzione.");
    if(F_struttura_vuota(richieste) && F_struttura_vuota(restituzioni)){
        printf("\nTutte le richieste sono state effettuate. Uscita.\n");
        controlloRichieste=0;
    }

    return controlloRichieste;
}

void F_aggiungi_richiesta_studente(Biblioteca B){
    int sceltaMenu=0;
    F_stampa_menu_gestione_biblioteca_richiesta_o_restituzione_libro();
    sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

    switch(sceltaMenu){
        default:
            break;
        case 1: // Richiesta per prestito libro
            F_aggiungi_richiesta_studente_prestito_libro(B);
            break;
        case 2: // Richiesta per restituzione per libro
            F_aggiungi_richiesta_studente_restituzione_libro(B);
            break;
    }

}

void F_aggiungi_richiesta_studente_restituzione_libro(Biblioteca B){
    Studente verifica_studente=F_verifica_registrazione_studente_biblioteca(B);

    AlberoLibro L=B->strutturaLibriPtr;
    char *titoloLibroDaRestituire=F_chiedi_stringa("Titolo del libro da restituire:");

    Libro libroScelto=F_cerca_libro_abr(&L,titoloLibroDaRestituire);

    if(libroScelto){
        printf("\nIl libro (%s) e' presente nel catalogo della biblioteca, inserisco la richiesta di restituzione in coda.\n",libroScelto->titoloPtr);
        Coda R=B->codaRestituzioniPtr;
        F_inserimento_in_coda_richieste_studente(&R,verifica_studente,libroScelto);
        B->codaRestituzioniPtr=R;
    } else printf("\nIl libro (%s) non e' presente nell'archivio libi della biblioteca. Richiesta annullata.\n",titoloLibroDaRestituire);
}

void F_aggiungi_richiesta_studente_prestito_libro(Biblioteca B){
    Studente verifica_studente=F_verifica_registrazione_studente_biblioteca(B);

    AlberoLibro L=B->strutturaLibriPtr;
    char *titoloLibroRichiesto=F_chiedi_stringa("Titolo del libro da prendere in prestito");

    Libro libroScelto=F_cerca_libro_abr(&L,titoloLibroRichiesto);

    if(libroScelto){
        printf("\nIl libro (%s) e' presente nella biblioteca, inserisco la richiesta in coda.\n",libroScelto->titoloPtr);
        Coda C=B->codaRichiestePtr;
        F_inserimento_in_coda_richieste_studente(&C,verifica_studente,libroScelto);
        B->codaRichiestePtr=C;
    } else printf("\nIl libro (%s) non e' presente nell'archivio libi della biblioteca. Richiesta annullata.\n",titoloLibroRichiesto);
}

Studente F_verifica_registrazione_studente_biblioteca(Biblioteca B){
    int matricola=F_chiedi_intero("Inserisci la matricola dello studente che richiede un libro:",10,'0','9');
    AlberoStudente S=B->strutturaStudentiPtr;
    Studente verifica_studente=F_cerca_studente_abr(&S,matricola);

    if(!verifica_studente){
        F_richiedi_informazioni_studente(&verifica_studente, matricola);
        F_inserisci_studente_abr(&S,verifica_studente);
        B->strutturaStudentiPtr=S;
        printf("\nStudente (%s-%s-%d) aggiunto all'archivio della biblioteca.\n",verifica_studente->cognomePtr,verifica_studente->nomePtr,verifica_studente->matricola);
    } else{
        printf("\nStudente con matricola (%d) presente nell'archivio della biblioteca.\n",verifica_studente->matricola);
        printf("Lo studente e' registrato con i seguenti dati (%s-%s).\n",verifica_studente->cognomePtr,verifica_studente->nomePtr);
    }
    return verifica_studente;
}

void F_richiedi_informazioni_studente(Studente *S, int matricola){
    (*S)=(struct struttura_gestione_studente*)malloc(sizeof(struct struttura_gestione_studente));
    printf("Studente con matricola (%d) non presente nell'archivio della biblioteca.\nSi prega di aggiungerlo.",matricola);
    char *nome=F_chiedi_stringa("nome dello studente:");
    char *cognome=F_chiedi_stringa("cognome dello studente:");
    (*S)->matricola=matricola;
    (*S)->nomePtr=nome;
    (*S)->cognomePtr=cognome;
}


void F_prendi_in_carico_una_richiesta_studente(Biblioteca B){
    int sceltaMenu=0;
    F_stampa_menu_gestione_biblioteca_presa_in_carico_richiesta_consegna_o_restituzione_libro();
    sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

    switch(sceltaMenu){
        default:
            break;
        case 1: // Consegna il libro allo studente
            F_consegna_libro_allo_studente(B);
            break;
        case 2: // Prendi il libro che aveva in prestito uno studente
            F_studente_restituisce_libro(B);
            break;
    }

}

void F_studente_restituisce_libro(Biblioteca B){
    Coda R=B->codaRestituzioniPtr;
    if(!F_struttura_vuota(R)){
        Libro L=R->codaLibro;
        Studente S=R->codaStudente;
        if(F_struttura_vuota(L)) F_error(6);
        if(F_struttura_vuota(S)) F_error(7);
        printf("\nPrendo in carico la richiesta dello studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);

        Coda P=B->codaLibriPresiInPrestitoPtr;
        int controlloPrestiti=F_cerca_elemento_coda(&P,S->matricola,L->titoloPtr);
        if(controlloPrestiti){
            printf("\nLo studente aveva preso in prestito il libro:\nTitolo:%s\nAutore:%s\n\n",L->titoloPtr,L->autorePtr);
            B->codaLibriPresiInPrestitoPtr=F_elimina_elemento_coda(P,S->matricola,L->titoloPtr);
            //Aggiorno il numero di copie
            L->copie=L->copie+1;
            printf("\nIl libro e' ritornato in biblioteca.\n");
        }else printf("\nLo studente non ha mai preso in prestito il libro:\nTitolo:%s\nAutore:%s\n\nLa richiesta e' annullata.\n",L->titoloPtr,L->autorePtr);

        F_elimina_elemento_coda_in_testa(&R);
        B->codaRestituzioniPtr=R;

    }else puts("\nNon sono presenti restituzioni da prendere in carico.");
}

void F_consegna_libro_allo_studente(Biblioteca B){
    Coda C=B->codaRichiestePtr;
    if(!F_struttura_vuota(C)){
        Libro L=C->codaLibro;
        Studente S=C->codaStudente;
        if(F_struttura_vuota(L)) F_error(4);
        if(F_struttura_vuota(S)) F_error(5);
        printf("\nPrendo in carico la richiesta dello studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);

        if(L->copie!=0){
            L->copie=L->copie-1;
            printf("\nLa richiesta del libro (%s) e' stata accettata.\n\n",L->titoloPtr);

            // Salvo il prestito del libro allo studente
            Coda P=B->codaLibriPresiInPrestitoPtr;
            F_inserimento_in_coda_richieste_studente(&P,S,L);
            B->codaLibriPresiInPrestitoPtr=P;

            // Elimino lo studente dalla coda delle richieste
            F_elimina_elemento_coda_in_testa(&C);
            B->codaRichiestePtr=C;

        }
        else{ // La richiesta viene sospesa e lo studente viene inserito in coda
            printf("\nIl libro (%s) richiesto dallo studente non e' disponibile. Pertanto la richiesta verra' messa in coda.\n",L->titoloPtr);
            F_elimina_elemento_coda_in_testa(&C);
            F_inserimento_in_coda_richieste_studente(&C,S,L);
            B->codaRichiestePtr=C;
        }
    }else puts("\nNon sono presenti richieste da prendere in carico.");
}


void F_sollecita_restituzione_libri(Biblioteca B){
    Coda P=B->codaLibriPresiInPrestitoPtr;
    while(!F_struttura_vuota(P)){
        Libro L=P->codaLibro;
        Studente S=P->codaStudente;
        printf("\nLo studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);
        printf("\n\nHa restituito il libro:\nTitolo:%s\nAutore:%s\n\n",L->titoloPtr,L->autorePtr);
        L->copie=L->copie+1;

        F_elimina_elemento_coda_in_testa(&P);
        //Coda elementoDaEliminare=P;
        //P=P->nextPrt;
        //free(elementoDaEliminare);
    }
    puts("\nTutti i libri presi in prestito sono stati consegnati.");
    B->codaLibriPresiInPrestitoPtr=P;
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
    (*B)->strutturaStudentiPtr=NULL;
    (*B)->strutturaLibriPtr=NULL;
    (*B)->codaRichiestePtr=NULL;
    (*B)->codaRestituzioniPtr=NULL;
    (*B)->codaLibriPresiInPrestitoPtr=NULL;
}

int F_struttura_vuota(void *S){
    return (!S);
}

void F_popolamento_da_terminale(Biblioteca B, int numeroLibri){
    if(numeroLibri!=0){
        Libro nuovo_libro=NULL; AlberoLibro T=B->strutturaLibriPtr;
        printf("Inserimento del libro numero (%d)",numeroLibri);
        char *titolo=F_chiedi_stringa("Inserisci il titolo del libro");
        char *autore=F_chiedi_stringa("Inserisci l'autore del libro");
        int copie=F_chiedi_intero("Inserisci il numero di copie del libro:",3,'1','9');
        F_alloca_struttura_libro(&nuovo_libro);
        F_inserisci_informazioni_libro(&nuovo_libro,titolo,autore,copie);
        F_inserisci_libro_abr(&T,nuovo_libro);
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
    Libro nuovo_libro=NULL; AlberoLibro T=B->strutturaLibriPtr;


   // Libri nuovo_libro=NULL;
   // Albero T=B->strutturaLibriPtr;
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
    F_inserisci_libro_abr(&T,nuovo_libro);
    B->strutturaLibriPtr=T;
}


//CANCELLA
/*
void STAMPALIBRI(AlberoLibro L){
    if(L){
        STAMPALIBRI(L->sxPtr);
        Libro a=L->nodoLibroPtr;
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
}*/

int F_cofronto_titolo_libri(char *s1, char *s2){
    return strcmp(s1,s2);
}



void F_inserisci_informazioni_libro(Libro *L,char *titolo,char *autore, int copie){
    (*L)->autorePtr=autore;
    (*L)->titoloPtr=titolo;
    (*L)->copie=copie;
}

void F_alloca_struttura_libro(Libro *L){
    (*L)=(struct struttura_gestione_libro*)malloc(sizeof(struct struttura_gestione_libro));
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


void F_stampa_menu_popolamento(){  // a
    puts("Gestione biblioteca - Popolamento");
    puts("Scegli il tipo di popolamento da efettuare:");
    puts("1] Popolamento dei libri tramite terminale (processo lungo)");
    puts("2] Popolamento dei libri automatico");
    puts("\n0] Esci");
}

void F_stampa_menu_gestione_biblioteca(){ // b
    puts("\nGestione biblioteca - Menu principale");
    puts("1] Aggiungi richiesta studente");
    puts("2] Prendi in carico una richiesta");
    puts("\n0] Termina");
}

void F_stampa_menu_gestione_biblioteca_richiesta_studente(){ // c
    puts("\nGestione biblioteca - Richiesta studente");
    puts("1] Soddisfa una richiesta");
    puts("2] Sollecita la consegna");
    puts("\n0] Indietro");
}

void F_stampa_menu_gestione_biblioteca_richiesta_o_restituzione_libro(){ // d
    puts("\nGestione biblioteca - Richiesta studente");
    puts("1] Richiesta prestito libro");
    puts("2] Richiesta restituzione libro");
    puts("\n0] Indietro");
}

void F_stampa_menu_gestione_biblioteca_presa_in_carico_richiesta_consegna_o_restituzione_libro(){
    puts("\nGestione biblioteca - Soddisfa richiesta");
    puts("1] Consegna libro");
    puts("2] Restituzione libro");
    puts("\n0] Indietro");
}