/*  STRUKTURE PODATAKA
    ZADATAK 10 - pod A
drave lista, gradovi stabla*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

int main()
{
    countryPos root = NULL;

    root = inputFromFile(root, "drzave.txt");

    return EXIT_SUCCESS;
}

//-------COUNTRIES TREE--------//

countryPos countryCreate(char *name)
{
    countryPos newCountry = NULL;
    cityPos head = NULL;

    newCountry = (countryPos)malloc(sizeof(Country));
    if (NULL == newCountry)
    {
        perror("Cannot allocate! ");
        return NULL;
    }

    head = (cityPos)malloc(sizeof(City));
    if (NULL == head)
    {
        perror("Cannot allocate! ");
        return NULL;
    }

    newCountry->head = head;

    strcpy(newCountry->name, name);
    newCountry->left = NULL;
    newCountry->right = NULL;

    return newCountry;
}

countryPos countryAdd(countryPos root, countryPos current, char *name)
{
    if (NULL == root)
        return current;

    else if (strcmp(name, root->name) > 0)
        root->left = countryAdd(root->left, current, name);

    else if (strcmp(name, root->name) < 0)
        root->right = countryAdd(root->right, current, name);

    return root;
}

//-------CITIES SORTED LINKED LIST--------//

cityPos cityCreate(char *name, int population)
{
    cityPos newCity = NULL;
    newCity = (cityPos)malloc(sizeof(City));
    if (NULL == newCity)
    {
        perror("Cannot allocate! ");
        return NULL;
    }

    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->next = NULL;

    return newCity;
}

int cityAddInOrder(countryPos country, char *name, int population)
{
    cityPos newCity = NULL;
    cityPos tmp = country->head;
    newCity = cityCreate(name, population);

    if (NULL == newCity)
        return EXIT_FAILURE;
     
    while (tmp->next != NULL && newCity->population <= tmp->next->population)
    {
        if (newCity->population == tmp->next->population)
        {
            if (strcmp(newCity->name, tmp->next->name) > 0)
                tmp = tmp->next;
            else
                break;
        }
        tmp = tmp->next;
    }

    newCity->next = tmp->next;
    tmp->next = newCity;

    return EXIT_SUCCESS;
}

//--------FILE--------//
countryPos inputFromFile(countryPos root, char *fileName)
{
    FILE *mainFile = NULL;
    FILE *citiesFile = NULL;
    char countryName[MAX] = {"0"};
    char cityName[MAX] = {"0"};
    char citiesFileName[MAX] = {"0"};
    int population = 0;
    countryPos currentCountry = NULL;

    mainFile = fopen(fileName, "r");
    if (NULL == mainFile)
    {
        perror("Cannot open file! ");
        return NULL;
    }

    while (!feof(mainFile))
    {

        fscanf(mainFile, " %s %s", countryName, citiesFileName);
        currentCountry = countryCreate(countryName);
        root = countryAdd(root, currentCountry, countryName);

        citiesFile = fopen(citiesFileName, "r");
        if (NULL == citiesFile)
        {
            perror("No such cities file! ");
            return NULL;
        }

        while (!feof(citiesFile))
        {
            fscanf(citiesFile, " %s %d", cityName, &population);
            cityAddInOrder(currentCountry, cityName, population);
        }
        fclose(citiesFile);
    }
    fclose(mainFile);

    return root;
}

//dodat provjere u input file i brisanje, napravit bez nepotrebnog malloca praznog heada