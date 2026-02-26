//
// Created by eetul on 25.2.2026.
//
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define namesize 30
#define maxlength 80
#define maxlines 100

int main(void) {
    FILE *myfile;
    char filename[namesize];
    char lines[maxlines][maxlength];
    int count = 0;


    printf("Enter filename: ");
    fgets(filename,namesize,stdin);
    filename[strcspn(filename,"\n")] = '\0';

    myfile = fopen(filename,"r");

    if (myfile == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
    }
    else {
        while (count < maxlines && fgets(lines[count],maxlength,myfile) != NULL) {
            count++;
        }
    }
    fclose(myfile);

    for (int i = 0; i < count; i++) {
        for (int j = 0; lines[i][j] != '\0'; j++) {
            lines[i][j] = toupper(lines[i][j]);
        }
    }
    myfile = fopen(filename,"w");
    if (myfile == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(myfile, "%s", lines[i]);
    }
    fclose(myfile);
    return 0;
}