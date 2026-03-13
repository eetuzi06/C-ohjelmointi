// Created by eetul on 2026-02-25.
//Car-Sales-Manager Project, finished 2026-03-13.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define maxlength 50
#define maxdatelength 10
#define linesize 250

//Making list for cars properties
typedef struct car
{
    char make[maxlength];
    char model[maxlength];
    int miles;
    char purchaseDate[maxdatelength];
    int purchasePrice;
    char sellingDate[maxdatelength];
    int sellingPrice;
    struct car *next;
} Car;

void addCar(const char *filename, Car c);
void date_check(const char *prompt, char *destination);
void removeNewline(char *str);
void string_check(const char *prompt, char *destination, int max_len);
int number_check(const char *prompt);
Car details(void);
void addCar(const char *filename, Car car);
void addSortedByProfit(Car **ppn, Car *new_node);
int parse_car_line(char *line, Car *detail);
void profitReport(const char *filename);
long dates(const char *date_str);
void add_sorted_by_time(Car **head, Car *new_node);
void sellTimeReport(const char *filename);


//Lets remove the newline from fgets
void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = 0;
}

void date_check(const char *prompt, char *destination) { //Lets check if date is in correct format
    bool problems = true;

    do {
        printf("%s", prompt);
        if (fgets(destination, maxlength, stdin) != NULL) {
            removeNewline(destination);

            //Length
            if (strlen(destination) != 10) {
                printf("Error! Date must be 10 characters (DD-MM-YYYY)!\n");
            }
            //Dashes
            else if (destination[2] != '-' || destination[5] != '-') {
                printf("Error! Use format DD-MM-YYYY with dashes (-)!\n");
            }
            else {
                //all numbers or no
                bool all_digits = true;
                for (int i = 0; i < 10; i++) {
                    // Check digits only from places without dashes
                    if (i != 2 && i != 5) {
                        if (!isdigit(destination[i])) {
                            all_digits = false;
                        }
                    }
                }

                if (all_digits == false) {
                    printf("Error! Use only numbers and dashes!\n");
                } else {
                    // We'll get through the function
                    problems = false;
                }
            }
        }
    } while (problems == true);
}

void string_check(const char *prompt, char *destination, int max_len) { //Checks if the answers are only characters
    bool problems = true;

    do {
        printf("%s", prompt);

        if (fgets(destination, max_len, stdin) != NULL) {
            removeNewline(destination);

            //Checking if user pressed enter or some other button
            if (strlen(destination) == 0) {
                printf("Error! You must've pressed the wrong button!\n");
            }
            else {
                //Does it contain numbers or no
                bool has_numbers = false;
                for (int i = 0; i < strlen(destination); i++) {
                    if (isdigit(destination[i])) {
                        has_numbers = true;
                    }
                }

                if (has_numbers) {
                    printf("Error! Numbers are not allowed in this field!\n");
                } else {
                    problems = false;
                }
            }
        }
    } while (problems == true);
}

int number_check(const char *prompt) //Checking if theres only numbers in a answer
{
    char temp[maxlength];
    int value = 0;
    bool problems = true;

    do
    {
        printf("%s", prompt);
        if (fgets(temp, sizeof(temp), stdin) != NULL)
        {

            if (temp[0] == '\n') //If user pressed enter
            {
                printf("Error, input cannot be empty.\n");
            }

            else if (sscanf(temp, "%d", &value) == 1) //It is number, moving forward
            {
                problems = false;
            }

            else
            {
                printf("Error! Please enter numbers only!\n");
            }
        }
    } while (problems == true);

    return value;

}

Car details(void) //Using different checking methods for questions
{
    Car car;

    string_check("Enter the make of the car:", car.make, maxlength);
    string_check("Enter the model of the car:", car.model, maxlength);
    car.miles = number_check("Enter the miles of the car:");
    date_check("Enter the purchase date (DD-MM-YYYY) of the car, you need to insert dashes between!: ", car.purchaseDate);
    car.purchasePrice = number_check("Enter the purchase price of the car:");
    date_check("Enter the selling date (DD-MM-YYYY) of the car, you need to insert dashes between!: ", car.sellingDate);
    car.sellingPrice = number_check("Enter the selling price of the car: ");

    return car;

}

//Function which adds cars to the CSV-file, does not return value
void addCar(const char *filename, Car car)
{
    FILE *newcar = fopen(filename, "a"); //Making file and appending / appending existing file

    if (newcar == NULL) //If file is empty or cant be opened
    {
        printf("Error opening file!\n");
        return;
    }


    //May look confusing, but it just prints the values one by one from their own variables
    fprintf(newcar, "%s,%s,%d,%s,%d,%s,%d\n",
        car.make,
        car.model,
        car.miles,
        car.purchaseDate,
        car.purchasePrice,
        car.sellingDate,
        car.sellingPrice);

    fclose(newcar); //Closing file, after not using it anymore.
    printf("Car info has been added successfully, Thank you!\n");

}
void addSortedByProfit(Car **ppn, Car *new_node) { //Sorting by profits, using double pointer for modifying the list
    int new_profit = new_node->sellingPrice - new_node->purchasePrice;
    //Sorting by descending order
    //Finding place where "new_profit" is bigger than old
    while (*ppn != NULL) {
        int current_profit = (*ppn)->sellingPrice - (*ppn)->purchasePrice;
        if (new_profit > current_profit) {
            break; // found it, Sorry for using break :D
        }
        ppn = &((*ppn)->next); // moving to the address of the next pointer
    }

    new_node->next = *ppn;
    *ppn = new_node;
}


int parse_car_line(char *line, Car *detail) {
    //Parses a single line for every car to the csv file
    int fields = sscanf(line,
        "%49[^,],"  // Make
        "%49[^,],"  // Model
        "%d,"       // Miles
        "%19[^,],"  // Purchase Date
        "%d,"       // Purchase Price
        "%19[^,],"  // Selling Date
        "%d",       // Selling Price
        detail->make,
        detail->model,
        &detail->miles,
        detail->purchaseDate,
        &detail->purchasePrice,
        detail->sellingDate,
        &detail->sellingPrice
    );

    return (fields == 7); //Works only if every detail inputted
}

void profitReport(const char *filename) { //Generates total profit
    FILE *profits = fopen(filename, "r");
    if (profits == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Car *head = NULL;
    char line[linesize];
    int totalProfit = 0;

    while (fgets(line, sizeof(line), profits)) {
        Car temp;
        if (parse_car_line(line, &temp)) {
            Car *new_node = (Car *)malloc(sizeof(Car));
            if (new_node != NULL) {
                *new_node = temp;

                //Counting total profit
                totalProfit += (new_node->sellingPrice - new_node->purchasePrice);

                //Descending order
                addSortedByProfit(&head, new_node);
            }
        }
    }
    fclose(profits);

    //Results
    printf("\n========================================");
    printf("\nTOTAL PROFIT MADE: %d e", totalProfit);
    printf("\n========================================\n");

    printf("\n%-15s %-15s %-10s %-10s %-10s\n", "MAKE", "MODEL", "BOUGHT (e)", "SOLD (e)", "PROFIT (e)");
    printf("----------------------------------------------------------------------\n");

    Car *current = head;
    while (current != NULL) {
        int profit = current->sellingPrice - current->purchasePrice;
        printf("%-15s %-15s %-10d %-10d %-10d\n",
               current->make, current->model, current->purchasePrice, current->sellingPrice, profit);

        Car *temp_to_free = current;
        current = current->next;
        free(temp_to_free); // Freeing the memory
    }
}

long dates(const char *date_str) { //Converts a  DD-MM-YYYY string to a "day index"
    int day, month, year;
    if (sscanf(date_str, "%d-%d-%d", &day, &month, &year) == 3) {
        return (year * 365L) + (month * 30L) + day;
    }
    return 0; //With this one i needed help from AI
}



void add_sorted_by_time(Car **head, Car *new_node) {
    // Counting new cars sell time
    long new_diff = dates(new_node->sellingDate) - dates(new_node->purchaseDate);

    Car **ppn = head; //Moving the doublepointer back to head
    while (*ppn != NULL) {
        long current_diff = dates((*ppn)->sellingDate) - dates((*ppn)->purchaseDate);

        // Descending sort
        if (new_diff > current_diff) {
            break;
        }
        ppn = &((*ppn)->next); //Moving forward
    }
    new_node->next = *ppn;
    *ppn = new_node;
}

void sellTimeReport(const char *filename) { //Report from selltime
    FILE *report = fopen(filename, "r");
    if (report == NULL) {
        printf("Error opening file !\n");
        return;
    }

    Car *list_head = NULL;
    char line[linesize];
    int total_profit = 0;

    while (fgets(line, sizeof(line), report)) {
        Car temp_data;
        if (parse_car_line(line, &temp_data)) {
            Car *new_car = malloc(sizeof(Car));
            if (new_car) {
                *new_car = temp_data;

                //Counting total profit
                total_profit += (new_car->sellingPrice - new_car->purchasePrice);

                //Descending order
                add_sorted_by_time(&list_head, new_car);
            }
        }
    }
    fclose(report);

    //Printing results
    printf("\n========================================");
    printf("\nREPORT: CARS SORTED BY SELL TIME");
    printf("\nTOTAL PROFIT MADE: %d EUR", total_profit);
    printf("\n========================================\n\n");

    //Headings
    printf("%-15s %-15s %-15s %-10s\n", "MAKE", "MODEL", "TIME IN STOCK", "PROFIT");
    printf("------------------------------------------------------------------\n");

    Car *current = list_head;
    while (current != NULL) {
        //Counting sell time for print
        long days = dates(current->sellingDate) - dates(current->purchaseDate);
        int profit = current->sellingPrice - current->purchasePrice;

        printf("%-15s %-15s %-10ld days    %-10d EUR\n",
               current->make,
               current->model,
               days,
               profit);

        //Freeing the memory
        Car *temp_free = current;
        current = current->next;
        free(temp_free);
    }
    printf("------------------------------------------------------------------\n");
}



int main(void) {
    const char *tiedosto = "cars.csv";
    int selection = 0;
    int check;

    do { //Asking what user wants to do
        printf("\nWhat do you wanna do?\n");
        printf("1. Add new car\n");
        printf("2. Print a report (profit)\n");
        printf("3. Print a report (sell time)\n");
        printf("Your choice (1-3): ");

        // Lets view it in character mode
        check = getchar();

        if (check == '\n') {
            printf("\nOops, you must've pressed a wrong button!\n");
        }
        else if (!isdigit(check)) { //Lets check if it has numbers or characters
            printf("\nInvalid selection! Use numbers only.\n");
            while (getchar() != '\n');
        }
        else {
            ungetc(check, stdin); // Returning data type to number
            scanf("%d", &selection);

            while (getchar() != '\n');

            if (selection < 1 || selection > 3) {
                printf("\nNumber is out of range! (1-3 only)\n");
            }
        }

    } while (selection < 1 || selection > 3);

    //Troubleshoot done, moving forward

    if (selection == 1) //Moving to the functions which describe the choice
    {
        printf("Cool you want to add new car!\n");
        Car new_car = details();
        addCar(tiedosto, new_car);
    }
    else if (selection == 2)
    {
        printf("Alright, lets see the Profit report!\n");
        profitReport(tiedosto);
    }
    else if (selection == 3)
    {
        printf("Alright lets see the sell time report!\n");
        sellTimeReport(tiedosto);
    }

}
