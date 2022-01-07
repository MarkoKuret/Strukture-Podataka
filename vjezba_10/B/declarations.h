#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX 40

struct _city;
typedef struct _city *cityPos;
typedef struct _city
{
    char name[MAX];
    int population;
    cityPos next;
} City;

struct _country;
typedef struct _country *countryPos;
typedef struct _country
{
    char name[MAX];
    countryPos left;
    countryPos right;
    cityPos head;
} Country;

// Country - tree - functions
countryPos countryCreate(char *name);
countryPos countryAdd(countryPos root, countryPos current, char *name);
countryPos countryFindByName(countryPos root, char *name);
int countriesDelete(countryPos root);

// Cities - linked list - functions
cityPos cityCreate(char *name, int population);
int cityAddInOrder(countryPos country, char *name, int population);
int citiesBiggerThan(cityPos head, int min_population);
int citiesDelete(cityPos head);

// File functions
countryPos inputFromFile(countryPos root, char *fileName);

//MENU
int menu(countryPos root);

#endif
