#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Position;

struct Node {
	int element;
	Position next;
};

Position create_node();
int push(Position, int);
int pop(Position, int*);
int print_list(Position);
int delete_list(Position);
int postfix(char[], int*);

int main() {
	printf("Unesi ime datoteke: ");
	char filename[32] = "";
	scanf("%31s", filename);

	int result = 0;
	if (postfix(filename, &result) == 0)
	{
		printf("Uspjesno izracunat postfix.\nRezultat operacija: %d", result);
	}
}

Position create_node() {
	Position node = malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("ERROR, alokacija cvora\n");
		return NULL;
	}
	node->next = NULL;
	return node;
}

int push(Position p, int number) {
	Position node = create_node();
	if (node == NULL) {
		printf("ERROR, alokacija cvora\n");
		return 2;
	}
	if (p == NULL) {
		printf("ERROR, push funkcija null pointer\n");
		free(node);
		return 1;
	}
	node->element = number;
	node->next = p->next;
	p->next = node;
	return 0;
}

int pop(Position p, int* output) {
	if (p == NULL) {
		printf("ERROR, null pointer pop funkcija\n");
		return 1;
	}
	if (p->next != NULL) {
		Position temp = 0;
		int output1 = p->next->element;
		temp = p->next->next;
		free(p->next);
		p->next = temp;
		*output = output1;
		return 0;
	}
	else {
		printf("Stog je prazan\n");
		return 2;
	}
}

int print_list(Position p) {
	if (p == NULL) {
		printf("ERROR, print list null pointer\n");
		return 1;
	}

	Position current = p->next;
	if (current == NULL) {
		printf("Lista je prazna.\n");
		return 2;
	}

	while (current != NULL) {
		printf("%d ", current->element);
		current = current->next;
	}
	printf("\n");
	return 0;
}

int delete_list(Position p) {
	if (p == NULL) {
		printf("ERROR, delete list null pointer\n");
		return 1;
	}

	Position current = p->next;
	while (current != NULL) {
		Position next = current->next;
		free(current);
		current = next;
	}
	p->next = NULL;
	return 0;
}

int postfix(char* filename, int* result) {
	FILE* file = NULL;
	fopen_s(&file, filename, "r");
	if (file == NULL) {
		printf("ERROR, otvaranje datoteke\n");
		return 1;
	}

	if (fgetc(file) == EOF)
	{
		printf("ERROR, prazna datoteka\n");
		fclose(file);
		return 3;
	}
	else
		rewind(file);

	Position stackp = create_node();
	if (stackp == NULL) {
		printf("ERROR, alokacija memorije stog\n");
		fclose(file);
		return 2;
	}
	char znak = EOF;
	int number = 0;
	int previous = 0;


	while ((znak = fgetc(file)) != EOF && znak != '\n')
	{
		if (znak >= '0' && znak <= '9') {
			number *= 10;
			number += znak - '0';
			previous = 1;
		}
		else if (znak == ' ') {
			if (previous == 1) {
				if (push(stackp, number) != 0) {
					delete_list(stackp);
					free(stackp);
					fclose(file);
					return 7;
				}
				number = 0;
				previous = 0;
			}
			continue;
		}
		else {
			if (previous == 1) {
				if (push(stackp, number) != 0) {
					delete_list(stackp);
					free(stackp);
					fclose(file);
					return 7;
				}
				number = 0;
			}
			previous = 0;
			int op2 = 0;
			int op1 = 0;
			if (pop(stackp, &op2) == 2 || pop(stackp, &op1) == 2)
			{
				printf("ERROR, neispravan izraz\n");
				delete_list(stackp);
				free(stackp);
				fclose(file);
				return 3;
			}
			int result = 0;
			switch (znak) {
			case '+':
				result = op1 + op2;
				break;
			case '-':
				result = op1 - op2;
				break;
			case '*':
				result = op1 * op2;
				break;
			case '/':
				if (op2 == 0) {
					printf("ERROR: dijeljenje s nulom!\n");
					fclose(file);
					delete_list(stackp);
					free(stackp);
					return 3;
				}
				result = op1 / op2;
				break;
			default:
				printf("ERROR: nepoznat operator %c\n", znak);
				delete_list(stackp);
				free(stackp);
				fclose(file);
				return 4;
			}
			if (push(stackp, result) != 0) {
				delete_list(stackp);
				free(stackp);
				fclose(file);
				return 7;
			}
		}
	}
	if (previous == 1) {
		if (push(stackp, number) != 0) {
			delete_list(stackp);
			free(stackp);
			fclose(file);
			return 4;
		}
		number = 0;
	}
	if (stackp->next->next != NULL)
	{
		printf("ERROR, neispravan izraz\n");
		delete_list(stackp);
		free(stackp);
		fclose(file);
		return 5;
	}
	pop(stackp, result);
	delete_list(stackp);
	free(stackp);
	fclose(file);
	return 0;
}

