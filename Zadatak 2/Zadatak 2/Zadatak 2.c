#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* Position;

struct Person {
    char name[64];
    char surname[64];
    int year_of_birth;
    Position next;
};

void push_to_front(Position);
void print_list(Position);
void push_to_back(Position);
Position find_surname(Position, char[]);
void delete_element(Position, char[]);
Position find_previous(Position, char[]);
void add_after_surname(Position, char[]);
void add_before_surname(Position, char[]);
void write_to_file(Position, char[]);
void read_from_file(Position, char[]);

int main() {

    Position head = (Position)malloc(sizeof(struct Person));
    if (head == NULL) {
        printf("Greska pri alokaciji memorije za dummy cvor!");
        return -1;
    }

    head->next = NULL;

    push_to_front(head);
    push_to_front(head);
    push_to_front(head);
    print_list(head->next);
    push_to_back(head);
    print_list(head->next);

    Position pronaden = find_surname(head->next, "ivic");
    if (pronaden != NULL) {
        printf("Osoba je pronadena!\n");
        printf("Podaci: %s %s %d\n", pronaden->name,
            pronaden->surname, pronaden->year_of_birth);
        printf("***********************\n");
    }
    else {
        printf("Osoba nije pronadena!\n");
    }

    delete_element(head, "ivic");
    print_list(head->next);
    add_after_surname(head, "anic");
    add_before_surname(head, "anic");
    print_list(head->next);
    write_to_file(head->next, "test.txt");
    read_from_file(head->next, "test.txt");

    return 0;
}

void push_to_front(Position p) {
    Position novi = (Position)malloc(sizeof(struct Person));

    printf("Unesi ime: ");
    scanf(" %s", novi->name);

    printf("Unesi prezime: ");
    scanf(" %s", novi->surname);

    printf("Unesi godinu rodenja: ");
    scanf(" %d", &novi->year_of_birth);

    novi->next = p->next;
    p->next = novi;

}

void print_list(Position p) {

    if (p == NULL) {
        printf("Prazna lista!\n");
        return;
    }

    while (p != NULL) {
        printf("Ime: %s\n", p->name);
        printf("Prezime: %s\n", p->surname);
        printf("Godina rodenja: %d\n", p->year_of_birth);
        printf("***********************\n");
        p = p->next;
    }

}

void push_to_back(Position p) {

    while (p->next != NULL) {
        p = p->next;
    }

    push_to_front(p);
}

Position find_surname(Position p, char prezime[]) {

    while (p != NULL && strcmp(p->surname, prezime) != 0) {
        p = p->next;
    }

    return p;
}

void delete_element(Position p, char prezime[]) {

    Position prev;

    prev = find_previous(p, prezime);

    if (prev == NULL) {
        printf("Ne postoji element u vezanoj listi s tim prezimenom!\n");
        return;
    }
    else {
        p = prev->next;
        prev->next = p->next;
        free(p);
    }
}

Position find_previous(Position p, char prezime[]) {

    Position prev = p;
    p = p->next;

    while (p != NULL && strcmp(p->surname, prezime) != 0) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        return NULL;
    }

    return prev;
}

void add_after_surname(Position head, char prezime[]) {

    Position found_element = find_surname(head->next, prezime);

    if (found_element == NULL) {
        printf("Greska: Osoba nije pronadena. Element nije dodan.\n");
        return;
    }

    Position novi = (Position)malloc(sizeof(struct Person));

    printf("Unesi ime: ");
    scanf(" %s", novi->name);

    printf("Unesi prezime: ");
    scanf(" %s", novi->surname);

    printf("Unesi godinu rodenja: ");
    scanf(" %d", &novi->year_of_birth);

    novi->next = found_element->next;

    found_element->next = novi; 

}

void add_before_surname(Position head, char prezime[]) {

    Position previous_element = find_previous(head, prezime);

    if (previous_element == NULL) {
        printf("Greska: Osoba s prezimenom '%s' nije pronadena. Element nije dodan.\n", prezime);
        return;
    }

    Position novi = (Position)malloc(sizeof(struct Person));

    printf("Unesi ime: ");
    scanf(" %s", novi->name);

    printf("Unesi prezime: ");
    scanf(" %s", novi->surname);

    printf("Unesi godinu rodenja: ");
    scanf(" %d", &novi->year_of_birth);

    novi->next = previous_element->next;

    previous_element->next = novi;

}

void write_to_file(Position p, char filename[]) {

    FILE* fp = NULL;
    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje: %s\n", filename);
        return;
    }

    while (p != NULL) {
        fprintf(fp, "%s %s %d\n", p->name, p->surname, p->year_of_birth);
        p = p->next;
    }

    fclose(fp);
}

void read_from_file(Position head, char filename[]) {

    FILE* fp = NULL;
    Position current_last = head;
    char name_buffer[64];
    char surname_buffer[64];
    int year_buffer;

    while (current_last->next != NULL) {
        current_last = current_last->next;
    }

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke: %s\n", filename);
        return;
    }

    while (fscanf(fp, "%s %s %d", name_buffer, surname_buffer, &year_buffer) == 3) {

        Position novi = (Position)malloc(sizeof(struct Person));

        strcpy(novi->name, name_buffer);
        strcpy(novi->surname, surname_buffer);
        novi->year_of_birth = year_buffer;
        novi->next = NULL;

        current_last->next = novi;
        current_last = novi;
    }

    fclose(fp);
}