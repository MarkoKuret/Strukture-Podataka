#ifndef stog_H
#define stog_H

#include "declarations.h"

stogP AlocirajStogElement()
{
    stogP noviElement = NULL;

    noviElement = (stogElement*)malloc(33);//sizeof(stogElement)
    if(NULL == noviElement)
    {
        perror("Greška alokacije elementa stoga! ");
        return NULL;
    }

    noviElement->next = NULL;
    noviElement->tip = DEFAULT;

    return noviElement;
}

int dodajStogElement(stogP head, tipVarijable tip)
{
    stogP noviElement = NULL;

    noviElement = AlocirajStogElement();
    if(NULL == noviElement)
        return EXIT_FAILURE;

    noviElement->next = head->next;
    head->next = noviElement;

    noviElement->tip = tip;

    return EXIT_SUCCESS;
}

tipVarijable pop(stogP head)
{
    stogP stogElement = NULL;
    tipVarijable tip = DEFAULT;

    stogElement = head->next;
    if(NULL == stogElement)
    {
        printf("Prazan stog!\n");
        return EXIT_SUCCESS;
    }

    head->next = stogElement->next;

    tip = stogElement->tip;

    free(stogElement);

    return tip;
}

int brisanjeStoga(stogP head)
{
    stogP zaBrisanje = head->next;
    stogP sljedeci = NULL;

    while(NULL != zaBrisanje)
    {
        sljedeci = zaBrisanje->next;
        free(zaBrisanje);
        zaBrisanje = sljedeci;
    }
    
    head->next = NULL;

    return EXIT_SUCCESS;
}

int oslobodiStogElement(stogP head, int pozicija)
{
    int counter = 0;
    stogP tmp = head;
    stogP prosli = NULL;

    while(counter != pozicija && tmp != NULL)
    {
        counter++;
        prosli = tmp;
        tmp = tmp->next;
    }

    prosli->next = tmp->next;
    free(tmp);

    return EXIT_SUCCESS;
}
 
int procitajStog(stogP head, int pozicija)
{
    stogP tmp = head;
    tipVarijable tip = DEFAULT;
    int i = 0;

    for (i = 0; i < pozicija; i++)
        tmp = tmp->next;

    if(NULL == tmp)
    {
        printf("Prazan stog!\n");
        return EXIT_SUCCESS;
    }

    tip = tmp->tip;

    return tip;
}
#endif 