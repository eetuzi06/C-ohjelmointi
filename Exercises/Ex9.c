//
// Created by eetul on 5.2.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 20

int find_first(const unsigned int *array, unsigned int what);

int find_first(const unsigned int *array, unsigned int what) {
    const unsigned int *p = array;
    int alkio = 0;
    while (*p != 0) {
        if (*p == what) {
            return alkio;
        }
        p++;
        alkio++;
    }
    return -1;
}

int main(void) {
    unsigned int numbers[ARRAY_SIZE];
    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = (rand() % 20) + 1;
    }

    numbers[ARRAY_SIZE - 1] = 0;

    printf("Array contents\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%u\n", numbers[i]);
    }

    unsigned int search;
    int result;

    do {
        printf("Enter a number to search or 0 to stop: ");

        if (scanf("%u", &search) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            search = 1;
        } else {
            if (search != 0) {
                result = find_first(numbers, search);

                if (result == -1) {
                    printf("Didn't find the number.\n");
                } else {
                    printf("Found the number from index %d\n", result);
                }
            }
        }
    } while (search != 0);
    printf("Program ending.");
    return 0;

}