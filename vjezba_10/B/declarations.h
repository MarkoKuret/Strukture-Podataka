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

// Cities - linked list - functions
cityPos cityCreate(char *name, int population);
int cityAddInOrder(countryPos country, char *name, int population);

// File functions
countryPos inputFromFile(countryPos root, char *fileName);

#endif
