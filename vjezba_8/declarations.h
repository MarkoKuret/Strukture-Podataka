#ifndef DECLARATIONS_H
#define DECLARATIONS_H

typedef enum
{
	INSERT = 1,
	INORDER = 2,
	PREORDER = 3,
	POSTORDER = 4,
	LEVEL_ORDER = 5,
	FIND = 6,
	DELETE = 7,
} inputOption;

struct _node;
typedef struct _node *Position;
typedef struct _node
{
	int data;
	Position right;
	Position left;
} Node;

Position createNode(int data);
Position insertNode(int data, Position root);

int printInOrder(Position root);
int printPreOrder(Position root);
int printPostOrder(Position root);

int getHeight(Position root);
int printCurrentLevel(Position root, int height);
int printLevelOrder(Position root);

Position deleteNode(Position root, int data);
Position findMinimum(Position root);
Position findNode(Position root, int data);

int menu(Position root);

#endif 

