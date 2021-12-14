#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"


int main()
{
	Directory dirHead = {.name="~", .sibling=NULL, .child = NULL};
	StackElement stackHead = {.parentDir = &dirHead, .next = NULL};


	navigation(&dirHead, &stackHead);

	return EXIT_SUCCESS;
}

Position directoryCreate(char* name)
{
	Position newDirectory = NULL;

	newDirectory = malloc(sizeof(Directory));
	if (NULL == newDirectory)
	{
		perror("Cannot allocate memmory!");
		return NULL;
	}

	strcpy(newDirectory->name, name);
	newDirectory->sibling = NULL;
	newDirectory->child = NULL;

	return newDirectory;
}

Position directoryInsertSorted(Position current, Position newDirectory)
{
	if (NULL == current)
		return newDirectory;

	if (strcmp(current->name, newDirectory->name) < 0)
	{
		current->sibling = directoryInsertSorted(current->sibling, newDirectory);
	}
	else
	{
		newDirectory->sibling = current;
		return newDirectory;
	}

	return current;
}

int directoryInsert(Position current, StackP stackHead, char* name)
{
	Position newDirectory = NULL;

	newDirectory = directoryCreate(name);
	if (NULL == newDirectory)
		return EXIT_FAILURE;

	current->child = directoryInsertSorted(current->child , newDirectory);

	return EXIT_SUCCESS;
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
	newStackElement->parentDir = NULL;

	return newStackElement;
}

int stackElementInsert(StackP head, Position parentDir)
{
	StackP newStackElement = NULL;

	newStackElement = stackElementCreate();

	if(NULL == newStackElement)
		return EXIT_FAILURE;

	newStackElement->next = head->next;
	head->next = newStackElement;

	newStackElement->parentDir = parentDir;

	return EXIT_SUCCESS;
}

Position pop(StackP head)
{
	StackP currentStackElement = NULL;
	Position parentDirectory = NULL;

	currentStackElement = head->next;
	head->next = currentStackElement->next;

	parentDirectory = currentStackElement->parentDir;

	free(currentStackElement);

	return parentDirectory;
}
// DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

int navigation(Position parent, StackP stackHead)
{
	char function[5];
	char name[MAX_STRING] = "";
	char buffer[MAX_STRING] = "";
	int option = 0;

	Position current = parent;
	Position tmp = NULL;

	while(1)
	{
		printPath(current, stackHead);
		fgets(buffer, MAX_STRING, stdin);
		sscanf(buffer, " %s %s", function, name);

		if (strcmp("md", function) == 0)
		{
			if (strlen(name) == 1)
			{
				printf("usage: md <name>\n");
				return CONTINUE;
			}

			directoryInsert(current, stackHead, name);
		}

		else if (strcmp("cd", function) == 0)
		{
			if (strlen(name) == 1)
				printf("usage: cd <name>\n");

			tmp = directoryFindByName(current, name);
			if (tmp == NULL)
			{
				printf("cd: no such file or directory: %s\n", name);
				continue;
			}

			if (EXIT_FAILURE == stackElementInsert(stackHead, current))
				continue;

			current = tmp;
		}

		else if (strcmp("cd..", function) == 0)
		{
			current = pop(stackHead);
			//printf("/%s\n", current->name);
		}

		else if (strcmp("dir", function) == 0)
		{
			printChildren(current);
		}

		else if (strcmp("exit", function) == 0)
			return EXIT_SUCCESS;

		else
			printf("command not found: %s\n", function);
	}

	return EXIT_FAILURE;
}

Position directoryFindByName(Position current, char* name)
{
	Position child = current->child;

	if(NULL == child)
	{
		printf("Current directory is empty\n");
		return child;
	}

	while(child != NULL && strcmp(child->name, name) != 0)
	{
		child = child->sibling;
	}

	return child;
}

int printPath(Position current, StackP stackHead)
{
	char path[MAX_STRING] = "";
	char tmpString[MAX_STRING] = "";
	StackP tmp = stackHead;

	while(tmp)
	{
		strcpy(tmpString, tmp->parentDir->name);
		strcat(tmpString, path);
		tmp = tmp->next;
	}

	strcat(path, current->name);

	printf("%s %% ", path);

	return EXIT_SUCCESS;
}

int printChildren(Position current)
{
	Position tmp = current->child;

	if(NULL == tmp)
		return EXIT_SUCCESS;

	while(tmp)
	{
		printf("%s\t", tmp->name);
		tmp = tmp->sibling;
	}

	puts("");

	return EXIT_SUCCESS;
}

