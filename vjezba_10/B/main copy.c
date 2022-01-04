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

    inputFromFile(root, "drzave.txt");

    return EXIT_SUCCESS;
}

//-------COUNTRIES TREE--------//

countryPos countryCreate(char *name)
{
    countryPos newCountry = NULL;
    newCountry = (countryPos)malloc(sizeof(Country));
    if (NULL == newCountry)
    {
        perror("Cannot allocate! ");
        return NULL;
    }

    strcpy(newCountry->name, name);
    newCountry->left = NULL;
    newCountry->right = NULL;

    return newCountry;
}

countryPos countryAdd(countryPos root, char *name)
{
    if (NULL == root)
        return countryCreate(name);

    else if (strcmp(name, root->name) > 0)
        root->left = countryAdd(root->left, name);

    else if (strcmp(name, root->name) < 0)
        root->right = countryAdd(root->right, name);

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

int cityAddInOrder(cityPos head, char *name, int population)
{
    cityPos newCity = NULL;
    cityPos tmp = head;
    newCity = cityCreate(name, population);

    if (NULL == newCity)
        return EXIT_FAILURE;

    while (tmp->next != NULL && newCity->population >= tmp->next->population)
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
int inputFromFile(countryPos root, char *fileName)
{
    FILE *mainFile = NULL;
    FILE *citiesFile = NULL;
    char countryName[MAX] = {"0"};
    char cityName[MAX] = {"0"};
    char citiesFileName[MAX] = {"0"};
    int population = 0;

    mainFile = fopen(fileName, "r");
    if (NULL == mainFile)
    {
        perror("Cannot open file! ");
        return EXIT_FAILURE;
    }

    while (!feof(mainFile))
    {

        fscanf(mainFile, " %s %s", countryName, citiesFileName);
        root = countryAdd(root, countryName);

        citiesFile = fopen(citiesFileName, "r");
        if (NULL == citiesFile)
        {
            perror("No such cities file! ");
            return EXIT_FAILURE;
        }

        while (!feof(citiesFile))
        {
            fscanf(citiesFile, " %s %d", cityName, &population);
            cityAddInOrder(root->head, cityName, population);
        }
        fclose(citiesFile);
    }
    fclose(mainFile);

    return EXIT_SUCCESS;
}