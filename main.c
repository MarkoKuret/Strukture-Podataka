/*----DODATNI ZADATAK----
Strukture podataka FESB
Marko Kuret 2021/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 20

struct _Node;
typedef struct _Node* position;
typedef struct _Node {
    position next;
} Node;

typedef enum {
    INT = 1,
    STRING = 2,
    DOUBLE = 3,
    FLOAT = 4
} tipVarijable;

position stvoriElement(tipVarijable tip);
int unosPodataka(position noviNode, tipVarijable tip, void* varijabla);
int dodajNaPocetak(position head, tipVarijable tip, void* varijabla);
int ispis(position head);
int izbornik(position head);

//----MAIN----
int main()
{
    Node head = {.next = NULL};

    position headPtr = &head;

    izbornik(headPtr);
    ispis(headPtr);

   //dodat brisanje

    return EXIT_SUCCESS;
}

int izbornik(position head)
{
    tipVarijable tip = 0;
    int opcija = 0;
    int i = 0;
    char s[MAX_STRING];
    double d = 0.0;
    float f = 0.0;

    while(1)
    {
        printf("\nTip podatka za unos: 1 - int, 2 - string/char, 3 - double, 4 - float\n\t5 - ispis i izlaz\n");
        scanf(" %d", &opcija);
        tip = opcija;
        switch (opcija)
        {
            printf("Vrijednost: ");
            case INT:
                scanf(" %d", &i);
                dodajNaPocetak(head, tip, &i);
                break;
            case STRING:
                scanf(" %s", s);
                dodajNaPocetak(head, tip, &s);
                break;
            case DOUBLE:
                scanf(" %lf", &d);
                dodajNaPocetak(head, tip, &d);
                break;
            case FLOAT:
                scanf(" %f", &f);
                dodajNaPocetak(head, tip, &f);
                break;
            case 5:
                return EXIT_SUCCESS;
            default:
                return EXIT_SUCCESS;
        }  
    }
    return EXIT_SUCCESS;
}

position stvoriElement(tipVarijable tip)
{
    position noviNode = NULL;
    int size = 0;

    switch (tip)
    {
        case INT:
            size = sizeof(int);
            break;
        case STRING:
            size = sizeof(char)*MAX_STRING;
            break;
        case DOUBLE:
            size = sizeof(double);
            break;
        case FLOAT:
            size = sizeof(float);
            break;

    }

    noviNode = (position)malloc(sizeof(Node) + size + 1);

    if(!noviNode)
    {
        perror("Greška alokacije! ");
        return NULL;
    }
    noviNode->next = NULL;

    return noviNode;
}

int unosPodataka(position noviNode, tipVarijable tip, void* varijabla)
{   
    switch(tip)
    {
        case INT:
            *((int*)(noviNode + sizeof(Node))) = *((int*)varijabla);
            *((char*)(noviNode + sizeof(Node) + 1)) = 'i';
            break;

        case STRING:
            strcpy(((char*)(noviNode + sizeof(Node))), (char*)varijabla);
            *((char*)(noviNode + sizeof(Node) + 1)) = 's';
            break;

        case DOUBLE:
            *((double*)(noviNode + sizeof(Node))) = *((double*)varijabla);
            *((char*)(noviNode + sizeof(Node) + 1)) = 'd';
            break;

        case FLOAT:
            *((float*)(noviNode + sizeof(Node))) = *((float*)varijabla); 
            *((char*)(noviNode + sizeof(Node) + 1)) = 'f';  
            break;

    }
    return EXIT_SUCCESS;
}

int dodajNaPocetak(position head, tipVarijable tip, void* varijabla)
{
    position noviNode = NULL;

    noviNode = stvoriElement(tip);
    if(noviNode == NULL)
        return EXIT_FAILURE;

    unosPodataka(noviNode, tip, varijabla);

    noviNode->next = head->next;
    head->next = noviNode;

    return EXIT_SUCCESS;
}

int ispis(position head)
{
    position tmp = NULL;
    int brojac = 1;

    if(head->next != NULL)
        tmp = head->next;

    printf("\n--ISPIS:--\n");

    while(tmp)
    {
        printf("\n====ELEMENT %d====\n", brojac);
        switch(*((char*)(tmp + sizeof(Node) + 1)))
        {
            case 'i':
                printf("Int: %d\n", *((int*)(tmp + sizeof(Node))));
                break;

            case 's':
                printf("String: %s\n", ((char*)(tmp + sizeof(Node))));
                break;

            case 'd':
                printf("Double: %lf\n", *((double*)(tmp + sizeof(Node))));
                break;

            case 'f':
                printf("Float: %f\n", *((float*)(tmp + sizeof(Node))));
                break;
        }
        tmp = tmp->next;
        brojac++;
    }

    puts("");

    return EXIT_SUCCESS;
}
