#ifndef GENERIC_LIST
#define GENERIC_LIST

#include "declarations.h"
#include "stog.h"

position stvoriElement(size_t velicinaVarijable)
{
    position noviNode = NULL;

    noviNode = (position)malloc((sizeof(Node) + velicinaVarijable));

    if(NULL == noviNode)
    {
        perror("Greška alokacije! ");
        return NULL;
    }
    noviNode->next = NULL;

    return noviNode;
}

int unosPodataka(position noviNode, void* varijabla, size_t velicinaVarijable)
{
    memcpy((noviNode + sizeof(Node)), varijabla, velicinaVarijable);
    return EXIT_SUCCESS;
}

int dodajNaPocetak(position head, stogP stogHead, tipVarijable tip, void* varijabla, size_t velicinaVarijable)
{
    position noviNode = NULL;

    noviNode = stvoriElement(velicinaVarijable);
    if(NULL == noviNode)
        return EXIT_FAILURE;

    dodajStogElement(stogHead, tip);

    unosPodataka(noviNode, varijabla, velicinaVarijable);

    noviNode->next = head->next;
    head->next = noviNode;

    return EXIT_SUCCESS;
}

int ispisListe(position head, stogP stogHead)
{
    position tmp = NULL;
    tipVarijable tip = DEFAULT;
    int counter = 0;

    if(head->next != NULL)
        tmp = head->next;
    else
    	printf("Prazna lista!\n");

    printf("\n--ISPIS:--\n");

    while(tmp != NULL)
    {
        counter++;
        tip = procitajStog(stogHead, counter);
        ispisElementa(tmp, tip);
        tmp = tmp->next;   
        
    }
    puts("");

    return EXIT_SUCCESS;
}

int ispisElementa(position element, tipVarijable tip)
{
    switch(tip)
    {
        case INT:
            printf("Int: %d\n", *((int*)(element + sizeof(Node))));
            break;

        case DOUBLE:
            printf("Double: %lf\n", *((double*)(element + sizeof(Node))));
            break;

        case FLOAT:
            printf("Float: %f\n", *((float*)(element + sizeof(Node))));
            break;

        case CHAR:
            printf("Char: %c\n", *((char*)(element + sizeof(Node))));
            break;

        case STRING:
            printf("String: %s\n", ((char*)(element + sizeof(Node))));
            break;

        case DEFAULT:
        default:
            printf("Adresa podatka: %p", (element + sizeof(Node)));
    }
    return EXIT_SUCCESS;
}

int brisanjeListe(position head, stogP stogHead)
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
    
    brisanjeStoga(stogHead);

    return EXIT_SUCCESS;
}

int brisanjeElementa(position head, stogP stogHead, void* varijabla)
{
    tipVarijable tip = DEFAULT;
    int counter = 0;
    position tmp = head;
    position prosli = NULL;

    while(tmp != NULL)
    {
        if(*((int*)(tmp + sizeof(Node))) == *(int*)varijabla)
        {
            prosli->next = tmp->next;
            printf("Brisem element na lokaciji %p...\n", tmp);
            free(tmp);
            oslobodiStogElement(stogHead, counter);
            printf("Element izbrisan!\n");  
           
            return EXIT_SUCCESS;
        }
        counter++;
        prosli = tmp;
        tmp = tmp->next;
    }

    printf("Element ne postoji! ");

    return EXIT_SUCCESS;
}

#endif 