#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING 10

typedef enum{
    DEFAULT = -1,
    INT = 0,
    DOUBLE = 1,
    FLOAT = 2,
    CHAR = 3,
    STRING = 4,
}tipVarijable;

struct _Node;
typedef struct _Node* position;
typedef struct _Node {
    position next;
} Node;

//samo za test
typedef struct _struktura {
    char string[MAX_STRING];
} Struktura;

struct _stogElement;
typedef struct _stogElement* stogP;
typedef struct _stogElement
{
    stogP next;
    tipVarijable tip;
} stogElement;

position stvoriElement(size_t velicinaVarijable);
int unosPodataka(position noviNode, void* varijabla, size_t velicinaVarijable);
int dodajNaPocetak(position head, stogP stogHead, tipVarijable tip, void* varijabla, size_t velicinaVarijable);
int ispisListe(position head, stogP stogHead);
int ispisElementa(position element, tipVarijable tip);
int brisanjeListe(position head, stogP stogHead);
int brisanjeElementa(position head, stogP stogHead, void* varijabla);


stogP AlocirajStogElement();
int dodajStogElement(stogP head, tipVarijable tip);
tipVarijable pop(stogP head);
int brisanjeStoga(stogP head);
int oslobodiStogElement(stogP head, int pozicija);
int procitajStog(stogP stogHead, int pozicija);
 
#endif 