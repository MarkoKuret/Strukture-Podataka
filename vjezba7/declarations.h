#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_STRING 44

typedef enum {
    CONTINUE = 2,
    EXIT = 3,
} returnType;

struct _dir;
typedef struct _dir* Position;
typedef struct _dir
{
	char name[MAX_STRING];
	Position sibling;
	Position child;
} Directory;

struct _stackElement;
typedef struct _stackElement* StackP;
typedef struct _stackElement
{
	Position parentDir;
	StackP next;
} StackElement;

Position directoryCreate(char* name);
Position directoryInsertSorted(Position current, Position newDirectory);
int directoryInsert(Position current, StackP stackHead, char* name);
Position directoryFindByName(Position current, char* name);

StackP stackElementCreate();
int stackElementInsert(StackP head, Position parent);
Position pop(StackP head);

int navigation(Position parent, StackP stackHead);
int printChildren(Position current);
int printPath(Position current, StackP stackHead);


#endif 