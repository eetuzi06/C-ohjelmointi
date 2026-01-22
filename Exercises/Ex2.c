
#include <stdio.h>
int main() {
    float salary[12];
    float taxes[12];
    float taxrate, taxrateover;
    float incomelimit;
    float totalincome = 0;
    float taxable;

    printf("Enter tax rate: ");
    scanf("%f", &taxrate);

    printf("Enter income limit: ");
    scanf("%f", &incomelimit);

    printf("Enter tax rate for income over the limit:");
    scanf("%f", &taxrateover);

    for (int i=0; i<12; i++) {
        printf("Enter income for month %d: ", i+1);
        scanf("%f", &salary[i]);
    }

    for (int i=0; i<12; i++) {
        float salari = salary[i];
        float tax = 0;

        if (totalincome + salari <= incomelimit) {
            tax = salari * taxrate / 100.0;
        } else if (totalincome >= incomelimit) {
            tax = salari * taxrateover / 100.0;
        } else {
            float lower = incomelimit - totalincome;
            float higher = salari - lower;
            tax = lower * taxrate / 100.0 + higher * taxrateover / 100.0;
        }

        taxes[i] = tax;
        totalincome += salari;
    }
    printf("\n%-5s %-10s %-10s\n", "month", "income", "tax");

    for (int i = 0; i < 12; i++) {
        printf("%-5d %10.2f %10.2f\n", i + 1, salary[i], taxes[i]);
    }


}