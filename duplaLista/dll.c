#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Node head = {.number = 0, .next = NULL, .prev = NULL};
	Position headPosition = &head;

	int option = 3;

	while(1)
	{
		printf("\n--OPTIONS--: 0-prepend, 1-append"
			", 2-print, 3-exit, 4-select element\n");
		printf("Your option: ");
		scanf(" %d", &option);
		switch(option)
		{
			case 0:
				prepend(headPosition);
				break;

			case 1:
				append(headPosition);
				break;

			case 2:
				print(headPosition);
				break;

			case 3:
				freeList(headPosition);
				return EXIT_SUCCESS;

			case 4:
				selectElement(headPosition);
				return EXIT_SUCCESS;

			default:
				break;
		}
	}

	return EXIT_SUCCESS;
}

Position makeNode()
{
	Position newNode = NULL;
	int number = 0;

	newNode = (Position)malloc(sizeof(Node));
	if(NULL == newNode)
	{
		perror("Cannot allocate memmory!");
		return NULL;
	}

	newNode->next = NULL;
	newNode->prev = NULL;

	printf("Input number: ");
	scanf(" %d", &number);
	newNode->number = number;

	return newNode;
}


int prepend(Position head)
{
	Position newNode = NULL;

	newNode = makeNode();
	if (NULL == newNode)
		return EXIT_FAILURE;

	if(head->next != NULL)
		head->next->prev = newNode;

	newNode->next = head->next;
	head->next = newNode;
	newNode->prev = head;

	return EXIT_SUCCESS;
}

Position findLast(Position head)
{
	Position tmp = head;

	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	return tmp;
}

int append(Position head)
{
	Position lastNode = NULL;
	Position newNode = NULL;

	newNode = makeNode();
	if (NULL == newNode)
		return EXIT_FAILURE;

	lastNode = findLast(head);

	lastNode->next = newNode;
	newNode->prev = lastNode;

	return EXIT_SUCCESS;
}

int print(Position head)
{
	Position current = NULL;

	if(NULL == head->next)
		return -1;

	current = head->next;

	puts("");
	while(current != NULL)
	{
		printf("|%d| ", current->number);
		current = current->next;
	}
	puts("");

	return EXIT_SUCCESS;
}

int freeList(Position head)
{
	Position tmp = head->next;
	Position current = NULL;

	while(tmp != NULL)
	{
		current = tmp;
		tmp = tmp->next;
		free(current);
	}

	head->next = NULL;

	return EXIT_SUCCESS;
}

int selectElement(Position head)
{
	int value = 0;
	Position tmp = head;

	if(head->next == NULL)
	{
		return EXIT_SUCCESS;
	}

	printf("Use keys: 1 (<-), 2(->), any other key for exit\n");
	print(head);

	while(1)
	{
		scanf("%d", &value);
		switch(value)
		{
			case 1:
				if(tmp->prev != NULL)
				{
					tmp = tmp->prev;
					printf("|%d| ", tmp->number);
				}
				break;

			case 2:
				if (tmp->next != NULL)
				{
					tmp = tmp->next;
					printf("|%d| ", tmp->number);
				}
				break;

			default:
				return EXIT_SUCCESS;
		}
	}
	
	return EXIT_SUCCESS;
}