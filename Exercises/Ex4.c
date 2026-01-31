//
// Created by eetul on 26.1.2026.
//
#include <stdio.h>
int read_integer(void);

int main(void) {
    int numero;
    float summa = 0;
    int count = 0;
    float average;

    do {
        printf("Give positive numbers or a negative to stop: ");
        numero = read_integer();

        if (numero >= 0) {
            summa += numero;
            count++;
        }
    } while (numero >= 0);

    if (count > 0) {
        average = summa / count;
        printf("You entered %d positive numbers. The average is: %.3f", count, average);
    }
}

int read_integer(void) {
    int number;
    int tulos;

    do {
        tulos = scanf("%d", &number);
        if (tulos == 0) {
            while (getchar() != '\n');
            printf("Invalid input. Please try again. \n");
            printf("Give positive numbers or a negative to stop: ");

        }
    } while (tulos == 0);

    return number;
}