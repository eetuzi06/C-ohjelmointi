//
// Created by eetul on 22.1.2026.
//
#include <stdio.h>

int main() {
    float bussilippu;
    float taxi;
    float money;
    int choice;
    printf("Enter price of bus ticket: ");
    scanf("%f", &bussilippu);
    printf("Enter price of taxi: ");
    scanf("%f", &taxi);
    printf("Enter how much money you have: ");
    scanf("%f", &money);


    while (money >= bussilippu || money >= taxi) {

        printf("\nDo you want to take:\n");
        printf("1 = Bus (%.2f euros)\n", bussilippu);
        printf("2 = Taxi (%.2f euros)\n", taxi);
        printf("Enter your selection:");
        scanf("%d", &choice);

        if (choice == 1) {
            if (money >= bussilippu) {
                printf("\nYou chose bus.\n");
                money = money - bussilippu;
                printf("You have %.2f euros left", money);

            } else {
                printf("You don't have enough money for a bus.\n");
                printf("You have %.2f euros left", money);
            }

        }
        else if (choice == 2) {
            if (money >= taxi) {
                printf("\nYou chose taxi.\n");
                money = money - taxi;
                printf("You have %.2f euros left", money);


            } else {
                printf("You don't have enough money for a taxi.\n");
                printf("You have %.2f € left", money);
            }
        }
    }

    printf("\nYou dont have enough money, you'll have to walk\n");

}
