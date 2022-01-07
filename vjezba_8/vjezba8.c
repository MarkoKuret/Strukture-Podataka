/*vjezba
8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog dataa u stablo, ispis elemenata
(inorder, preorder, postorder i level order), brisanje i pronalaženje nekog dataa.
*/

#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

int main()
{
	Position root = NULL;
	menu(root);

	return EXIT_SUCCESS;
}

int menu(Position root)
{
	inputOption option = 0;
	int data = 0;
	int check = 0;
	Position tmp = NULL;

	while (1)
	{
		printf("\n--OPITONS:\n\t1 - add new data\n\tprint:\n\t  2 - inorder\n\t  3 - preorder"
			   "\n\t  4 - postorder\n\t  5 - level order\n\t6 - find by data\n\t7 - delete by data\n\tPRESS ANY OTHER KEY FOR EXIT\n");
		printf("\n--Option: ");
		check = scanf(" %d", &option);
			if (check != 1)
			{
				printf("\nexiting...");
				return EXIT_FAILURE;
			}

		switch (option)
		{
		case INSERT:
			printf("Insert data: ");
			check = scanf(" %d", &data);
			if (check != 1)
			{
				printf("INVALID DATA TYPE!\nexiting...");
				return EXIT_FAILURE;
			}

			root = insertNode(data, root);
			break;

		case INORDER:
			printInOrder(root);
			break;

		case PREORDER:
			printPreOrder(root);
			break;

		case POSTORDER:
			printPostOrder(root);
			break;

		case LEVEL_ORDER:
			printLevelOrder(root);
			break;

		case FIND:
			printf("Find element by data: ");
			check = scanf(" %d", &data);
			if (check != 1)
			{
				printf("INVALID DATA TYPE!\nexiting...");
				return EXIT_FAILURE;
			}

			tmp = findNode(root, data);

			if (tmp != NULL)
				printf("Found element %d in location %p\n", tmp->data, tmp);
			else
				printf("Element not found!\n");

			break;

		case DELETE:
			printf("Delete element by data: ");
			check = scanf(" %d", &data);
			if (check != 1)
			{
				printf("INVALID DATA TYPE!\nexiting...");
				return EXIT_FAILURE;
			}

			root = deleteNode(root, data);
			break;

		default:
			printf("exiting...\n\n");
			return EXIT_SUCCESS;
		}
	}

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

	else if (data < root->data)
		root->left = insertNode(data, root->left);

	else if (data > root->data)
		root->right = insertNode(data, root->right);

	return root;
}

int printInOrder(Position root)
{
	if (root != NULL)
	{
		printInOrder(root->left);
		printf("%d\n", root->data);
		printInOrder(root->right);
	}
	return EXIT_SUCCESS;
}

int printPreOrder(Position root)
{
	if (root != NULL)
	{
		printf("%d\n", root->data);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
	return EXIT_SUCCESS;
}

int printPostOrder(Position root)
{
	if (root != NULL)
	{
		printPostOrder(root->left);
		printPostOrder(root->right);
		printf("%d\n", root->data);
	}
	return EXIT_SUCCESS;
}

int getHeight(Position root)
{
	int rmax = 0;
	int lmax = 0;

	if (NULL == root)
		return 0;

	lmax = getHeight(root->left);
	rmax = getHeight(root->right);

	if (lmax > rmax)
		return lmax + 1;
	else
		return rmax + 1;
}

int printCurrentLevel(Position root, int height)
{
	if (NULL == root)
	{
		printf("   ");
		return EXIT_SUCCESS;
	}
	if (height == 1)
		printf("|%d| ", root->data);
	else if (height > 1)
	{
		printCurrentLevel(root->left, height - 1);
		printCurrentLevel(root->right, height - 1);
	}
	return EXIT_SUCCESS;
}

int printLevelOrder(Position root)
{
	int height = 0;
	int i = 0;
	int j = 0;
	height = getHeight(root);

	for (i = 1; i <= height; i++)
	{
		for(j = height; j > i; j--)
			printf("  ");
		printCurrentLevel(root, i);
		puts("");
	}
	return EXIT_SUCCESS;
}

Position deleteNode(Position root, int data)
{
	Position tmp;

	if (NULL == root)
		return NULL;

	else if (data < root->data)
		root->left = deleteNode(root->left, data);

	else if (data > root->data)
		root->right = deleteNode(root->right, data);

	else
	{
		if (root->left && root->right)
		{
			tmp = findMinimum(root->right);
			root->data = tmp->data;
			root->right = deleteNode(root->right, tmp->data);
		}
		else
		{
			tmp = root;
			if (NULL == root->left)
				root = root->right;

			else if (NULL == root->right)
				root = root->left;

			free(tmp);
		}
	}

	return root;
}

Position findMinimum(Position root)
{
	while (root->left)
		root = root->left;

	return root;
}

Position findNode(Position root, int data)
{
	if (NULL == root)
		return NULL;

	else if (data < root->data)
		return findNode(root->left, data);

	else if (data > root->data)
		return findNode(root->right, data);

	else
		return root;
}