#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Position;

struct Node {
    int element;
    Position next;
};

Position create_node();
int add_to_start(Position, int, Position);
int add_to_end(Position, int, Position);
int print_list(Position);
int delete_list(Position);
int delete_node(Position, Position);
int add_after_node(Position, int, int, Position);
int add_before_node(Position, int, int, Position);
int add_sorted_node(Position, int, Position);
int polynomial_sort(Position*);
int already_in_list(Position, int);
Position unija(Position*, int);
Position presjek(Position*, int);
Position read_sorted_list(FILE*);
FILE* file_input();

int main() {
    FILE* files[2] = { NULL };
    Position p[2];

    for (int i = 0; i < 2; i++)
    {
        printf("%d ", i + 1);
        files[i] = file_input();
        if (files[i] == NULL)
            i--;
    }

    for (int i = 0; i < 2; i++)
    {
        p[i] = read_sorted_list(files[i]);
        if (p[i] == NULL) {
            printf("ERROR, ucitavanje liste iz datoteke");
            return 1;
        }
    }
    char input = '0';
    do
    {
        printf("\nUnesi znak za trazenu radnju:\n1) Unija brojeva \n2) Presjek brojeva \nx) Prekid programa\n");
        scanf(" %c", &input);


        Position newp = NULL;

        switch (input)
        {
        case '1': {
            newp = unija(p, 2);
            if (newp == NULL)
                input = 'x';
            printf("Nova lista: ");
            print_list(newp);
            delete_list(newp);
            free(newp);
            break;
        }
        case '2': {
            newp = presjek(p, 2);
            if (newp == NULL)
                input = 'x';
            printf("Nova lista: ");
            print_list(newp);
            delete_list(newp);
            free(newp);
            break;
        }
        default:
            break;
        }

    } while (input != 'x');

    for (int i = 0; i < 2; i++)
    {
        if (files[i] != NULL)
            fclose(files[i]);
        if (p[i] != NULL) {
            delete_list(p[i]);
            free(p[i]);
        }
    }
    return 0;

}

Position create_node() {
    Position node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("ERROR, nije alociran cvor\n");
        return NULL;
    }
    node->next = NULL;
    return node;
}

int add_to_start(Position p, int num, Position node) {
    if (p == NULL || node == NULL) {
        printf("ERROR, add to start\n");
        return 1;
    }
    node->element = num;
    node->next = p->next;
    p->next = node;
    return 0;
}

int add_to_end(Position p, int num, Position node) {
    if (p == NULL || node == NULL) {
        printf("ERROR, add to end\n");
        return 1;
    }
    node->element = num;
    node->next = NULL;

    Position current = p;
    while (current->next != NULL)
        current = current->next;

    current->next = node;
    return 0;
}

int print_list(Position p) {
    if (p == NULL) {
        printf("ERROR, print list\n");
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
    return 0;
}

int delete_list(Position p) {
    if (p == NULL) {
        printf("ERROR, delete list\n");
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

int delete_node(Position p, Position node) {
    if (p == NULL || node == NULL) {
        printf("ERROR, delete node\n");
        return 1;
    }

    Position currentNode = p;
    while (currentNode->next != NULL) {
        if (currentNode->next == node) {
            currentNode->next = node->next;
            free(node);
            printf("Element izbrisan iz liste!\n");
            return 0;
        }
        currentNode = currentNode->next;
    }
    printf("Element nije pronaden!");
    return 1;
}

int add_after_node(Position p, int targetIndex, int num, Position newNode) {
    if (p == NULL || newNode == NULL) {
        printf("ERROR, add after node\n");
        return 1;
    }

    Position pointer = p->next;
    int i = 0;
    while (pointer != NULL) {
        if (i == targetIndex) {
            newNode->element = num;
            newNode->next = pointer->next;
            pointer->next = newNode;
            printf("Clan dodan nakon elementa s %d!\n", targetIndex);
            return 0;
        }
        pointer = pointer->next;
        i++;
    }

    printf("Indeks nije pronaden!\n");
    free(newNode);
    return 1;
}

int add_before_node(Position p, int targetIndex, int num, Position newNode) {
    if (p == NULL || newNode == NULL) {
        printf("ERROR, add before node\n");
        return 1;
    }

    Position pointer = p;
    int i = 0;
    while (pointer->next != NULL) {
        if (i == targetIndex) {
            newNode->element = num;
            newNode->next = pointer->next;
            pointer->next = newNode;
            printf("Clan dodan prije elementa s %d!\n", targetIndex);
            return 0;
        }
        pointer = pointer->next;
        i++;
    }

    printf("Indeks nije pronaden!\n");
    free(newNode);
    return 1;
}

int add_sorted_node(Position p, int num, Position newNode) {
    if (p == NULL || newNode == NULL)
    {
        printf("ERROR, ucitavanje liste u add sorted node");
        return 1;
    }

    Position current = p;
    while (current->next != NULL) {
        if (num >= current->next->element)
            break;
        current = current->next;
    }

    newNode->element = num;
    newNode->next = current->next;
    current->next = newNode;

    return 0;
}

int polynomial_sort(Position* p) {
    if (p == NULL || *p == NULL)
    {
        printf("ERROR, ucitavanje liste u polynomial sort");
        return 1;
    }
    if ((*p)->next == NULL) {
        printf("Lista je prazna!");
        return 0;
    }

    Position newp = create_node();
    if (newp == NULL)
        return 2;

    Position current = (*p)->next;
    Position newNode = NULL;
    while (current != NULL)
    {
        newNode = create_node();
        if (newNode == NULL)
            return 2;
        if (add_sorted_node(newp, current->element, newNode) != 0) {
            printf("ERROR, polynomial sort");
            return 3;
        }
        current = current->next;
    }
    delete_list(*p);
    *p = newp;
    return 0;
}

int already_in_list(Position p, int number) {
    if (p == NULL)
    {
        printf("ERROR, ucitavanje liste u already in list");
        return -1;
    }

    Position current = p->next;

    while (current != NULL)
    {
        if (current->element == number) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Position unija(Position* p, int arr_length) {
    if (p == NULL)
    {
        printf("ERROR, join without duplicates 1");
        return NULL;
    }
    Position newp = create_node();
    if (newp == NULL) {
        printf("ERROR, join without duplicates 2");
        return NULL;
    }
    Position newNode;
    Position current = NULL;
    for (int i = 0; i < arr_length; i++) {
        Position current = p[i]->next;
        while (current != NULL) {
            if (already_in_list(newp, current->element) == 0) {
                Position newNode = create_node();
                if (newNode != NULL) {
                    add_sorted_node(newp, current->element, newNode);
                }
            }
            current = current->next;
        }
    }
    return newp;
}

Position presjek(Position* p, int arr_length) {
    if (p == NULL)
    {
        printf("ERROR, funkcija presjek");
        return NULL;
    }
    Position newp = create_node();
    if (newp == NULL) {
        printf("ERROR, alokacija cvora u funkciji presjek");
        return NULL;
    }
    Position newNode;
    Position current = NULL;
    for (int i = 1; i < arr_length; i++) {
        Position current = p[i]->next;
        while (current != NULL) {
            if (already_in_list(p[0], current->element) == 1 && already_in_list(newp, current->element) == 0) {
                Position newNode = create_node();
                if (newNode != NULL) {
                    add_sorted_node(newp, current->element, newNode);
                }
            }
            current = current->next;
        }
    }
    return newp;
}

Position read_sorted_list(FILE* file) {
    if (file == NULL) {
        printf("Greska: datoteka nije otvorena!\n");
        return NULL;
    }

    Position p = create_node();
    if (p == NULL)
        return NULL;

    int num;
    Position node = NULL;
    while (fscanf(file, "%d", &num) == 1)
    {
        node = create_node();
        if (node == NULL) {
            delete_list(p);
            free(p);
            return NULL;
        }
        add_sorted_node(p, num, node);
    }

    return p;
}

FILE* file_input() {
    FILE* file = NULL;
    printf("Unesi ime datoteke: ");
    char fileName[40] = "";
    scanf(" %40s", fileName);

    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("ERROR, otvaranje datoteke");
    }
    return file;
}

