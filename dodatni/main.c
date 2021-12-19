/*----DODATNI ZADATAK----
Strukture podataka FESB
    Marko Kuret */



#include "genericList.h"

int main()
{
    Node head = {.next = NULL};
    stogElement stogHead = {.next = NULL, .tip = DEFAULT};
    position headPtr = &head;
    stogP stogPtr = &stogHead;

    tipVarijable tip;

    Struktura test = {.string = "pet"};
    int i = 1;
    int j = 2;
    int l = 3;
    char c = '4';
    
    double d = 3.14;
 
    dodajNaPocetak(headPtr, stogPtr, STRING, &test, sizeof(test));
    dodajNaPocetak(headPtr, stogPtr, CHAR, &c, sizeof(c));
    dodajNaPocetak(headPtr, stogPtr, INT, &l, sizeof(l));

    dodajNaPocetak(headPtr, stogPtr, INT, &j, sizeof(j));
    dodajNaPocetak(headPtr, stogPtr, INT, &i, sizeof(i));

    ispisListe(headPtr, stogPtr);

    brisanjeElementa(headPtr, stogPtr, &j);
    dodajNaPocetak(headPtr, stogPtr, DOUBLE, &d, sizeof(d));
    
    ispisListe(headPtr, stogPtr);

    brisanjeElementa(headPtr, stogPtr, &i);

    ispisListe(headPtr, stogPtr);
    

    brisanjeListe(headPtr, stogPtr);

    return EXIT_SUCCESS;
}