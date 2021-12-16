#include "declarations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

position stvoriElement(int velicinaVarijable)
{
    position noviNode = NULL;

    noviNode = (position)malloc(sizeof(Node) + velicinaVarijable);

    if(!noviNode)
    {
        perror("Greška alokacije! ");
        return NULL;
    }
    noviNode->next = NULL;

    return noviNode;
}

int unosPodataka(position noviNode, int velicinaVarijable, void* varijabla)
{   
    memcpy((noviNode + sizeof(Node)), varijabla, sizeof(velicinaVarijable));

    return EXIT_SUCCESS;
}

int dodajNaPocetak(position head, int velicinaVarijable, void* varijabla)
{
    position noviNode = NULL;

    noviNode = stvoriElement(velicinaVarijable);
    if(NULL == noviNode)
        return EXIT_FAILURE;

    unosPodataka(noviNode, velicinaVarijable, varijabla);

    noviNode->next = head->next;
    head->next = noviNode;

    return EXIT_SUCCESS;
}

int ispis(position head)
{
    position tmp = NULL;
    int brojac = 0;

    if(head->next != NULL)
        tmp = head->next;
    else
    	printf("Prazna lista!\n");

    printf("\n--ISPIS:--\n");

    while(tmp)
    {
        printf("Lokacija podatka: %p\n", (tmp + sizeof(Node)));
        tmp = tmp->next;   
    }

    puts("");

    return EXIT_SUCCESS;
}

int brisanje(position head)
{
    position zaBrisanje = head->next;
    position sljedeci = NULL;

    while(NULL != zaBrisanje)
    {
        sljedeci = zaBrisanje->next;
        free(zaBrisanje);
        zaBrisanje = sljedeci;
    }
    
    head->next = NULL;

    return EXIT_SUCCESS;
}
