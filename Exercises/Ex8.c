//
// Created by eetul on 5.2.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 15

void print_numbers(const int *array, int count);

void print_numbers(const int *array, int count) {
    for (int i = 0; i < count; i++) {
        printf("%8d\n", array[i]);
    }

}

int main(void) {
    int numbers[ARRAY_SIZE];

    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand();
    }
    print_numbers(numbers, ARRAY_SIZE);

    return 0;

}