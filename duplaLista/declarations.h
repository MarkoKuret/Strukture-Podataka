#ifndef DECLARATIONS_H
#define DECLARATIONS_H

struct _Node;
typedef struct _Node* Position;

typedef struct _Node
{
	int number;
	Position next;
	Position prev;
} Node;


Position makeNode();
int prepend(Position head);
Position findLast(Position head);
int append(Position lastNode);
int print(Position head);
int freeList(Position head);
int selectElement(Position head);

#endif 