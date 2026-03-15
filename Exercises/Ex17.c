//
// Created by eetul on 5.3.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

bool password_generator(char *pointer, int size, const char *word) {
    int wordlength = strlen(word);
    int passwordlength = 2 * wordlength + 1;

    if (size <= passwordlength) {
        return false;
    }
    pointer[0] = (char)(32 + (rand() % (126 - 32 + 1)));

    for (int i = 0; i < wordlength; i++) {
        pointer[i * 2 + 1] = word[i];
        pointer[i * 2 + 2] = (char)(32 + (rand() % (126 - 32 + 1)));
    }
    pointer[passwordlength - 1] = (char)(32 + (rand() % (126 - 32 + 1)));
    pointer[passwordlength] = '\0';
    return true;

}
int main(void) {
    char input[32];
    char password[100];

    srand((unsigned int)time(NULL));

    while (printf("Enter a word: "), fgets(input, 32, stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "stop") == 0) {
            break;
        }
        if (strlen(input) == 0) {
            printf("Error! Input cannot be empty.\n");
        }
        else if (password_generator(password, sizeof(password), input)) {
            printf("Generated password: %s\n", password);
        }
        else {
            printf("Error: Generated password could not fit in the buffer.\n");
        }
    }
}