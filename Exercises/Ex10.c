//
// Created by eetul on 11.2.2026.
//
#include <stdio.h>
#include <string.h>

int main(void) {
    char merkkijono[20];

    do {
        printf("Enter a string: ");
        fgets(merkkijono, 20, stdin);
        merkkijono[ strcspn(merkkijono, "\n")] = '\0';
        printf("Your string was: %s and its length is: %d letters\n", merkkijono, strlen(merkkijono));

    } while (strcmp(merkkijono, "stop") != 0);
}

