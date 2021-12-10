/*----DODATNI ZADATAK take2----
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


//samo za test
typedef struct _struktura {
    char string[MAX_STRING];
} Struktura;

position stvoriElement(int velicinaVarijable);
int unosPodataka(position noviNode, int velicinaVarijable, void* varijabla);
int dodajNaPocetak(position head, int velicinaVarijable, void* varijabla);
int ispis(position head);
int brisanje(position head);

//----MAIN----
int main()
{
    Node head = {.next = NULL};
    position headPtr = &head;

    //testni podaci 
    Struktura test = {.string = "test"};
    int i = 5;
    int m = 10;
    int j = 342;
    int c = 'a';

    dodajNaPocetak(headPtr, sizeof(int), &i);
    dodajNaPocetak(headPtr, sizeof(int), &m);
    dodajNaPocetak(headPtr, sizeof(int), &j);
    dodajNaPocetak(headPtr, sizeof(char), &c);
    dodajNaPocetak(headPtr, sizeof(test), &test);

    ispis(headPtr);
    brisanje(headPtr);


    return EXIT_SUCCESS;
}

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
    *((noviNode + sizeof(Node))) = *((position)varijabla);

    return EXIT_SUCCESS;
}

int dodajNaPocetak(position head, int velicinaVarijable, void* varijabla)
{
    position noviNode = NULL;

    noviNode = stvoriElement(velicinaVarijable);
    if(noviNode == NULL)
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
    char string[MAX_STRING];

    if(head->next != NULL)
        tmp = head->next;

    printf("\n--ISPIS:--\n");

    while(tmp)
    {
        brojac++;
        printf("\n====ELEMENT %d====\n", brojac);
        
        //hard codano za testne podatke, mogu popravit ako treba
        if(brojac == 1)
            printf("string: %s\n", ((Struktura*)(tmp + sizeof(Node)))->string);

        else if(brojac == 2)
            printf("Char: %c\n", *((char*)(tmp + sizeof(Node))));

        else
            printf("Int: %d\n", *((int*)(tmp + sizeof(Node))));
         
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
