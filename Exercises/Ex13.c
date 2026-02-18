//
// Created by eetul on 2026-02-17.
//
#include <stdio.h>
#include <string.h>

#define namesize 20
#define linesize 80

int main(void)
{
    FILE *myfile;
    char filename[namesize];
    char line[linesize];
    int value;
    int min, max;
    int count = 0;


    printf("Enter filename: ");
    fgets(filename,namesize,stdin);
    filename[ strcspn(filename, "\n") ] = '\0';

    myfile = fopen(filename,"r");

    if (myfile == NULL)
    {
        fprintf(stderr,"Error opening file %s\n",filename);
        return 1;
    }
    while (fgets(line, linesize, myfile) != NULL)
    {
        if (fscanf(myfile, "%d", &value) == 1) {
            printf("%d\n", value);

            if (count == 0)
            {
                min = max = value;
            }
            else
            {
                if (value < min) min = value;
                if (value > max) max = value;
            }
            count++;
    }


        }
    fclose(myfile);

    if (count == 0)
    {
        printf("No integers found from this file.\n");
    } else
    {
        printf("Count is: %d integers\n", count);
        printf("Lowest number is: %d\n", min);
        printf("Largest number is: %d\n", max);
    }
}