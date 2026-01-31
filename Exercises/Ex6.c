//
// Created by eetul on 31.1.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int read_d6(void);
int read_d10(void);
int valinta_fun(int low, int high);

int read_d6(void) {
    srand(time(NULL));
    int random_variable = rand();
    printf("Random number on range (1-6): ", RAND_MAX, random_variable);

    for (int n=0; n != 1; ++n) {
        int x = 7;
        while (x > 6)
            x = 1 + rand()/((RAND_MAX + 1u)/6);
        printf("%d \n", x);
    }


}

int read_d10(void) {
    srand(time(NULL));
    int random_variable = rand();
    printf("Random number on range (1-10): ", RAND_MAX, random_variable);

    for (int n=0; n != 1; ++n) {
        int x = 11;
        while (x > 10)
            x = 1 + rand()/((RAND_MAX + 1u)/10);
        printf("%d \n", x);
    }


}

int main(void) {
    int valinta;
    int keskeytys = 1;

    while (keskeytys) {
        printf("1. Roll D6\n");
        printf("2. Roll D10\n");
        printf("3. Quit\n");
        valinta = valinta_fun(1, 3);

        if (valinta == 1) {
            read_d6();
        } else if (valinta == 2) {
            read_d10();
        } else if (valinta == 3) {
            printf("Goodbye !!!\n");
            keskeytys = 0;
        }
    }



}

int valinta_fun(int low, int high) {
    int range;
    int palautetaanko = 0;

    do {
        printf("Select your choice (1-3): ");
        if (scanf("%d", &range) == 1) {
            if (range >= low && range <= high) {
                palautetaanko = 1;
            } else {
                printf("Number is out of range.\n");
                printf("1. Roll D6\n");
                printf("2. Roll D10\n");
                printf("3. Quit\n");

            }
        } else {
            while (getchar() != '\n');
            printf("Invalid input, please enter an integer.\n");
            printf("1. Roll D6\n");
            printf("2. Roll D10\n");
            printf("3. Quit\n");

        }
    } while (!palautetaanko);

    return range;
}