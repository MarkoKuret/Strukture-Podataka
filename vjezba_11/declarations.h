#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX 40
#define ASCII_OFFSET 48

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
int cityCompare(cityPos first, char *secondName, int secondPopulation);
cityPos cityAdd(cityPos root, char *name, int population);
int citiesBiggerThan(cityPos root, int min_population);
int citiesDelete(cityPos root);

// File functions
int inputFromFile(Country table[], char *fileName);

// extra
int menu(Country table[]);
int hash(char *countryName);

#endif
