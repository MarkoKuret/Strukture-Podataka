#ifndef DECLARATIONS_H
#define DECLARATIONS_H

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

#endif 