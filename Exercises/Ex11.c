//
// Created by eetul on 12.2.2026.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int replace_char(char *str, const char *repl);

int replace_char(char *str, const char *repl) {
    if (strlen(repl) != 2) {
        return 0;
    }

    int counter = 0;
    int slen = strlen(str);

    for (int i = 0; i < slen; i++) {
        if (tolower(str[i]) == tolower(repl[0])) {
            str[i] = repl[1];
            counter++;
        }

    }
return counter;
}

int main(void) {
    char merkkijono[30];
    char merkkijono2[3];
    printf("Enter a string: ");
    fgets(merkkijono, 20, stdin);
    merkkijono[ strcspn(merkkijono, "\n")] = '\0';
    printf("Enter replacement for example (e3) replaces all E's to 3's: ");
    fgets(merkkijono2, 3, stdin);
    merkkijono2[ strcspn(merkkijono2, "\n")] = '\0';

    int vaihtoja = replace_char(merkkijono, merkkijono2);
    if (vaihtoja == 0) {
        printf("String was not modified.");
    }
    else {
        printf("Replaced %d characters\n", vaihtoja);
        printf("Your string now is: %s\n", merkkijono);

    }
    return 0;


}

