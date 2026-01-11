#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node* Position;

struct Node {
	int element;
	Position next;
};

Position crate_node() {
	Position node = malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("ERROR, alokacija cvora\n");
		return NULL;
	}
	node->next = NULL;
	return node;
}

int push(Position p, int broj) {
	Position node = crate_node();
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
	Position newNode = crate_node();
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

int main() {

	srand((unsigned int)time(NULL));

	char input = ' ';
	char action = ' ';
	int broj = 0;

	Position p = crate_node();

	if (p == NULL) return 1;

	do {
		printf("\nIzaberi:\na) Stack\nb) Queue\nx) Exit\nOdabir: ");
		scanf(" %c", &input);

		if (input == 'a' || input == 'b') {
			do {
				if (input == 'a')
					printf("\na) Push, b) pop, c) Random, d) Print, x) Back: ");
				else
					printf("\na) Enqueue, b) Dequeue, c) Random, d) Print, x) Back: ");

				scanf(" %c", &action);

				switch (action) {
				case 'a':
					printf("Unesi broj: ");
					scanf(" %d", &broj);
					if (input == 'a') {
						push(p, broj);
					}
					else {
						enqueue(p, broj);
					}
					break;

				case 'b':
					if (pop(p) == 0) {
						printf("Element uklonjen.\n");
					}
					
					break;

				case 'c':
					broj = rand() % (100 - 10 + 1) + 10;
					if (input == 'a') {
						push(p, broj);
					}
					else {
						enqueue(p, broj);
					}
					printf("Dodan broj: %d\n", broj);
					break;

				case 'd':
					print_list(p);
					break;
				}
			} while (action != 'x');

			delete_list(p);
		}
	} while (input != 'x');

	free(p);
	return 0;
}