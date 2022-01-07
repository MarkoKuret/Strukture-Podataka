#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX 40

struct _city;
typedef struct _city *cityPos;
typedef struct _city
{
    char name[MAX];
    int population;
    cityPos left;
    cityPos right;
} City;

struct _country;
typedef struct _country *countryPos;
typedef struct _country
{
    char name[MAX];
    countryPos next;
    cityPos root;
} Country;

// Country - linked list - functions
countryPos countryCreate(char *name);
countryPos countryAddInOrder(countryPos head, char *name);
countryPos countryFindByName(countryPos head, char *name);
int countriesDelete(countryPos head);

// Cities - tree - functions
cityPos cityCreate(char *name, int population);
cityPos cityAdd(cityPos root, char *name, int population);
int citiesBiggerThan(cityPos root, int min_population);
int citiesDelete(cityPos root);

// File functions
int inputFromFile(countryPos head, char *fileName);

//menu
int menu(countryPos head);

#endif
