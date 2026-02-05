//
// Created by eetul on 4.2.2026.
//
#include <stdio.h>
#include <stdbool.h>
bool read_positive(int *value);

bool read_positive(int *value) {
    int number;
    printf("Enter a positive number: ");
    if (scanf("%d",&number)!=1) {
        while (getchar()!='\n');
        return false;
    }

    while (getchar()!='\n');
    if (number <= 0) {
        return false;
    }
    *value = number;
    return true;
}

int main(void) {
    int guess;
    int wrong_answer = 0;

    do {
        printf("Guess how much money i have!\n");

        if (read_positive(&guess)) {
            int muutos = guess * 2 + 20;
            printf("You didn't get it right. I have %d euros.\n", muutos);
        } else {
            printf("Incorrect input.\n");
            wrong_answer++;
        }
    } while (wrong_answer < 3);

    printf("I give up! See you later!");
    return 0;
}
