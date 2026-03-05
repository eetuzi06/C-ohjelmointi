//
// Created by eetul on 4.3.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int number;
    struct node *next;
} nnode;

int main(void) {
    struct node *head = NULL;
    char input[50];
    int num;

    printf("Enter number ('end' to stop): ");
    scanf("%s", input);

    while (strcmp(input, "end") != 0) {
        if (sscanf(input, "%d", &num) == 1) {
             struct node *newnode = malloc(sizeof(nnode));

            newnode->number = num;
            newnode->next = head;
            head = newnode;
        } else {
            printf( "Error, invalid input\n");
        }
        printf("Enter number ('end' to stop): ");
        scanf("%s", input);
    }
    printf("Numbers entered: \n");

    nnode *current = head;
    while (current != NULL) {
        printf("%d\n", current->number);
        current = current->next;
    }
    while (head != NULL) {
        nnode *temp = head;
        head = head->next;
        free(temp);
    }
}