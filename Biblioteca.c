#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Error.h"
#include "Abr.h"
#include "Coda.h"
#define NUMERO_LIBRI_POPOLAMENTO 15
#define LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE 40
/*
 * NUMERO_LIBRI_POPOLAMENTO->valore numerico del totale dei libri che si vogliono
 * aggiungere alla biblioteca. Se il valore e' >15 il popolamento automatico va
 * modificato aggiungendo un numero di libri maggiore. Se il valore e' <15 il po-
 * polamento automatico inserisce un sottinsieme di libri predefiniti.
 * Il valore non influisce il popolamento tramite terminale, tranne il numero di
 * libri da inserire.
 * LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE->valore numerico massimo di caratteri
 * che verranno presi in input. Tale valore specifica: titolo, autore del libro e nome,
 * cognome dello studente.
 *
 */


/*
 *  Descrizione: gestione della biblioteca
 *  Dettagli: gestisce l'intera biblioteca e ogni sua componente
 *  Parametri in: //
 *  Parametri out: //
 *  Chiamante: Main->main
 *
*/
void F_gestione_biblioteca(){
    /*
     * Cuore del programma esegue:
     * allocazione della struttura principale contenente
     * tutte le informazioni sulla gestione delle biblioteca,
     * popolamento dell'albero dei libri,
     * esecuzione e gestione della biblioteca e infine la deal-
     * locazione di tutte le strutture dati usate
     *
     */
    Biblioteca B=NULL;
    F_alloca_struttura_biblioteca(&B);
    F_popolamento(B);
    F_engine_biblioteca(B);
    F_dealloca_strutture(B);
}

/*
 *  Descrizione: gestione di tutte le funzionalita' della biblioteca
 *  Dettagli:    //
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_gestione_biblioteca
 *
*/
void F_engine_biblioteca(Biblioteca B){
    int sceltaMenu=0, uscitaMenu=-1;
    do{
        F_stampa_menu_gestione_biblioteca();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');
        switch(sceltaMenu){
            default:
                break;
            case 1: /* Aggiungi richiesta studente */
                F_aggiungi_richiesta_studente(B);
                break;
            case 2: /* Stampa sottomenu gestione richieste */
                F_stampa_menu_gestione_biblioteca_richiesta_studente();
                sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');
                switch(sceltaMenu){
                    default:
                        break;
                    case 1: /* Prendi in carico una richiesta */
                        F_prendi_in_carico_una_richiesta_studente(B);
                        break;
                    case 2: /* Sollecita restituzione libri */
                        F_sollecita_restituzione_libri(B);
                        break;
                }
                break;
            case 0: /* Uscita dal programma */
                uscitaMenu=F_verifica_richieste(B);
                break;
        }
    }while(uscitaMenu!=0);
}

/*
 *  Descrizione: verifica la presenza di richieste in coda
 *  Dettagli: vengono verificate tutte le code, se una di queste
 *            contiene ancora delle informazioni il programma non
 *            termina
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: controlloRichieste->0 tutte le code sono vuote
 *                                    -1 almeno una coda non e' vuota
 *  Chiamante: Biblioteca->F_engine_biblioteca
 *
*/
int F_verifica_richieste(Biblioteca B){
    int controlloRichieste=-1;
    Coda richieste=B->codaRichiestePtr;
    Coda prestiti=B->codaLibriPresiInPrestitoPtr;
    Coda restituzioni=B->codaRestituzioniPtr;
    /*
     * Ogni coda che e' stata creata va verificata se ci sono ancora:
     * studenti che hanno fatto una richiesta di prendere un libro
     * studenti cha hanno fatto una richiesta per restituire un libro
     * studenti che hanno preso in prestito un libro
     *
     * Basta che una di queste code non sia vuota per non permettere l'uscita
     * dal programma come concordato nel progetto. Si informa l'utente sulle
     * azioni da intraprendere (sollecitare la consegna)
     *
     */
    if(!F_struttura_vuota(richieste) || (!F_struttura_vuota(restituzioni))) printf("\nSono presenti ancora delle richieste da prendere in carico.\nE' consigliabile sollecitare la restituzione.");
    if(!F_struttura_vuota(prestiti)) printf("\nSono presenti ancora delli libri che devono essere restituiti.\nE' consigliabile sollecitare la restituzione.");
    if(F_struttura_vuota(richieste) && F_struttura_vuota(prestiti) && F_struttura_vuota(restituzioni)){
        printf("\nTutte le richieste sono state effettuate. Uscita.\n");
        controlloRichieste=0;
    }

    return controlloRichieste;
}

/*
 *  Descrizione: selezione per la richiesta di libri
 *  Dettagli: permette di selzionare se richiedere il prestito di un libro
 *            oppure richiedere la restituzione di un libro
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_engine_biblioteca
 *
*/
void F_aggiungi_richiesta_studente(Biblioteca B){
    int sceltaMenu=0;
    F_stampa_menu_gestione_biblioteca_richiesta_o_restituzione_libro();
    sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

    switch(sceltaMenu){
        default:
            break;
        case 1: /* Richiesta per prestito libro */
            F_aggiungi_richiesta_studente_prestito_libro(B);
            break;
        case 2: /* Richiesta per restituzione per libro */
            F_aggiungi_richiesta_studente_restituzione_libro(B);
            break;
    }

}

/*
 *  Descrizione: gestione libri da restituire
 *  Dettagli: accoda la restituzione di un libro
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_aggiungi_richiesta_studente
 *
*/
void F_aggiungi_richiesta_studente_restituzione_libro(Biblioteca B){
    /*
     * Lo studente puo' richiedere di una futua restituzione di un libro. La restituzione viene
     * effettuata chiedendo il titolo da consegnare. Viene veridicato se il libro e' presente
     * nel catalogo dei libri in biblioteca, pena l'annullamento della richiesta.
     * Se il libro e' presente in biblioteca la richiesta di restituzione viene accettata, sara'
     * poi carico del gestore della biblioteca eseguire le funzioni che vadano ad accettare la restituzione
     *
     */
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

/*
 *  Descrizione: gestione libri da prendere in prestito
 *  Dettagli: accoda il prestito di un libro
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_aggiungi_richiesta_studente
 *
*/
void F_aggiungi_richiesta_studente_prestito_libro(Biblioteca B){
    /*
     * Lo studente puo' richiedere di prendere in prestito un libro. Viene verificato
     * che il libro sia presente nella biblioteca, pena l'annullamento della richiesta.
     * Se il libro e' presente allora la richiesta viene accettata, sara' poi carico del
     * gestore della biblioteca eseguire le funzioni che vadano a consegnare il libro allo
     * studente
     *
    */
    Studente verifica_studente=F_verifica_registrazione_studente_biblioteca(B);

    AlberoLibro L=B->strutturaLibriPtr;
    char *titoloLibroRichiesto=F_chiedi_stringa("Titolo del libro da prendere in prestito");

    Libro libroScelto=F_cerca_libro_abr(&L,titoloLibroRichiesto);

    if(libroScelto){
        printf("\nIl libro (%s) e' presente nella biblioteca, inserisco la richiesta in coda.\n\n",libroScelto->titoloPtr);
        Coda C=B->codaRichiestePtr;
        F_inserimento_in_coda_richieste_studente(&C,verifica_studente,libroScelto);
        B->codaRichiestePtr=C;
    } else printf("\nIl libro (%s) non e' presente nell'archivio libi della biblioteca. Richiesta annullata.\n\n",titoloLibroRichiesto);
}

/*
 *  Descrizione: verifica se uno studente e' registrato
 *  Dettagli: qualsiasi richiesta richiede che lo studente sia registrato
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: verifica_studente->contiene le informazioni dello studente
 *  Chiamante: Biblioteca->F_aggiungi_richiesta_studente_restituzione_libro
 *             Biblioteca->F_aggiungi_richiesta_studente_prestito_libro
 *
*/
Studente F_verifica_registrazione_studente_biblioteca(Biblioteca B){
    /*
     * Viene chiesto l'inserimendo della matricola dello studente. Si verifica se lo studente
     * e' registrato nell'albero degli studenti. Se non lo e' viene chiesto l'inserimento delle sue informazioni,
     * caso contrario l'albero ritorna lo studente gia' registrato e il sistema mostra le sue informazioni
     *
     */
    int matricola=F_chiedi_intero("Inserisci la matricola dello studente che richiede un libro:",10,'0','9');
    AlberoStudente S=B->strutturaStudentiPtr;
    Studente verifica_studente=F_cerca_studente_abr(&S,matricola);
    /*
     * La funzione F_cerca_studente_abr ritorna l'indirizzo contentente la struttura
     * dello studente se questi e' registrato, altimenti ritorna null
     */
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

/*
 *  Descrizione: registra uno studente
 *  Dettagli: se lo studente non ha mai fatto alcuna richiesta
 *            viene registrato
 *  Parametri in: S->struttura studente
 *                matricola->matricola dello studente
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_aggiungi_richiesta_studente_restituzione_libro
 *             Biblioteca->F_aggiungi_richiesta_studente_prestito_libro
 *
*/
void F_richiedi_informazioni_studente(Studente *S, int matricola){
    (*S)=(struct struttura_gestione_studente*)malloc(sizeof(struct struttura_gestione_studente));
    if(F_struttura_vuota(*S)) F_error(6);
    printf("\nStudente con matricola (%d) non presente nell'archivio della biblioteca.\nSi prega di aggiungerlo.",matricola);
    char *nome=F_chiedi_stringa("nome dello studente:");
    char *cognome=F_chiedi_stringa("cognome dello studente:");
    (*S)->matricola=matricola;
    (*S)->nomePtr=nome;
    (*S)->cognomePtr=cognome;
}

/*
 *  Descrizione: gestite le richieste fatte dagli studenti
 *  Dettagli: permette di consegnare un libro allo studente oppure
 *            prende il libro che lo studente aveva preso in prestito
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_engine_biblioteca
 *
*/
void F_prendi_in_carico_una_richiesta_studente(Biblioteca B){
    int sceltaMenu=0;
    F_stampa_menu_gestione_biblioteca_presa_in_carico_richiesta_consegna_o_restituzione_libro();
    sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

    switch(sceltaMenu){
        default:
            break;
        case 1: /* Consegna il libro allo studente */
            F_consegna_libro_allo_studente(B);
            break;
        case 2: /* Prendi il libro che aveva in prestito uno studente */
            F_studente_restituisce_libro(B);
            break;
    }

}

/*
 *  Descrizione: gestisce la restituzione di un libro
 *  Dettagli: prende il libro che lo studente aveva preso in prestito e
 *            lo aggiunge di nuovo in biblioteca
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_prendi_in_carico_una_richiesta_studente
 *
*/
void F_studente_restituisce_libro(Biblioteca B){
    /*
     * Si prende la coda contenente tutti gli studenti che avevo chiesto di voler
     * consegnare un libro. Si verifica che lo studente avesse preso in prestito il libro, caso
     * affermativo si incrementa il numero di copie del libro di 1 e la richiesta viene eliminata.
     * Caso negativo significa che lo studente aveva fatto richiesta di consegna di un libro che non ha
     * mai preso
     *
     */
    Coda R=B->codaRestituzioniPtr;
    if(!F_struttura_vuota(R)){
        Libro L=R->codaLibro;
        Studente S=R->codaStudente;
        if(F_struttura_vuota(L)) F_error(6);
        if(F_struttura_vuota(S)) F_error(7);
        printf("\nPrendo in carico la richiesta dello studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);

        Coda P=B->codaLibriPresiInPrestitoPtr;
        int controlloPrestiti=F_cerca_elemento_coda(&P,S->matricola,L->titoloPtr);
        /*
         * F_cerca_elemento_coda verifica che effettivamente lo studente ha preso in prestito il libro
         * che sta consegnando
         */
        if(controlloPrestiti){
            printf("\nLo studente aveva preso in prestito il libro:\nTitolo:%s\nAutore:%s\n\n",L->titoloPtr,L->autorePtr);
            B->codaLibriPresiInPrestitoPtr=F_elimina_elemento_coda(P,S->matricola,L->titoloPtr);
            /* Aggiorno il numero di copie */
            L->copie=L->copie+1;
            printf("\nIl libro e' ritornato in biblioteca.\n");
        }else printf("\nLo studente non ha mai preso in prestito il libro:\nTitolo:%s\nAutore:%s\n\nLa richiesta e' annullata.\n",L->titoloPtr,L->autorePtr);

        F_elimina_elemento_coda_in_testa(&R);
        B->codaRestituzioniPtr=R;

    }else puts("\nNon sono presenti restituzioni da prendere in carico.");
}

/*
 *  Descrizione: gestisce la consegna di un libro
 *  Dettagli: permette di cosegnare il libro scelto dalla studente
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_prendi_in_carico_una_richiesta_studente
 *
*/
void F_consegna_libro_allo_studente(Biblioteca B){
    /*
     * Si prende la coda contenente tutte le richieste di libri fatte dagli studenti.
     * Si verifica se il libro e' disponibile. Risposta affermativa  il libro viene consegnato
     * e le informazioni dello studente e del libro preso vengono inserite nella codaPresiInPrestito.
     * Risposta negativa la richiesta di consegna del libro viene posta in coda a tutte le altre richieste
     * sperando che qualche altro studente consegni il libro
     *
     */
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

            /* Salvo il prestito del libro allo studente */
            Coda P=B->codaLibriPresiInPrestitoPtr;
            F_inserimento_in_coda_richieste_studente(&P,S,L);
            B->codaLibriPresiInPrestitoPtr=P;

            /* Elimino lo studente dalla coda delle richieste */
            F_elimina_elemento_coda_in_testa(&C);
            B->codaRichiestePtr=C;

        }
        else{ /* La richiesta viene sospesa e lo studente viene inserito in coda */
            printf("\nIl libro (%s) richiesto dallo studente non e' disponibile. Pertanto la richiesta verra' messa in coda.\n",L->titoloPtr);
            F_elimina_elemento_coda_in_testa(&C);
            F_inserimento_in_coda_richieste_studente(&C,S,L);
            B->codaRichiestePtr=C;
        }
    }else puts("\nNon sono presenti richieste da prendere in carico.");
}

/*
 *  Descrizione: sollecita la restituzione dei libri
 *  Dettagli: tutti i libri presi in prestito dagli studenti vengono
 *            riconsegnati in biblioteca. Inoltre le richieste di prestito
 *            o consegna vengono annullate
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_engine_biblioteca
 *
*/
void F_sollecita_restituzione_libri(Biblioteca B){
    /*
     * Per evitare deadlock la sollecitazione permette di far
     * consegnare agli studenti tutti i libri che hanno preso
     * in prestito e di eliminare tutte le loro richieste di
     * consegna e restituzione dei libri
     *
     */
    Coda P=B->codaLibriPresiInPrestitoPtr;
    F_sollecita_restituzione_libri_presi_in_prestito(&P);
    B->codaLibriPresiInPrestitoPtr=P;

    Coda R=B->codaRestituzioniPtr;
    F_sollecita_restituzione_libri_restituzioni(&R);
    B->codaRestituzioniPtr=R;

    Coda RR=B->codaRichiestePtr;
    F_sollecita_restituzione_libri_richiesti(&RR);
    B->codaRichiestePtr=RR;
}

/*
 *  Descrizione: sollecita la restizione dei libri
 *  Dettagli: vengono annullate tutte le richieste di prestito libri
 *  Parametri in: C->coda contenente le richieste di prestito fatte
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_sollecita_restituzione_libri
 *
*/
void F_sollecita_restituzione_libri_richiesti(Coda *C){
    if(!F_struttura_vuota(*C)){
        Libro L=(*C)->codaLibro;
        Studente S=(*C)->codaStudente;
        printf("\nLo studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);
        printf("\n\nAveva richiesto il libro:\nTitolo:%s\nAutore:%s\nIl sollecito ha annullato la richiesta.\n",L->titoloPtr,L->autorePtr);
        F_sollecita_restituzione_libri_richiesti((&(*C)->nextPrt));
        F_elimina_elemento_coda_in_testa((&(*C)));
    }
}

/*
 *  Descrizione: sollecita la restizione dei libri
 *  Dettagli: vengono annullate tutte le richieste di consegna libri
 *  Parametri in: C->coda contentente le richieste di restituzione fatte
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_sollecita_restituzione_libri
 *
*/
void F_sollecita_restituzione_libri_restituzioni(Coda *C){
    if(!F_struttura_vuota(*C)){
        Libro L=(*C)->codaLibro;
        Studente S=(*C)->codaStudente;
        printf("\nLo studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);
        printf("\n\nAveva richiesto di restituire il libro:\nTitolo:%s\nAutore:%s\nIl sollecito ha annullato la richiesta.\n",L->titoloPtr,L->autorePtr);
        F_sollecita_restituzione_libri_restituzioni((&(*C)->nextPrt));
        F_elimina_elemento_coda_in_testa((&(*C)));
    }
}

/*
 *  Descrizione: sollecita la restizione dei libri
 *  Dettagli: ogni studente consegna il/i libro/i preso in prestito
 *  Parametri in: C->coda degli studenti che hanno preso un libro in prestito
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_sollecita_restituzione_libri
 *
*/
void F_sollecita_restituzione_libri_presi_in_prestito(Coda *C){
    if(!F_struttura_vuota(*C)){
        Libro L=(*C)->codaLibro;
        Studente S=(*C)->codaStudente;
        printf("\nLo studente:\nMatricola:%d\nCognome:%s\nNome:%s",S->matricola,S->cognomePtr,S->nomePtr);
        printf("\n\nHa restituito il libro:\nTitolo:%s\nAutore:%s\n\n",L->titoloPtr,L->autorePtr);
        L->copie=L->copie+1;
        F_sollecita_restituzione_libri_presi_in_prestito((&(*C)->nextPrt));
        F_elimina_elemento_coda_in_testa((&(*C)));
    }
}

/*
 *  Descrizione: scelta sul tipo di popolamento da effettuare
 *  Dettagli: viene scelto il tipo di popolamento (automatico-da terminale)
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_gestione_biblioteca
 *
*/
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
            exit(0);
    }
}

/*
 *  Descrizione: alloca la struttura principale
 *  Dettagli: //
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: ///
 *  Chiamante: Biblioteca->F_gestione_biblioteca
 *
*/
void F_alloca_struttura_biblioteca(Biblioteca *B){
    (*B)=(struct struttura_gestione_biblioteca*)malloc(sizeof(struct struttura_gestione_biblioteca));
    if(F_struttura_vuota(*B)) F_error(1);
    (*B)->strutturaStudentiPtr=NULL;
    (*B)->strutturaLibriPtr=NULL;
    (*B)->codaRichiestePtr=NULL;
    (*B)->codaRestituzioniPtr=NULL;
    (*B)->codaLibriPresiInPrestitoPtr=NULL;
}

/*
 *  Descrizione: verifica se una struttura e' vuota
 *  Dettagli: //
 *  Parametri in: S->qualsiasi tipo di struttura
 *  Parametri out: 1->struttura vuota
 *                 0->altrimenti
 *
*/
int F_struttura_vuota(void *S){
    return (!S);
}

/*
 *  Descrizione: permette il popolamento dei libri
 *  Dettagli: riceve da terminale le informazioni per popolare
 *            la biblioteca con libri scelti dall'utente
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_popolamento
 *
*/
void F_popolamento_da_terminale(Biblioteca B, int numeroLibri){
    /*
     * Chiede all'utente di inserire un totale di 15 libri come da progetto.
     * Presi in input: titolo, autore e il numero di copie del libro, viene
     * allocata la struttura per i libri e inserita nell'albero abr che gesti-
     * sce tutti i libri della biblioteca
     *
     */
    if(numeroLibri!=0){
        Libro nuovo_libro=NULL; AlberoLibro T=B->strutturaLibriPtr;
        printf("\nInserimento del libro numero (%d)",numeroLibri);
        char *titolo=F_chiedi_stringa("Inserisci il titolo del libro");
        char *autore=F_chiedi_stringa("Inserisci l'autore del libro");
        int copie=F_chiedi_intero("\nInserisci il numero di copie del libro:",3,'1','9');
        F_alloca_struttura_libro(&nuovo_libro);
        F_inserisci_informazioni_libro(&nuovo_libro,titolo,autore,copie);
        F_inserisci_libro_abr(&T,nuovo_libro);
        B->strutturaLibriPtr=T;
        F_popolamento_da_terminale(B,numeroLibri-1);
    }
}

/*
 *  Descrizione: prende in ingresso una stringa
 *  Dettagli: vengono prese massimo LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE
 *            caratteri qualsiasi. Successivamente si crea una stringa delle
 *            dimensioni adatte a quella inserita in input
 *  Parametri in: s->testo che viene mostrato in output all'utente
 *  Parametri out: stringa_uscita->stringa presa in input
 *
*/
char *F_chiedi_stringa(char *s){
    /*
     * Viene preso qualsiasi carattere in imput a patto che:
     * non si superi il valore LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE,
     * non si arrivi a un new line
     * non si arrivi a end of file
     *
     */
    char *tmp=NULL,c='*';
    void *stringa_uscita=NULL;
    int i=0;

    tmp=(char *)malloc((LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE)*sizeof(char));
    if(F_struttura_vuota(tmp)) F_error(7);
    printf("\nInserisci %s (MAX:%d):",s,LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE);

    for(i=0; (i<LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE && (c= (char) getchar()) != '\n' && c != EOF); i++){
        tmp[i]=c;
    }
    tmp[i]='\0';

    /*
     * Allocazione del giusto spazio per la stringa che e' stata
     * presa in imput
     *
     */
    stringa_uscita=malloc(i*sizeof(char));
    if(F_struttura_vuota(stringa_uscita)) F_error(7);

    /*
     * Copia della stringa nello spazio adibito al suo contenimento
     *
     */
    strcpy(stringa_uscita,tmp);
    free(tmp);

    return stringa_uscita;
}

/*
 *  Descrizione: richiama la funzione per il popolamento automatico
 *  Dettagli: //
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_popolamento
 *
*/
void F_popolamento_automatico(Biblioteca B, int numeroLibri){
    if(numeroLibri!=0){
        F_popolamento_automatico_libro(B,numeroLibri);
        F_popolamento_automatico(B,numeroLibri-1);
    }
}

/*
 *  Descrizione: popola la biblioteca con libri predefiniti
 *  Dettagli: //
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_popolamento_automatico
 *
*/
void F_popolamento_automatico_libro(Biblioteca B, int sceltaLibro){
    /*
     * La procedura e' chiamata in automatico passando il numero del libro
     * da inserire in automatico (da 15 a 1). Per ogni libro viene creata la
     * sturrura apposita, rimpita con le informazioni del libro e aggiunta allo
     * albero abr che gestisce tutti i libri della biblioteca
     *
     */
    Libro nuovo_libro=NULL; AlberoLibro T=B->strutturaLibriPtr;
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

/*
 *  Descrizione: deallocazione di tutte le strutture
 *  Dettagli: //
 *  Parametri in: B->struttura principale contenente tutti i dati della
 *                biblioteca
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_gestione_biblioteca
 *
*/
void F_dealloca_strutture(Biblioteca B){
    /*
     * Vengono deallocate tutte le strutture che non siano
     * vuote. Viene eseguita prima di uscire dall'applicativo
     *
     */
    Coda richieste=B->codaRichiestePtr;
    Coda restituzioni=B->codaRestituzioniPtr;
    Coda prestiti=B->codaLibriPresiInPrestitoPtr;
    AlberoLibro alberoLibro=B->strutturaLibriPtr;
    AlberoStudente alberoStudente=B->strutturaStudentiPtr;

    if(!F_struttura_vuota(richieste)) F_dealloca_struttura_coda(&richieste);
    if(!F_struttura_vuota(restituzioni)) F_dealloca_struttura_coda(&restituzioni);
    if(!F_struttura_vuota(prestiti)) F_dealloca_struttura_coda(&prestiti);
    if(!F_struttura_vuota(alberoLibro)) F_dealloca_struttura_albero_libro(&alberoLibro);
    if(!F_struttura_vuota(alberoStudente)) F_dealloca_struttura_albero_studente(&alberoStudente);
}

/*
 *  Descrizione: confronto di due stringhe
 *  Dettagli: //
 *  Parametri in: s1-s2: stringhe da confrontare
 *  Parametri out: 0->stringhe identiche
 *                 <0->stringa s1 < stringa s2
 *                 >0->stringa s1 > stringa s2
 *
*/
int F_cofronto_titolo_libri(char *s1, char *s2){
    return strcmp(s1,s2);
}

/*
 *  Descrizione: inserisce le informazioni di un libro
 *  Dettagli: //
 *  Parametri in: L->struttura del libro
 *                titolo/autore/copie: come da nome
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_popolamento_automatico_libro
 *             Biblioteca->F_popolamento_da_terminale
 *
*/
void F_inserisci_informazioni_libro(Libro *L,char *titolo,char *autore, int copie){
    (*L)->autorePtr=autore;
    (*L)->titoloPtr=titolo;
    (*L)->copie=copie;
}

/*
 *  Descrizione: alloca la struttura per un libro
 *  Dettagli: //
 *  Parametri in: L->struttura del libro
 *  Parametri out: //
 *  Chiamante: Biblioteca->F_popolamento_automatico_libro
 *             Biblioteca->F_popolamento_da_terminale
 *
*/
void F_alloca_struttura_libro(Libro *L){
    (*L)=(struct struttura_gestione_libro*)malloc(sizeof(struct struttura_gestione_libro));
    if(F_struttura_vuota(*L)) F_error(2);
    (*L)->autorePtr=NULL;
    (*L)->titoloPtr=NULL;
    (*L)->copie=0;
}

/*
 *  Descrizione: prende in intero da terminale
 *  Dettagli: permette di prendere solo valori numerici scartando
 *            eventuali altri caratteri. I parametri passati alla
 *            funzione permettono di creare un range di numeri che
 *            possono essere accettati, altimenti viene chiesto di
 *            inserire di nuovo il valore
 *  Parametri in: s->stringa da mostrare in output all'utente
 *                dim->dimensione del vettore che conterrà i valori numerici presi in inmput
 *                minimo->valore piu' piccolo che puo' essere preso
 *                massimo->valore massimo che puo' essere preso
 *  Parametri out: intero preso in input
 *
*/
int F_chiedi_intero(char *s,int dim,char minimo,char massimo){
    /*
     * Permette di prendere un interno dall'input. Vengono scartati tutti
     * i caratteri che non sono numeri. Informazioni sui parametri presi dalla
     * funzione in alto.
     * Si prendono valori numerici fin tanto che:
     * non si raggiunge un new line
     * non si supera il parametro dim
     * non si raggiunge end of file
     *
     */
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
        }else flag=1; /* Valore corretto */
    }while(flag==0);

    /*
     * Viene creato un elemento di tipo intero adibito
     * a contenere il valore preso in imput e restituito
     */
    int *elemento=malloc(sizeof(int));
    if(F_struttura_vuota(elemento)) F_error(8);
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

/*
 *  Descrizione: funzioni di menu mostrate all'utente
 *
*/
void F_stampa_menu_popolamento(){
    puts("Laboratorio di algoritmi e strutture dati\nSimone Margio - N86001098");
    puts("-------------------------------------------------------------");
    puts("Gestione biblioteca - Popolamento\n");
    puts("Scegli il tipo di popolamento da efettuare:");
    puts("1] Popolamento dei libri tramite terminale (processo lungo)");
    puts("2] Popolamento dei libri automatico");
    puts("\n0] Esci");
    puts("-------------------------------------------------------------");
}

void F_stampa_menu_gestione_biblioteca(){
    puts("---------------------------------------------");
    puts("\nGestione biblioteca - Menu principale\n");
    puts("1] Aggiungi richiesta studente");
    puts("2] Prendi in carico una richiesta");
    puts("\n0] Termina");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_biblioteca_richiesta_studente(){
    puts("---------------------------------------------");
    puts("\nGestione biblioteca - Operazione richieste\n");
    puts("1] Soddisfa una richiesta");
    puts("2] Sollecita la consegna");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_biblioteca_richiesta_o_restituzione_libro(){
    puts("---------------------------------------------");
    puts("\nGestione biblioteca - Richiesta studente\n");
    puts("1] Richiesta prestito libro");
    puts("2] Richiesta restituzione libro");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_biblioteca_presa_in_carico_richiesta_consegna_o_restituzione_libro(){
    puts("---------------------------------------------");
    puts("\nGestione biblioteca - Soddisfa richiesta\n");
    puts("1] Consegna libro");
    puts("2] Restituzione libro");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}