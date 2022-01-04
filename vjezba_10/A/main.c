/*  STRUKTURE PODATAKA
    ZADATAK 10 - pod A
drave lista, gradovi stabla*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

int main()
{
    Country head = {.name = "", .next = NULL};
    countryPos headPtr = &head;

   /* countryAddInOrder(headPtr, "Argentina");
    countryAddInOrder(headPtr, "Brazil");
    countryAddInOrder(headPtr, "Croatia");

    root = cityAdd(root, "Split", 21);
    root = cityAdd(root, "Zagreb", 110);
    root = cityAdd(root, "Dubrovnik", 3);
    root = cityAdd(root, "Borovo", 1);*/

    inputFromFile(headPtr, "drzave.txt");

    printf("test");

    return EXIT_SUCCESS;
}

//-------COUNTRIES SORTED LINKED LIST--------//

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
    newCountry->next = NULL;

    return newCountry;
}

countryPos countryAddInOrder(countryPos head, char *name)
{
    countryPos newCountry = NULL;
    countryPos tmp = head;
    newCountry = countryCreate(name);

    if (NULL == newCountry)
        return NULL;

    while (tmp->next != NULL && strcmp(newCountry->name, tmp->next->name) > 0)
        tmp = tmp->next;

    newCountry->next = tmp->next;
    tmp->next = newCountry;

    return newCountry;
}

//-------CITIES TREE--------//

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
    newCity->left = NULL;
    newCity->right = NULL;

    return newCity;
}

cityPos cityAdd(cityPos root, char *name, int population)
{
    if (NULL == root)
        return cityCreate(name, population);

    else if (population < root->population)
        root->left = cityAdd(root->left, name, population);

    else if (population > root->population)
        root->right = cityAdd(root->right, name, population);

    else if (strcmp(name, root->name) > 0)
        root->left = cityAdd(root->left, name, population);

    else if (strcmp(name, root->name) < 0)
        root->right = cityAdd(root->right, name, population);

    return root;
}

//--------FILE--------//
int inputFromFile(countryPos head, char *fileName)
{
    FILE *mainFile = NULL;
    FILE *citiesFile = NULL;
    char *countryName = "";
    char *cityName = "";
    char *citiesFileName = "";
    int population = 0;
    countryPos countryCurrent = NULL;

    mainFile = fopen(fileName, "r");
    if (NULL == mainFile)
    {
        perror("Cannot open file! ");
        return EXIT_FAILURE;
    }

    while (!feof(mainFile))
    {
        fscanf(mainFile, " %s %s", countryName, citiesFileName);
        countryCurrent = countryAddInOrder(head, countryName);

        citiesFile = fopen(citiesFileName, "r");
        if(NULL == citiesFile)
        {
            perror("No such cities file! ");
            return EXIT_FAILURE;
        }

        while(!feof(citiesFile))
        {
            fscanf(citiesFile, " %s %d", cityName, &population);
            countryCurrent->root = cityAdd(countryCurrent->root, cityName, population);
        }
        fclose(citiesFile);
    }
    fclose(mainFile);

    return EXIT_SUCCESS;
}