#include <stdio.h>
//
// Created by eetul on 24.1.2026.
//
int main(void) {
    int studentLuku;
    printf("How many students?: ");
    scanf("%d", &studentLuku);
    int grade[studentLuku];

    for (int i = 0; i < studentLuku; i++) {
        grade[i] = -1;
    }
    int studentNumero = -1;

    while (studentNumero != 0) {
        printf("Enter student number (1 - %d) or 0 to stop: ", studentLuku);
        scanf("%d", &studentNumero);

        if (studentNumero >= 1 && studentNumero <= studentLuku) {
            int grades;
            printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", studentNumero);
            scanf("%d", &grades);

            if (grades >= 0 && grades <= 5) {
                grade[studentNumero - 1] = grades;
            }
            else if (grades != -1) {
                printf("Invalid grade !\n");
            }
        }
        else if (studentNumero != 0) {
            printf("Invalid student number!\n");
        }
    }

    printf("\nStudent Grade\n");
    for (int i = 0; i < studentLuku; i++) {
        if (grade[i] == -1) {
            printf("%d N/A\n", i + 1);
        } else {
            printf("%d %d\n",i + 1, grade[i]);
        }
    }
}