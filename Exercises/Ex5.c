//
// Created by eetul on 27.1.2026.
//
#include <stdio.h>
int read_range(int low, int high);

int read_range(int low, int high) {
    int range;
    int palautetaanko = 0;

    do {
        printf("Enter a number between 1 and 6: ");
        if (scanf("%d", &range) == 1) {
            if (range >= low && range <= high) {
                palautetaanko = 1;
            } else {
                printf("Integer must be inside the range of 1-6\n");
                printf("Roll a dice and enter your result.\n");

            }
        } else {
            while (getchar() != '\n');
            printf("Invalid input, please enter an integer.\n");
            printf("Roll a dice and enter your result.\n");

        }
    } while (!palautetaanko);

    return range;

}

int main(void) {
    int house;
    int player;
    int kierrokset = 3;

    printf("Lets play!\n");

    for (int i = 1; i <= kierrokset; i++) {
        printf("Roll a dice and enter your result.\n");
        player = read_range(1, 6);

        if (player == 6) {
            house = 6;
            printf("I got %d. It is a tie!\n", house);
        } else {
            house = player + 1;
            printf("I got %d. The house wins! (As always :D)\n", house);
        }

    }

    printf("Better luck next time. Bye!!\n");


}