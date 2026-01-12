#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node* Position;

struct Node {
	int element;
	Position next;
};

Position create_node();
int print_list(Position);
int push(Position, int);
int pop(Position);
int enqueue(Position, int);
int dequeue(Position);
int delete_list(Position);

int main() {

	srand((unsigned int)time(NULL));

	char input = ' ';
	char action = ' ';
	int broj = 0;

	Position pStack = create_node();
	Position pQueue = create_node();
	if (pStack == NULL || pQueue == NULL) {
		return 1;
	}

	do {
		printf("\nIzaberi:\na) Stack\nb) Queue\nx) Exit\nOdabir: ");
		scanf(" %c", &input);

		if (input == 'a' || input == 'b') {
			do {
				if (input == 'a')
					printf("\nSTACK: a) Push, b) pop, c) Random, d) Print, x) Back: ");
				else
					printf("\nQUEUE: a) Enqueue, b) Dequeue, c) Random, d) Print, x) Back: ");

				scanf(" %c", &action);

				switch (action) {
				case 'a':
					printf("Unesi broj: ");
					scanf(" %d", &broj);
					if (input == 'a') {
						push(pStack, broj);
					}
					else {
						enqueue(pQueue, broj);
					}
					break;

				case 'b':
					if (input == 'a') {
						if (pop(pStack) == 0) printf("Element uklonjen sa Stacka.\n");
					}
					else {
						if (dequeue(pQueue) == 0) printf("Element uklonjen iz Queuea.\n");
					}
					break;

				case 'c':
					broj = rand() % (100 - 10 + 1) + 10;
					if (input == 'a') {
						push(pStack, broj);
					}
					else {
						enqueue(pQueue, broj);
					}
					printf("Dodan broj: %d\n", broj);
					break;

				case 'd':
					if (input == 'a') {
						printf("Sadrzaj STACKA: ");
						print_list(pStack);
					}
					else {
						printf("Sadrzaj QUEUEA: ");
						print_list(pQueue);
					}
					break;
				}
			} while (action != 'x');
		}
	} while (input != 'x');

	delete_list(pStack);
	free(pStack);
	delete_list(pQueue);
	free(pQueue);
	return 0;
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

int push(Position p, int broj) {
	Position node = create_node();
	if (node == NULL) {
		printf("ERROR, alokacija push\n");
		return 2;
	}
	if (p == NULL) {
		printf("ERROR, null pointer push\n");
		free(node);
		return 1;
	}
	node->element = broj;
	node->next = p->next;
	p->next = node;
	return 0;
}

int pop(Position p) {
	if (p == NULL) {
		printf("ERROR, pop pokazivac\n");
		return 1;
	}
	if (p->next != NULL) {
		Position temp = 0;
		temp = p->next->next;
		free(p->next);
		p->next = temp;
		return 0;
	}
	else {
		printf("Stog je prazan\n");
		return 2;
	}
}

int print_list(Position p) {
	if (p == NULL) {
		printf("ERROR, print list pokazivac\n");
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

int enqueue(Position p, int broj) {
	Position newNode = create_node();
	if (newNode == NULL) {
		printf("ERROR, enqueue");
		return 2;
	}
	newNode->element = broj;

	Position current = p;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newNode;
	return 0;
}

int dequeue(Position p) {
	if (p == NULL) {
		printf("ERROR, pokazivac dequeue\n");
		return 1;
	}
	if (p->next != NULL) {
		Position temp = 0;
		temp = p->next->next;
			
		free(p->next);
		p->next = temp;
		return 0;
	}
	else {
		printf("Red je prazan\n");
		return 2;
	}
}

int delete_list(Position p) {
	if (p == NULL) {
		printf("ERROR, delete list pointer\n");
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

