#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char student_id[20];
    char title[50];
    char date[15];
    char status[20];
    struct Node* next;
} Node;

Node* createNode(const char* sid, const char* t, const char* d, const char* s) {
    Node* n = malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy(n->student_id, sid);
    strcpy(n->title, t);
    strcpy(n->date, d);
    strcpy(n->status, s);
    n->next = NULL;
    return n;
}

void add(Node** head, const char* sid, const char* t, const char* d, const char* s) {
    Node* n = createNode(sid, t, d, s);
    if (!*head) *head = n;
    else {
        Node* cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }
}

void updateStatus(Node* head, const char* sid, const char* t, const char* newS) {
    while (head) {
        if (strcmp(head->student_id, sid) == 0 && strcmp(head->title, t) == 0) {
            strcpy(head->status, newS);
            break;
        }
        head = head->next;
    }
}

void displayAll(Node* head) {
    while (head) {
        printf("%s | %s | %s | %s\n", head->student_id, head->title, head->date, head->status);
        head = head->next;
    }
}

void searchByStudent(Node* head, const char* sid) {
    while (head) {
        if (strcmp(head->student_id, sid) == 0)
            printf("%s | %s | %s | %s\n", head->student_id, head->title, head->date, head->status);
        head = head->next;
    }
}

void freeList(Node* head) {
    while (head) {
        Node* t = head;
        head = head->next;
        free(t);
    }
}

int main() {
    Node* sub = NULL;

    add(&sub, "S001", "Math", "2025-08-15", "Submitted");
    add(&sub, "S002", "Science", "2025-08-16", "Pending");
    add(&sub, "S001", "History", "2025-08-17", "Pending");

    printf("All submissions:\n");
    displayAll(sub);

    updateStatus(sub, "S001", "History", "Submitted");
    printf("\nAfter update:\n");
    displayAll(sub);

    printf("\nSearch for S001:\n");
    searchByStudent(sub, "S001");

    freeList(sub);
    return 0;
}