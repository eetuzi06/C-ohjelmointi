//
// Created by eetul on 12.2.2026.
//
#include <stdio.h>
#include <string.h>

int count_words(const char* str, const char *word);

int count_words(const char* str, const char *word) {

     int counter = 0;
    char *p = strstr(str, word);
    while (p != NULL) {
        counter++;
        p = strstr(p + strlen(word), word);
    }
return counter;
}

int main(void) {
    char merkkijono[150];
    char sana[20];
    do
    {
        printf("Enter a string: ");
        fgets(merkkijono, 150, stdin);
        merkkijono[ strcspn(merkkijono, "\n")] = '\0';

        printf("Enter a word: ");
        fgets(sana, 20, stdin);
        sana[strcspn(sana, "\n")] = '\0';
        
        if (strcmp(sana, "stop") != 0) {
            int count = count_words(merkkijono, sana);

            if (count == 0) {
                printf("The word was not found from the string.\n");
            } else {
                printf("The word was found from the string %d times.\n", count);
            }
        }
    } while (strcmp(sana, "stop") != 0);
}