#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "declarations.h"

int main()
{
	int i = 0;
	StackElement stackHead = {.data = 0, .next = NULL};
	Position root = NULL;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
		root = insertNode((rand() % 81) + 10, root);

	replace(root);
	printToStack(root, &stackHead);

	fileInput("test.txt", &stackHead);

	return EXIT_SUCCESS;
}

int fileInput(char* fileName, StackP stackHead)
{
	int i = 0;
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL)
		return EXIT_FAILURE;

	for(i = 0; i < 10; i++)
		fprintf(fp, "%d ", pop(stackHead));

	fclose(fp);

	return EXIT_SUCCESS;
}

Position createNode(int data)
{
	Position newNode = (Position)malloc(sizeof(Node));
	if (NULL == newNode)
	{
		printf("Cannot allocate memmory!\n");
		return NULL;
	}

	newNode->data = data;
	newNode->right = NULL;
	newNode->left = NULL;

	return newNode;
}

Position insertNode(int data, Position root)
{
	if (!root)
		return createNode(data);

	else if (data > root->data)
		root->left = insertNode(data, root->left);

	else if (data < root->data)
		root->right = insertNode(data, root->right);

	else if (data == root->data)
		root->left = insertNode(data, root->left);

	return root;
}	

int printToStack(Position root, StackP stackHead)
{
	if (root != NULL)
	{
		printToStack(root->left, stackHead);
		printf("%d\n", root->data);
		stackElementInsert(stackHead, root->data);
		printToStack(root->right, stackHead);
	}
	return EXIT_SUCCESS;
}

int replace(Position root)
{
	int sum = 0;

	if(root == NULL)
		return sum;
	
	if(root->left == NULL && root->right == NULL)
	{
		sum = root->data;
		root->data = 0;
		return sum;
	}

	sum += replace(root->left);
	sum += replace(root->right);
	sum += root->data;

	root->data = sum - root->data;

	return sum;
}

StackP stackElementCreate()
{
	StackP newStackElement = NULL;

	newStackElement = malloc(sizeof(StackElement));
	if(NULL == newStackElement)
	{
		perror("Failed to allocate stack! ");
		return NULL;
	}

	newStackElement->next = NULL;
	newStackElement->data = 0;

	return newStackElement;
}

int stackElementInsert(StackP head, int data)
{
	StackP newStackElement = NULL;

	newStackElement = stackElementCreate();

	if(NULL == newStackElement)
		return EXIT_FAILURE;

	newStackElement->next = head->next;
	head->next = newStackElement;

	newStackElement->data = data;

	return EXIT_SUCCESS;
}

int pop(StackP head)
{
	StackP currentStackElement = NULL;
	int data = 0;

	currentStackElement = head->next;
	head->next = currentStackElement->next;

	data = currentStackElement->data;

	free(currentStackElement);

	return data;
}