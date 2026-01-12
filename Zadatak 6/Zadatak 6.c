#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int max = 0;
static int current = 0;

typedef struct Node* Position;

struct Node {
	int element;
	int priority;
	Position next;
};

Position create_node();
int push(Position, int);
int pop(Position);
int print_list(Position);
int enqueue(Position, int);
int dequeue(Position);
int deleteList(Position);

int main() {
	srand((unsigned int)time(NULL));
	char input = ' ';
	char action = ' ';
	int num = 0;

	Position pStack = create_node();
	Position pQueue = create_node();

	if (pStack == NULL || pQueue == NULL)
		return 1;

	do {
		printf("Odaberi:\na) Cirkularni stack\nb) Queue s prioritetom\nx) Exit\n");
		scanf(" %c", &input);

		switch (input) {
		case 'a': {
			printf("Unesite maksimalan broj elemenata stoga (0 za neograniceno): ");
			scanf("%u", &max);
			do {
				printf("\nSTACK - Odaberi: a) Push b) Pop c) Random d) Ispis x) Exit\n");
				scanf(" %c", &action);
				if (action == 'a') {
					printf("Unesi broj: "); scanf("%d", &num);
					push(pStack, num);
				}
				else if (action == 'b') {
					pop(pStack);
				}
				else if (action == 'c') {
					num = rand() % 91 + 10;
					push(pStack, num);
				}
				else if (action == 'd') {
					print_list(pStack);
				}
			} while (action != 'x');
			break;
		}
		case 'b': {
			do {
				printf("\nQUEUE - Odaberi: a) Enqueue b) Dequeue c) Random d) Ispis x) Exit\n");
				scanf(" %c", &action);
				if (action == 'a') {
					printf("Unesi broj: "); scanf("%d", &num);
					enqueue(pQueue, num);
				}
				else if (action == 'b') {
					dequeue(pQueue);
				}
				else if (action == 'c') {
					num = rand() % 100 - 10 + 1 + 10;
					enqueue(pQueue, num);
				}
				else if (action == 'd') {
					print_list(pQueue);
				}
			} while (action != 'x');
			break;
		}
		}
	} while (input != 'x');

	deleteList(pStack); 
	free(pStack);
	deleteList(pQueue); 
	free(pQueue);
	return 0;
}

Position create_node() {
	Position node = malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("ERROR, alokacija cvora\n");
		return NULL;
	}
	
	node->priority = rand() % (5 - 1 + 1) + 1;
	node->next = NULL;
	return node;
}

int push(Position p, int num) {
	if (max > 0 && current >= max) {
		printf("Pun Stack! Maksimalan broj elemenata je %d\n", max);
		return 3;
	}
	Position node = create_node();
	if (node == NULL) {
		printf("ERROR, alokacija push\n");
		return 2;
	}
	if (p == NULL) {
		printf("ERROR, push pokazivac null\n");
		free(node);
		return 1;
	}
	node->element = num;
	node->next = p->next;
	p->next = node;
	current++;
	return 0;
}

int pop(Position p) {
	if (p == NULL) {
		printf("ERROR, pokazivac u pop je null\n");
		return 1;
	}
	if (p->next != NULL) {
		Position temp = 0;
		temp = p->next->next;
		free(p->next);
		p->next = temp;
		current--;
		return 0;
	}
	else {
		printf("Stog je prazan\n");
		return 2;
	}
}

int print_list(Position p) {
	if (p == NULL) {
		printf("ERROR, print list pokazivac je null\n");
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

int enqueue(Position p, int num) {
	if (p == NULL) {
		printf("ERROR, enqueu pokazivac je null\n");
		return -1;
	}

	Position node = create_node();
	if (node == NULL) {
		printf("ERROR, enqueue alokacija cvora\n");
		return -2;
	}

	Position current = p;
	while (current->next != NULL) {
		if (node->priority > current->next->priority)
			break;
		current = current->next;
	}

	node->element = num;
	node->next = current->next;
	current->next = node;
	return node->priority;
}

int dequeue(Position p) {
	if (p == NULL) {
		printf("ERROR, dequeue pokazivac null\n");
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

int deleteList(Position p) {
	if (p == NULL) {
		printf("ERROR, delete list pokazivac null\n");
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

