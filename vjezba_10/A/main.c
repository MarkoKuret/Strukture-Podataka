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

    inputFromFile(&head, "files/countries.txt");

    menu(&head);
   
    countriesDelete(&head);

    return EXIT_SUCCESS;
}

//main menu
int menu(countryPos head)
{
    countryPos tmp = NULL;
    char name[MAX] = "0";
    int min_population = 0;

    printf("Type exit for exiting!\nSearch country: ");
    while(scanf(" %s", name) == 1)
    {
        if (strcmp(name, "exit") == 0)
            break;
        printf("Minimal city population: ");
        if (scanf(" %d", &min_population) != 1)
        {
            printf("Invalid input!\n ");
            break;
        }
        tmp = countryFindByName(head, name);
        if (tmp != NULL)
            citiesBiggerThan(tmp->root, min_population);
        else
            printf("No such country!\n");
        
        printf("\nSearch country: ");
    }

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

countryPos countryFindByName(countryPos head, char *name)
{
    countryPos tmp = head;

    while (NULL != tmp)
    {
        if (strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

int countriesDelete(countryPos head)
{

    countryPos current = head->next;
    countryPos tmp = NULL;

    printf("Deleting all allocated data...\n");
    while (current != NULL)
    {
        tmp = current->next;
        citiesDelete(current->root);
        free(current);
        current = tmp;
    }

    head->next = NULL;

    printf("Deleted!\n");

    return EXIT_SUCCESS;
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

int citiesBiggerThan(cityPos root, int min_population)
{
    if (NULL == root)
        return EXIT_SUCCESS;

    if (root->population < min_population)
        citiesBiggerThan(root->right, min_population);
    else
    {
        printf("City %s, population = %d\n", root->name, root->population);
        citiesBiggerThan(root->right, min_population);
        citiesBiggerThan(root->left, min_population);
    }

    return EXIT_SUCCESS;
}

int citiesDelete(cityPos root)
{
    if (NULL == root)
        return EXIT_SUCCESS;

    citiesDelete(root->left);
    citiesDelete(root->right);
    free(root);

    return EXIT_SUCCESS;
}

//--------FILE--------//
int inputFromFile(countryPos head, char *fileName)
{
    FILE *mainFile = NULL;
    FILE *citiesFile = NULL;
    char countryName[MAX] = {"0"};
    char cityName[MAX] = {"0"};
    char citiesFileName[MAX] = "0";
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
        if (NULL == citiesFile)
        {
            perror("No such cities file! ");
            return EXIT_FAILURE;
        }
        while (!feof(citiesFile))
        {
            fscanf(citiesFile, " %s %d", cityName, &population);
            countryCurrent->root = cityAdd(countryCurrent->root, cityName, population);
        }
        fclose(citiesFile);
    }
    fclose(mainFile);

    return EXIT_SUCCESS;
}