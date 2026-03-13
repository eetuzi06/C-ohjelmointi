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

//Making variables for cars properties
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

//Lets remove the newline from fgets
void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = 0;
}

void date_check(const char *prompt, char *destination) {
    bool problems = true;

    do {
        printf("%s", prompt);
        if (fgets(destination, maxlength, stdin) != NULL) {
            removeNewline(destination);

            // 1. TARKISTUS: Pituus
            if (strlen(destination) != 10) {
                printf("Error: Date must be 10 characters (DD-MM-YYYY).\n");
            }
            // 2. TARKISTUS: Viivat oikeilla paikoilla
            else if (destination[2] != '-' || destination[5] != '-') {
                printf("Error: Use format DD-MM-YYYY with dashes (-).\n");
            }
            else {
                // 3. TARKISTUS: Ovatko muut merkkejä numeroita?
                bool all_digits = true;
                for (int i = 0; i < 10; i++) {
                    // Tarkistetaan numerot vain kohdista, joissa EI ole viivaa
                    if (i != 2 && i != 5) {
                        if (!isdigit(destination[i])) {
                            all_digits = false;
                        }
                    }
                }

                if (all_digits == false) {
                    printf("Error: Use only numbers and dashes!\n");
                } else {
                    // Jos päästään tänne asti, kaikki on kunnossa!
                    problems = false;
                }
            }
        }
    } while (problems == true);
}

void string_check(const char *prompt, char *destination, int max_len) {
    bool problems = true;

    do {
        printf("%s", prompt);

        if (fgets(destination, max_len, stdin) != NULL) {
            removeNewline(destination); // Poistetaan \n heti alussa

            // 1. TARKISTUS: Tyhjä syöte
            if (strlen(destination) == 0) {
                printf("Error! You must've pressed the wrong button!\n");
            }
            else {
                // 2. TARKISTUS: Sisältääkö numeroita?
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

int number_check(const char *prompt)
{
    char temp[maxlength];
    int value = 0;
    bool problems = true;

    do
    {
        printf("%s", prompt);
        if (fgets(temp, sizeof(temp), stdin) != NULL)
        {

            if (temp[0] == '\n')
            {
                printf("Error, input cannot be empty.\n");
            }

            else if (sscanf(temp, "%d", &value) == 1)
            {
                problems = false;
            }

            else
            {
                printf("Error: Please enter numbers only!\n");
            }
        }
    } while (problems == true);

    return value;

}

Car details(void)
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
    FILE *newcar = fopen(filename, "a");

    if (newcar == NULL)
    {
        printf("Can't open file!\n");
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

    fclose(newcar);

    printf("Car info has been added successfully, Thank you!\n");

}
void addSortedByProfit(Car **ppn, Car *new_node) {
    int new_profit = new_node->sellingPrice - new_node->purchasePrice;

    // Etsitään paikka, jossa uusi voitto on suurempi kuin seuraavan
    while (*ppn != NULL) {
        int current_profit = (*ppn)->sellingPrice - (*ppn)->purchasePrice;
        if (new_profit > current_profit) {
            break; // Oikea paikka löytyi
        }
        ppn = &((*ppn)->next); // Siirrytään eteenpäin
    }

    // PDF 12b s. 7 & 11 mukainen kytkentä:
    new_node->next = *ppn;
    *ppn = new_node;
}


int parse_car_line(char *line, Car *detail) {
    // Käytetään sscanf:ää, mutta kirjoitetaan se luettavasti
    // %[^,] lukee pilkkuun asti
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

    return (fields == 7); // Palauttaa tosi (1) vain jos kaikki 7 löytyi
}

void profitReport(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Tiedostoa ei voitu avata.\n");
        return;
    }

    Car *head = NULL;
    char line[linesize];
    int totalProfit = 0; // Vaatimus: Raportin on laskettava kokonaisvoitto

    while (fgets(line, sizeof(line), f)) {
        Car temp;
        if (parse_car_line(line, &temp)) {
            Car *new_node = (Car *)malloc(sizeof(Car));
            if (new_node != NULL) {
                *new_node = temp;

                // Lisätään kokonaisvoittoon (Vaatimus: laske yhteissumma)
                totalProfit += (new_node->sellingPrice - new_node->purchasePrice);

                // KÄYTETÄÄN JÄRJESTÄVÄÄ LISÄYSTÄ (Vaatimus: Descending order)
                addSortedByProfit(&head, new_node);
            }
        }
    }
    fclose(f);

    // TULOSTUS (Vaatimus: Aloita kokonaisvoitolla)
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
        free(temp_to_free); // PDF 12 s. 6: Muistin vapautus
    }
}

long date_to_index(const char *date_str) {
    int day, month, year;
    if (sscanf(date_str, "%d-%d-%d", &day, &month, &year) == 3) {
        return (year * 365L) + (month * 30L) + day;
    }
    return 0;
}



void add_sorted_by_time(Car **head, Car *new_node) {
    // Lasketaan uuden auton "myyntiaika" karkeasti vertailua varten
    // (vuosi * 365 + kuukausi * 30 + paiva) on tässä helpoin tapa saada luku,
    // jolla voi mitata erotusta.
    long new_diff = date_to_index(new_node->sellingDate) - date_to_index(new_node->purchaseDate);

    Car **ppn = head;
    while (*ppn != NULL) {
        long current_diff = date_to_index((*ppn)->sellingDate) - date_to_index((*ppn)->purchaseDate);

        // Järjestetään DESCENDING (suurin myyntiaika ensin)
        if (new_diff > current_diff) {
            break;
        }
        ppn = &((*ppn)->next);
    }
    new_node->next = *ppn;
    *ppn = new_node;
}

void sellTimeReport(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    Car *list_head = NULL;
    char line[linesize];
    int total_profit = 0;

    // 1. LUKEMINEN JA JÄRJESTÄMINEN
    while (fgets(line, sizeof(line), file)) {
        Car temp_data;
        if (parse_car_line(line, &temp_data)) {
            Car *new_car = malloc(sizeof(Car));
            if (new_car) {
                *new_car = temp_data;

                // Lasketaan kokonaisvoitto talteen (Vaatimus 3)
                total_profit += (new_car->sellingPrice - new_car->purchasePrice);

                // Tämä funktio hoitaa järjestämisen (Descending order)
                add_sorted_by_time(&list_head, new_car);
            }
        }
    }
    fclose(file);

    // 2. TULOSTUS
    // Tehtävä vaatii: "Both reports must start with the total profit made"
    printf("\n========================================");
    printf("\nREPORT: CARS SORTED BY SELL TIME");
    printf("\nTOTAL PROFIT MADE: %d EUR", total_profit);
    printf("\n========================================\n\n");

    // Otsikot (%-15s tekee tilaa tekstille, jotta sarakkeet pysyy suorassa)
    printf("%-15s %-15s %-15s %-10s\n", "MAKE", "MODEL", "TIME IN STOCK", "PROFIT");
    printf("------------------------------------------------------------------\n");

    Car *current = list_head;
    while (current != NULL) {
        // Lasketaan myyntiaika tulostusta varten
        long days = date_to_index(current->sellingDate) - date_to_index(current->purchaseDate);
        int profit = current->sellingPrice - current->purchasePrice;

        printf("%-15s %-15s %-10ld days    %-10d EUR\n",
               current->make,
               current->model,
               days,
               profit);

        // MUISTIN VAPAUTUS (Tärkeää PDF-materiaalin mukaan!)
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

    do {
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

    if (selection == 1)
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