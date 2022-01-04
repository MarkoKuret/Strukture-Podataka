#include <stdio.h>
#include <stdlib.h>

#define MAX (100)


//struktura student (stud)
typedef struct student
{
    char ime[MAX];
    char prezime[MAX];  
    double bodovi;
} stud;


//prototipi
int brojRedaka (char *imeDat);
stud* ucitajPodatke (char* imeDat, int brojStudenata, double* maxBodovi);
int ispis (int brojStudenata, double maxbodovi, stud* studenti);
double relativniBodovi (double bodovi, double maxBodovi);

int main()
{
    //varijable
    int n = 0;
    double maxBodovi = 0;
    char imeDat[MAX];
    stud *studenti = NULL;

    //korisnik unosi ime datoteke
    printf("Ime datoteke: ");
    scanf(" %s", imeDat);

    // ucitaj broj redaka, odnosno studenata
    n = brojRedaka(imeDat);
    // alociranje memorije, upisivanje u memoriju, pronalaženje najboljih bodova
    studenti = ucitajPodatke (imeDat, n, &maxBodovi);
    //ispis
    ispis (n, maxBodovi, studenti);
    
    return 0;
}

double relativniBodovi (double bodovi, double maxbodovi)
{
    return (bodovi/maxbodovi) * 100;
}

int ispis(int brojStudenata, double maxBodovi, stud* studenti)
{
    int i = 0, sirina = 10;
    double tmp = 0;

    printf("            IME        PREZIME    BODOVI / RELATIVNI:\n\n");

    for (i = 0; i < brojStudenata; i++)
    {
        tmp = studenti[i].bodovi;
        printf("Student[%d]: %-10s %-10s  %lf / %0.1lf\n", i+1, studenti[i].ime, studenti[i].prezime, tmp, relativniBodovi(tmp, maxBodovi));
    }
    puts("");

    return 0;
}

stud* ucitajPodatke(char* imeDat, int brojStudenata, double* maxBodovi)
{
    int i = 0;
    double max = 0, tmp = 0;
    FILE * dat = NULL;
    stud* studenti = NULL;

    dat = fopen(imeDat, "r");
    if (!dat)
    {
        perror("Greška u otvaranju datoteke! ");
        return NULL;
    }

    studenti = malloc(sizeof(stud) * brojStudenata);
    if (!studenti)
    {
        perror("Greška u alociranju memorije! ");
        return NULL;
    }

    for (i = 0; i < brojStudenata; i++)
    {
        fscanf(dat, " %s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        tmp = studenti[i].bodovi;
        if (tmp > max);
        {
            max = tmp;
        }
    }

    fclose(dat);
    
    *maxBodovi = max;

    if (max == 0)
    {
        perror("Pretežak ispit! ");
        return NULL;
    }

    return studenti;
}

int brojRedaka(char* imeDat)
{
    FILE * dat = NULL;
    int counter = 0;

    dat = fopen(imeDat, "r");
    if (!dat)
    {
        perror("Greška u otvaranju datoteke! ");
        return -1;
    }

    while (!feof(dat))
    {
        if (getc(dat) == '\n')
        {
            counter++;
        }
    } 
    
    fclose(dat);
    counter++;

    return counter;
}

