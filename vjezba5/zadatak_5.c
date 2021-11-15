#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME 30


int main()
{
	double result = 0.0;
	char fileName[MAX_FILE_NAME];

	printf("\nType exit for exiting the program\n");
	
	while(1)
	{
		if(-2 == inputFileName(fileName))
			return EXIT_SUCCESS;
		if(EXIT_SUCCESS == calculatePostfixFromFile(&result, fileName))
			printf("Result: %.3lf\n\n", result);
	}

	return EXIT_SUCCESS;
}


Position createElement(double number)
{
	Position newElement = NULL;
	
	newElement = (Position)malloc(sizeof(newElement));
	if(NULL == newElement)
	{
		perror("Cannot allocate memmory! ");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int insertAfter(Position reference, Position newElement)
{
	newElement->next = reference->next;
	reference->next = newElement;

	return EXIT_SUCCESS;
}

int push(Position head, double number)
{
	Position newElement = NULL;

	newElement = createElement(number);
	if(NULL == newElement)
		return -1;

	insertAfter(head, newElement);

	return EXIT_SUCCESS;
}

int deleteAfter(Position reference)
{
	Position tmp = NULL;

	tmp = reference->next;
	if (NULL == tmp)
		return EXIT_SUCCESS;

	reference->next = tmp->next;
	free(tmp);

	return EXIT_SUCCESS;
}

int pop(double *value, Position head)
{
	if(NULL == head->next)
	{
		perror("Check file formatting! ");
		return -1;
	}

	*value = head->next->number;
	deleteAfter(head);

	return EXIT_SUCCESS;
}

int doOperation(Position head, char operacija)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int check = 0;

	check = pop(&operand2, head);
	if(check != EXIT_SUCCESS)
		return -2;

	check = pop(&operand1, head);
	if(check != EXIT_SUCCESS)
		return -1;

	switch(operacija)
	{
		case '+':
			result = operand1 + operand2;
			break;

		case '-':
			result = operand1 - operand2;
			break;

		case '*':
			result = operand1 * operand2;
			break;

		case '/':
			if(0 == operand2)
			{
				printf("Invalid - zero division! ");
				return -3;
			}
			result = operand1 / operand2;
			break;

		default:
			printf("Operation currently not supported! ");
			return -4;
	}

	push(head, result);

	return EXIT_SUCCESS;
}

int calculatePostfixFromFile(double* result, char* fileName)
{
	int fileLen = 0;
	int check = 0;
	int numBytes = 0;

	double number = 0;

	char *buffer = NULL;
	char *currentBuffer = 0;
	char operation = 0;

	FILE  * fp = NULL;

	stackElement head = { .number = 0, .next = NULL};

	fp = fopen(fileName, "rb");
	if(NULL == fp)
	{
		perror("Cannot open file! ");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fileLen = ftell(fp);

	buffer = (char*)calloc(fileLen + 1, sizeof(char));
	if(NULL == buffer)
	{
		perror("Cannot allocate memmory! ");
		return -1;
	}

	rewind(fp);
	fread(buffer, sizeof(char), fileLen, fp);
	printf("\nPostfix expression: %s", buffer);

	currentBuffer = buffer;
	while(strlen(currentBuffer) > 0)
	{
		check = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (check == 1)
		{
			push(&head, number);
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			check = doOperation(&head, operation);

			//provjera i uvjetno oslobadanje memorije
			if(check != EXIT_SUCCESS)
			{
				free(buffer);
				freeList(&head);

				return -2;
			}

			currentBuffer += numBytes;
		}
	}

	free(buffer);
	check = pop(result, &head);

	if (check != EXIT_SUCCESS) 
		return -3;

	if (head.next != NULL) 
	{
		printf("Postfix not valid! Please check your file!\n"); 
		return -4;
	}

	//oslobadanje memorije
	freeList(&head);
	
	return EXIT_SUCCESS;
}

int freeList(Position head)
{
	Position tmp = head;
	while (tmp->next != NULL)
	{
		deleteAfter(head);
	}

	return EXIT_SUCCESS;
}

int inputFileName(char* fileName)
{
	int check = 0;
	printf("File name (without type), or exit: ");
	check = scanf(" %s", fileName);
	if (check != 1)
			return -1;

	if(strcmp(fileName, "exit") == 0)
	{
		return -2;
	}

	strcat(fileName, ".txt");

	return EXIT_SUCCESS;
}



