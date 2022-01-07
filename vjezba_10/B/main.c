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

    root = inputFromFile(root, "files/countries.txt");

    menu(root);
    countriesDelete(root);
    printf("Deleted data!\n");

    return EXIT_SUCCESS;
}

//MENU
int menu(countryPos root)
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
        tmp = countryFindByName(root, name);
        if (tmp != NULL)
            citiesBiggerThan(tmp->head, min_population);
        else
            printf("No such country!\n");
        
        printf("\nSearch country: ");
    }

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

    else if (strcmp(root->name, name) < 0)
        root->left = countryAdd(root->left, current, name);

    else if (strcmp(root->name, name) > 0)
        root->right = countryAdd(root->right, current, name);

    return root;
}

countryPos countryFindByName(countryPos root, char *name)
{
    if (NULL == root)
        return NULL;

    if (strcmp(root->name, name) == 0)
        return root;

    if (strcmp(root->name, name) < 0)
        root = countryFindByName(root->left, name);
    else
        root = countryFindByName(root->right, name);

    return root;
}

int countriesDelete(countryPos root)
{
    if (NULL == root)
        return EXIT_SUCCESS;

    countriesDelete(root->left);
    countriesDelete(root->right);

    citiesDelete(root->head);
    free(root);

    return EXIT_SUCCESS;
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
     
    while (tmp->next != NULL && newCity->population >= tmp->next->population)
    {
        if (newCity->population == tmp->next->population)
        {
            if (strcmp(newCity->name, tmp->next->name) > 0)
                tmp = tmp->next;
            break;
        }
        tmp = tmp->next;
    }

    newCity->next = tmp->next;
    tmp->next = newCity;

    return EXIT_SUCCESS;
}

int citiesBiggerThan(cityPos head, int min_population)
{
    cityPos tmp = head->next;
    
    if(NULL == tmp)
    {
        printf("Empty cities list!\n");
        return EXIT_SUCCESS;
    }

    while(tmp != NULL && tmp->population < min_population)
        tmp = tmp->next;

    puts("");
    while(NULL != tmp)
    {
        printf("%s, population %d\n", tmp->name, tmp->population);
        tmp = tmp->next;
    }
    
    return EXIT_SUCCESS;
}

int citiesDelete(cityPos head)
{

    cityPos current = head->next;
    cityPos tmp = NULL;

    while (current != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }

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