/*----ZADATAK_3----
Strukture podataka FESB
Marko Kuret 2021/2022
(LINKED-LIST, nastavak na zadatak_2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define BIG_BUFFER 65

typedef struct _osoba* position;
typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina;
    position next;
} osoba;

// fje za izbornik
int pokreniIzbornik(position head);
int unosBroja(void);

// glavne fje za upravljanje elementima
position stvoriElement();
int izbrisiElement(position head, position elementZaBrisanje);
int unosPodataka(position novaOsoba);

// fje za unos u listu
int dodajNaRub(position head, int opcija);
int dodajNakon(position ref);
int dodajPrije(position head, position ref);
int dodajSortirano(position novaOsoba, position head);

// pomocne fje
position adresaZadnjeg(position head);
position prethodniElement(position head, position ref);
position traziPrezime(position head);
position sortiraj(position stariHead);
int ispis(position head);

// upravljenje datotekama
int upisDatoteka(position head);
position citajIzDatoteke(position head);

//----MAIN----
int main()
{
    //head je "prazna" struktura (ne pointer kao u zadatak_2)
    osoba head = {.next = NULL, .ime = {0}, .prezime = {0}, .godina = 0};

    position headPtr = &head;

    pokreniIzbornik(headPtr);
    
   /*ptr = citajIzDatoteke("test.txt");
    spis(ptr->next);*/

    return EXIT_SUCCESS;
}

//najvisa funkcija koja otvara izbornik i poziva sve druge fje. po izboru korisnika,
//ako korisnik unese nevaljani izlaz program se prekida
int pokreniIzbornik(position head)
{
    position buffer = NULL;
    
    //intigeri postavljeni na redudantne vrijednosti
    int opcija = 4, pod_opcija = 2;

    //char se koristi za unos odgovora d/n
    char c = 'n';
    
    while(1)
    {
        printf("----OPCIJE:----\n    1 - dodaj element\n    2 - briši element po prezimenu\n"
        "    3 - upis u datoteku\n    4 - unos iz datoteke\n    5 - sortiraj i ispisi\n    6 - ispis\n    7 - izlaz\n");
        opcija = unosBroja();

        switch (opcija)
        {
            // dodaj element
            case 1:
                printf("--Unos podataka--\n  OPCIJE:\n      1 - dodaj na pocetak\n"
                "      2 - dodaj na kraj\n      3 - dodaj nakon određenog elementa\n      4 - dodaj prije određenog elementa\n");
                pod_opcija = unosBroja();

                switch (pod_opcija)
                {
                    //dodavanje na pocetak ili kraj
                    case 1:
                    case 2:
                        dodajNaRub(head, pod_opcija);
                        break;

                    case 3: 
                        printf("Prezime osobe nakon koje dodajete: ");
                        buffer = traziPrezime(head);
                        if(buffer)
                            dodajNakon(buffer);
                        break;

                    case 4:
                        printf("Prezime osobe prije koje dodajete: ");
                        buffer = traziPrezime(head);
                        if(buffer)
                            dodajPrije(head, buffer);
                        break;

                    default:
                        break;
                }
                break;
            
            //brisi element po prezimenu
            case 2:
                printf("Prezime osobe koju zelite izbrisati: ");
                buffer = traziPrezime(head);
                if(buffer)
                {
                    printf("    Jeste li sigurni? d/n: ");
                    scanf(" %c", &c);
                    if (c == 'd')
                        izbrisiElement(head, buffer);
                }
                break;

            //upisi u listu u datoteku
            case 3:
                upisDatoteka(head->next);
                break;

            case 4:
                head = citajIzDatoteke(head);
                ispis(head->next);
                break;

            //sortiranje
            case 5:
                buffer = sortiraj(head);
                ispis(buffer->next);
                break;

            //ispis
            case 6:
                ispis(head->next);
                break;

            //izlaz iz programa
            case 7:
                return EXIT_SUCCESS;

            //default, vraca na pocetak i sprjecava overflow
            default:
                printf("Nevaljani unos!\n\n");
                scanf(" %c", &c);
                break;
        }
    }

    return EXIT_SUCCESS;
}

//fja prima intiger unos korisnika i radi provjeru
int unosBroja(void)
{
    int c = 0;
    int broj = -1;
    c = scanf(" %d", &broj);

    if (c != 1)
    {
        printf("Nije ispravan broj!\n"); 
        return -1;
    }

    //hvata enter
    c = getchar();

    return broj;
}

//alocira memoriju za novi element, postavlja next pointer na NULL, vraca lokaciju alocirane memorije
position stvoriElement()
{
    position novaOsoba = NULL;
    novaOsoba = (position)malloc(sizeof(osoba));
    if(!novaOsoba)
    {
        perror("Greška alokacije! ");
        return NULL;
    }
    novaOsoba->next = NULL;

    return novaOsoba;
}

//prima head i poziciju elementa za brisanje kojeg onda brise
int izbrisiElement(position head, position elementZaBrisanje)
{
    position tmp = head;

    while (tmp->next != elementZaBrisanje)
    {
        tmp = tmp->next;
    }
    
    tmp->next = elementZaBrisanje->next;
    free(elementZaBrisanje);
    printf("Element izbrisan!\n");

    return EXIT_SUCCESS;
}

//unosi podatke, koje upisuje korisnik,u novi element
int unosPodataka(position novaOsoba)
{   
    //buffer
    char big_buffer[BIG_BUFFER];

    //--unos podataka
    printf("Ime Prezime Godina: ");
    fgets(big_buffer, BIG_BUFFER, stdin);
    sscanf(big_buffer, " %s %s %d", novaOsoba->ime, novaOsoba->prezime, &novaOsoba->godina);

    return EXIT_SUCCESS;
}

//fja. koja dodaje novi element na rub liste, argumenti su head i opcija, za opcija 1 ili 2 dodaje na pocetak ili kraj
int dodajNaRub(position head, int opcija)
{
    position novaOsoba = NULL;
    position tmp = NULL;

    novaOsoba = stvoriElement();
    if(novaOsoba == NULL)
    {
        printf("Neuspjesan unos! ");
        return EXIT_FAILURE;
    }
    unosPodataka(novaOsoba);
    
    // ako je head->next NULL, nema elemenata u listi i svakako je dodavanje na pocetak
    // dodavanje na pocetak je opcija 0
    if (!head->next)
        opcija = 1;

    switch(opcija)
    {
        //dodavanje na pocetak
        case 1:
            novaOsoba->next = head->next;
            head->next = novaOsoba;
            break;
        
        //dodavanje na kraj
        case 2:
            tmp = adresaZadnjeg(head);
            novaOsoba->next = NULL;
            tmp->next = novaOsoba;
            break;

        default:
            printf("Greška u dodavanju");
            return EXIT_FAILURE;
    }

    return 0;
}

//dodaje novi element nakon određenog, vraca 1 ako je uspjesno
int dodajNakon(position ref)
{
    position novaOsoba = NULL, tmp = NULL;
    novaOsoba = stvoriElement();
    unosPodataka(novaOsoba);
    tmp = ref->next;
    ref->next = novaOsoba;
    novaOsoba->next = tmp;

    return EXIT_SUCCESS;
}

// dodaje novi element prije ref elementa, tako da pronalazi element prije referentnog elementa i onda poziva fju. dodaj nakon
int dodajPrije(position head, position ref)
{
    position novaOsoba = NULL, tmp = NULL;
    tmp = prethodniElement(head, ref);
    dodajNakon(tmp);

    return EXIT_SUCCESS;
}

// dodaje novi element u listu po abecednom redu
int dodajSortirano(position novaOsoba, position head)
{
    position tmp = head;
    
    while (tmp->next != NULL && (strcmp(tmp->next->prezime, novaOsoba->prezime) < 0))
        tmp = tmp->next;
    
    novaOsoba->next = tmp->next;
    tmp->next = novaOsoba;

    return EXIT_SUCCESS;
}

//vraca adresu zadnjeg elementa u listi koju ulaz head pokazuje
position adresaZadnjeg(position head)
{
    if (!head->next)
        return NULL;

    position tmp = head->next;

    while (tmp->next)
    {
        tmp = tmp->next;
    }
    return tmp;
}

// vraća poziciju prethodnog elmenta od elementa iz argumenta
position prethodniElement(position head, position ref)
{
    position tmp = head->next;

    while (tmp->next != ref)
    {
        tmp = tmp->next;
    }
    return tmp;
}

// vraća poziciju prve osobe s odredenim prezimenom
position traziPrezime(position head)
{
    //buffer
    char prezime[MAX];
    
    fgets(prezime, MAX, stdin);
    sscanf(prezime, "%s", prezime);
    
    position tmp = head->next;

    while(tmp)
    {
        if (strcmp(tmp->prezime, prezime) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }

    //ako ne pronađe
    printf("Nema osobe s tim prezimenom\n");

    return NULL;
}

//soritra staru listu i vraca adresu novog heada
position sortiraj(position stariHead)
{
    osoba noviHead = {.next = NULL, .ime = {0}, .prezime = {0}, .godina = 0};
    position ptr = &noviHead;
    position stariPtr = stariHead;
    position novaOsoba = NULL;

    while(stariPtr)
    {
        //novaOsoba = kopirajElement(tmp);
        
        novaOsoba = stariPtr;
        stariPtr = stariPtr->next;
        dodajSortirano(novaOsoba, ptr);
    }
    
    return ptr;
}

//ispisuje cijelu listu
int ispis(position first)
{
    printf("\n--ISPIS:--\n");
    position tmp = first;
    while(tmp)
    {
        printf("%s %s %d \n", tmp->ime, tmp->prezime, tmp->godina);
        tmp = tmp->next;
    }

    puts("");

    return EXIT_SUCCESS;
}

// upisuje cijelu listu u novu datoteku (korisnik upisuje samo ime datoteke, bez tipa)
int upisDatoteka(position first)
{
    FILE * fp = NULL;
    position tmp = first;
    char datoteka[MAX];
    
    printf("Ime datoteke: ");
    fgets(datoteka, MAX, stdin);
    sscanf(datoteka, "%s", datoteka);

    strcat(datoteka,".txt");

    fp = fopen(datoteka, "w");
    if(!fp)
    {
        perror("Greška u stvaranju datoteke");
        return EXIT_FAILURE;
    }
    
    while(tmp)
    {
        fprintf(fp, "%s %s %d\n", tmp->ime, tmp->prezime, tmp->godina);
        tmp = tmp->next;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

//fja cita iz datoteke koja je dana u argumentu i upisuje elemente u listu
position citajIzDatoteke(position head)
{
    position novaOsoba = NULL;
    FILE * dat = NULL;
    char buffer[BIG_BUFFER];
    char imeDat[MAX];
    
    printf("Ime datoteke (s ekstenzijom): ");

    fgets(imeDat, MAX, stdin);
    sscanf(imeDat, " %s", imeDat);
    head->next = NULL;

    dat = fopen(imeDat, "r");
    if (!dat)
    {
        perror("Greška u otvaranju datoteke! ");
        return NULL;
    }
    
    while (!feof(dat))
    {
        novaOsoba = stvoriElement();
        fgets(buffer, BIG_BUFFER, dat);
        sscanf(buffer, " %s %s %d", novaOsoba->ime, novaOsoba->prezime, &novaOsoba->godina);
        novaOsoba->next = head->next;
        head->next = novaOsoba;
    }

    fclose(dat);
    return head;
}