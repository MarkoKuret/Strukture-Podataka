#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define SMALL_BUFFER 15

typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina;
    struct _osoba* next;
} osoba;

//nisam koristio typedef struct _osoba* position jer mi je ovako preglednije

int dodajElement(osoba** head, int opcija);
int unosPodataka(osoba* novaOsoba);
int overEngineeredUnos(char* big_buffer, char* small_buff, char* vrijednost);
int ispis(osoba* head);
osoba* adresaZadnjeg(osoba* head);
osoba* traziPrezime(osoba* head, char* prezime);
int izbrisiElement(osoba* head, osoba* elementZaBrisanje);
int unosBroja(void);
int pokreniIzbornik(osoba* head);

int main()
{
    osoba* head = NULL;
    pokreniIzbornik(head);

    return EXIT_SUCCESS;
}

int pokreniIzbornik(osoba* head)
{
    osoba* zaBrisanje = NULL;
    
    int opcija = 4, pod_opcija = 2;
    char c = 'n';
    char prezime[MAX];
    
    while(1)
    {
        printf("----OPCIJE:----\n    1 - dodaj element\n    2 - briši element po prezimenu\n    3 - izlaz i ispis\n");
        opcija = unosBroja();

        switch (opcija)
        {
            case 1:
                printf("--Unos podataka--\n  OPCIJE:\n       0 - dodaj na pocetak\n       1 - dodaj na kraj\n");
                pod_opcija = unosBroja();
                if (pod_opcija == -1)
                {
                    break;
                }
                dodajElement(&head, pod_opcija);
                break;
            
            case 2:
                printf("--Prezime osobe koju želite izbrisati: ");
                scanf(" %s", prezime);
                zaBrisanje = traziPrezime(head, prezime);
                if(zaBrisanje)
                {
                    printf("    Jeste li sigurni? d/n:");
                    scanf(" %c", &c);
                    if (c == 'd')
                        izbrisiElement(head, zaBrisanje);
                }
                else
                {
                    printf("Nema osobe s tim prezimenom\n");
                }

                break;

            case 3:
                ispis(head);
                return EXIT_SUCCESS;
                break;
            
            default:
                printf("Nevaljani unos!\n");
                return EXIT_SUCCESS;
                break;
        }
    }

    return EXIT_SUCCESS;
}

int unosBroja(void)
{
    int c, broj;
    c = scanf("%d", &broj);

    if (c != 1)
    {
        printf("Nije ispravan broj!\n"); 
        return -1;
    }

    //hvata enter
    c = getchar();

    return broj;
}

int izbrisiElement(osoba* head, osoba* elementZaBrisanje)
{
    osoba* tmp = head;

    while (tmp->next != elementZaBrisanje)
    {
        tmp = tmp->next;
    }
    
    tmp->next = elementZaBrisanje->next;
    free(elementZaBrisanje);
    printf("Element izbrisan!\n");

    return EXIT_SUCCESS;
}

osoba* adresaZadnjeg(osoba* head)
{
    osoba* tmp = head;

    while (tmp->next)
    {
        tmp = tmp->next;
    }
    return tmp;
}

osoba* traziPrezime(osoba* head, char* prezime)
{
    osoba* tmp = head;

    while(tmp)
    {
        if (strcmp(tmp->prezime, prezime) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }

    //ako ne pronađe
    return NULL;
}

int dodajElement(osoba** head, int opcija)
{
    osoba* novaOsoba = NULL;
    osoba* tmp = NULL;

    novaOsoba = (osoba*)malloc(sizeof(osoba));
    if(!novaOsoba)
    {
        perror("Greška alokacije! ");
        return -1;
    }

    if(unosPodataka(novaOsoba) == EXIT_FAILURE)
    {
        perror("Greška kod unosa");
        return -1;
    }

    switch(opcija)
    {
        //dodavanje na pocetak
        case 0:
            novaOsoba->next = *head;
            *head = novaOsoba;
            break;
        //dodavanje na kraj
        case 1:
            tmp = adresaZadnjeg(*head);
            novaOsoba->next = NULL;
            tmp->next = novaOsoba;
            break;
    }

    return 0;
}

int unosPodataka(osoba* novaOsoba)
{   
    //bufferi
    char big_buffer[MAX];
    char small_buff[SMALL_BUFFER] = "";
    int tmpGodina;
    //--unos podataka

    //unos imena i error checking
    printf("Ime(na): ");
    if(overEngineeredUnos(big_buffer, small_buff, novaOsoba->ime) == EXIT_FAILURE)
    {
        perror("Greška u unosu imena");
        return -1;
    }

    //unos prezimena
    printf("Prezime(na): ");
    if(overEngineeredUnos(big_buffer, small_buff, novaOsoba->prezime) == EXIT_FAILURE)
    {
        perror("Greška u unosu prezimena! ");
        return -1;
    }
     
    //unos godine rođenja
    printf("Godina rođenja: ");
    tmpGodina = unosBroja();
    if (tmpGodina == -1)
    {
        printf("Nevaljani unos godine!\n ");
        return -1;
    }
    
    novaOsoba->godina = tmpGodina;

    return EXIT_SUCCESS;
}

int overEngineeredUnos(char* big_buffer, char* small_buff, char* vrijednost)
{
    fgets(big_buffer, MAX, stdin);
    sscanf(big_buffer, " %s %s", vrijednost, small_buff);

    if(strlen(small_buff) > 0)
        strcat(strcat(vrijednost," "), small_buff);

    return EXIT_SUCCESS;
}

int ispis(osoba* head)
{
    osoba* tmp = head;
    while(tmp)
    {
        printf("%s %s %d \n", tmp->ime, tmp->prezime, tmp->godina);
        tmp = tmp->next;
    }

    return EXIT_SUCCESS;
}