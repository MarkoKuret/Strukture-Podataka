/*----DODATNI ZADATAK----
Strukture podataka FESB
    Marko Kuret */

#include "genericList.h"

int main()
{
    Node head = {.next = NULL};
    position headPtr = &head;

    Struktura test = {.string = "test"};
    int i = 5;
    int m = 10;
    int j = 342;
    int c = 'a';

    dodajNaPocetak(headPtr, sizeof(int), &i);
    dodajNaPocetak(headPtr, sizeof(int), &m);
    dodajNaPocetak(headPtr, sizeof(int), &j);
    dodajNaPocetak(headPtr, sizeof(char), &c);
    dodajNaPocetak(headPtr, sizeof(test.string), &test);

    ispis(headPtr);
    brisanje(headPtr);


    return EXIT_SUCCESS;
}