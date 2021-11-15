#ifndef DECLARATIONS_H
#define DECLARATIONS_H

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement
{
	double number;
	Position next;
} stackElement;


Position createElement(double number);
int insertAfter(Position reference, Position newElement);
int push(Position head, double number);
int deleteAfter(Position reference);
int pop(double* value, Position head);
int doOperation(Position head, char operation);
int calculatePostfixFromFile(double* result, char* fileName);
int freeList(Position head);
int inputFileName();

#endif 