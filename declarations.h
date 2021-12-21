#ifndef DECLARATIONS_H
#define DECLARATIONS_H

struct _node;
typedef struct _node* Position;
typedef struct _node
{
	int data;
	Position right;
	Position left;
} Node;

struct _stackElement;
typedef struct _stackElement* StackP;
typedef struct _stackElement
{
	int data;
	StackP next;
} StackElement;

Position createNode(int data);
Position insertNode(int data, Position root);
int replace(Position root);
int randomNumber();

int printToStack(Position root, StackP stackHead);
int fileInput(char* fileName, StackP stackHead);

StackP stackElementCreate();
int stackElementInsert(StackP head, int data);
int pop(StackP head);

#endif 

