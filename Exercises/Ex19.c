//
// Created by eetul on 15.3.2026.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define namesize 50
#define maxlength 80

typedef struct menu_item_ {
    char name[namesize];
    double price;
} menu_item;

int compare_price(const void *a, const void *b) {
    menu_item *itemA = (menu_item *)a;
    menu_item *itemB = (menu_item *)b;

    if (itemA->price < itemB->price) {
        return -1;
    } else if (itemA->price > itemB->price) {
        return 1;
    }
}

int compare_by_name(const void *a, const void *b) {
    menu_item *itemA = (menu_item *)a;
    menu_item *itemB = (menu_item *)b;
    return strcmp(itemA->name, itemB->name);
}

int main(void) {
    char filename[namesize];
    char line[maxlength];
    FILE *my_file;
    menu_item arr[40];

    printf("Enter filename: ");
    fgets(filename, namesize, stdin);

    filename[strcspn(filename, "\n")] = '\0';

    my_file = fopen(filename, "r");

    if(my_file == NULL){
        fprintf(stderr, "Couldn't open %s.\n", filename);
        return 0;
    } else {
        printf("Reading from %s...\n", filename);
        int i = 0;
        while(fgets(line, maxlength, my_file) != NULL && i < 40) {
            line[strcspn(line, "\n")] = 0;
            char *name = strtok(line, ";");
            char *price = strtok(NULL, ";");

            if (name && price) {
                while (*price == ' ') price++;

                strncpy(arr[i].name, name, sizeof(arr[i].name) - 1);
                arr[i].name[sizeof(arr[i].name) - 1] = '\0';
                arr[i].price = atof(price);
                i++;
            }



        }
        fclose(my_file);

        int choice;
        printf("\nChoose sorting order:\n");
        printf("1. Sort by price\n");
        printf("2. Sort by name\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            qsort(arr, i, sizeof(menu_item), compare_price);
        }
        else if (choice == 2) {
            qsort(arr, i, sizeof(menu_item), compare_by_name);
        }


        printf("\n%-50s %8s\n", "Item", "Price (€)");
        printf("-------------------------------------------------- --------\n");
        for (int j = 0; j < i; j++) {
            printf("%-50s %8.2f\n", arr[j].name, arr[j].price);
        }
    }
    return 0;
}
