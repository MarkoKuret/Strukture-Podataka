#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50



typedef struct poli* position;

typedef struct poli
{
    int faktor;
    int potencija;
    position next;
} polinom;

int unosStringa(char* imeDat);
position stvoriElement();
int dodajSortirano(position head, int faktor, int potencija);
int citajDatoteku(char *imeDat, position head1, position head2);

int zbrojiPolinome(position head1, position head2, position headRjesenje);
int mnoziPolinome(position head1, position head2, position headRjesenje);
int ispis(position first, char* imePolinoma);
int ispisiSvaRjesenja(position ptr1, position ptr2, position ptr3);

int pokreniIzbornik(position ptr1, position ptr2, position ptr3);

int izbrisi(position head);

int main()
{
    polinom head1 = {.faktor = 0, .potencija = 0, .next = NULL};
    polinom head2 = {.faktor = 0, .potencija = 0, .next = NULL};
    polinom headRjesenje= {.faktor = 0, .potencija = 0, .next = NULL};
   
    position ptr1 = &head1;
    position ptr2 = &head2;
    position ptr3 = &headRjesenje;
    
    printf("\nUnesite ime datoteke koja sadrži polinome, ili exit za izlaz\n");

    pokreniIzbornik(ptr1, ptr2, ptr3);

    //oslobadanje memorije
    izbrisi(ptr1);
    izbrisi(ptr2);
    izbrisi(ptr3);

    return EXIT_SUCCESS;
}

int unosStringa(char* imeDat)
{
    int n = 0;

    printf("Ime datoteke: ");
    
    fgets(imeDat, MAX, stdin);
    n = sscanf(imeDat, " %s", imeDat);

    if (n != 1)
    {
        perror("Nevaljan unos");
        return EXIT_FAILURE;
    }

    if(strcmp(imeDat, "exit") == 0)
    {
        return 2;
    }

    strcat(imeDat, ".txt");

    return EXIT_SUCCESS;
}

//alocira memoriju za novi element
position stvoriElement()
{
    position noviElement = NULL;

    noviElement = (position)malloc(sizeof(polinom));
    if (!noviElement)
    {
        perror("Greska u alokaciji memorije!");
        return NULL;
    }

    return noviElement;
}

//dodaje sortirano u listu (descending), iste iste potencije se samo zbrajaju fakori
//zove fju stvoriElement
int dodajSortirano(position head, int faktor, int potencija)
{
    position tmp = head;
    position noviElement = NULL;

    while (tmp->next && tmp->next->potencija > potencija){
        tmp = tmp->next;}
    
    if (tmp->next && tmp->next->potencija == potencija)
    {
        tmp->next->faktor = tmp->next->faktor + faktor;
        return EXIT_SUCCESS;
    }

    noviElement = stvoriElement();
    noviElement->faktor = faktor;
    noviElement->potencija = potencija;

    noviElement->next = tmp->next;
    tmp->next = noviElement;

    return EXIT_SUCCESS;
}

//cita datoteku imeDat, i unosi dva polinoma tako da zove fju dodajSortirano
int citajDatoteku(char *imeDat, position head1, position head2)
{
    char buffer[MAX];
    char* newBuffer;

    int faktor = 0;
    int potencija = 0;
    int n = 0;
    int i = 0;
    int provjera = 0;
    
    FILE * fp = NULL;

    fp = fopen(imeDat, "r");
    if(!fp)
    {
        perror("Greška u otvaranju datoteke");
        return EXIT_FAILURE;
    }

    //moze ici i while loop, ali posto znamo da ce bit samo dva polinoma ovako je brze
    //plus sto nije optimalno koristiti feof za loop
    for(i = 0; i < 2; i++)
    {
        fgets(buffer, MAX, fp);
        newBuffer = buffer;
        while (strlen(newBuffer) > 0)
        {
            provjera = sscanf(newBuffer, " %d %d %n", &faktor, &potencija, &n);
            if (provjera != 2)
            {
                printf("Nevaljan format datoteke!");
                return EXIT_FAILURE;
            }
            newBuffer += n;
            if (i == 0)
                dodajSortirano(head1, faktor, potencija);
            else
                dodajSortirano(head2, faktor, potencija);               
        }
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

//zbraja polinome head1 i head2, i zapisuje u headRjesenje (O(n))
int zbrojiPolinome(position head1, position head2, position headRjesenje)
{
    position ptr3 = headRjesenje;
    position i = head1->next;
    position j = head2->next;
 
    while(i && j)
    {
        if(i->potencija == j->potencija)
        {
            dodajSortirano(ptr3, (i->faktor + j->faktor), i->potencija);
            i = i->next;
            j = j->next;
        }
        else if (i->potencija > j->potencija)
        {
            dodajSortirano(ptr3, i->faktor, i->potencija);
            i = i->next;
        }
        else
        {
            dodajSortirano(ptr3, j->faktor, j->potencija);
            j = j->next;
        }
    }

    //ako polinomi nisu iste duzine je potrebna zbrojiti ostatak
    //ovo se moze i s while (i || j), ali ovako je manje provjera
    if (i)
    {
        while(i)
        {
            dodajSortirano(ptr3, i->faktor, i->potencija);
            i = i->next;
        }
    }

    if (j)
    {
        while(j)
        {
            dodajSortirano(ptr3, j->faktor, j->potencija);
            j = j->next;
        }
    }

    return EXIT_SUCCESS;
}

//mnozi polinom head1 i head2, umnozak zapisuje u headRjesenje
int mnoziPolinome(position head1, position head2, position headRjesenje)
{
    position ptr3 = headRjesenje;
    position i = head1->next;
    position j = head2->next;

    while(i)
    {
        while(j)
        {
            dodajSortirano(ptr3, (i->faktor*j->faktor), (i->potencija + j->potencija));
            j = j->next;
        }
        //moramo vratit j na pocetak
        j = head2->next;
        i = i->next;
    }

    return EXIT_SUCCESS;
}

//ispisuje jednu listu
int ispis(position first, char* imePolinoma)
{
    position tmp = first;
    printf("Polinom %-3s = ", imePolinoma);
    while(tmp)
    {
        printf(" %dx^%d", tmp->faktor, tmp->potencija);
        tmp = tmp->next;
    }
    puts("");
    return EXIT_SUCCESS;
}

//ispisuje sve kombinacije s ptr1 i ptr2, a ptr3 je rjesenje
//zove fje ispis, zbrojiPolinome i mnoziPolinome
int ispisiSvaRjesenja(position ptr1, position ptr2, position ptr3)
{
    printf("\n----RJEŠENJE:----\n");
    ispis(ptr1->next, "1");
    ispis(ptr2->next, "2");

    zbrojiPolinome(ptr1, ptr2, ptr3);
    ispis(ptr3->next, "1+2");
    
    // oslobadanje memorije, da koristimo isti head za umnozak
    izbrisi(ptr3);

    mnoziPolinome(ptr1, ptr2, ptr3);
    ispis(ptr3->next, "1*2");
    puts("");
    
    return EXIT_SUCCESS;
}

//pokrece izbornik
//oslanja se na sve gornje funkcije
int pokreniIzbornik(position ptr1, position ptr2, position ptr3)
{
    char imeDat[MAX];

    //izbornik
    while(1)
    {
        switch (unosStringa(imeDat))
        {
            //case 2 je kada korisnik utipka exit
            case 2:
                return EXIT_SUCCESS;

            //kada je unos prihvacen citamo datoteku
            case EXIT_SUCCESS:
                //provjera dali postoji ta datoteka
                if(citajDatoteku(imeDat, ptr1, ptr2) == EXIT_SUCCESS)
                    ispisiSvaRjesenja(ptr1, ptr2, ptr3);
                else
                    printf("\n(bez .txt) ");
                break;

            default:
                return EXIT_FAILURE;
        }
    }
}

//oslobada alociranu memoriju
int izbrisi(position head)
{
    position zaBrisanje = head->next;
    position sljedeci = NULL;

    while(zaBrisanje)
    {
        sljedeci = zaBrisanje->next;
        free(zaBrisanje);
        zaBrisanje = sljedeci;
    }
    
    //mora se vratiti na NULL, da bi se moglo ponovo koristit
    head->next = NULL;

    return EXIT_SUCCESS;
}