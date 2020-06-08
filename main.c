/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vuong van truong -He141617

 */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void spinning(int num[]) {
    int i;
    // This for loop loop 3 time
    // Each time assgn a random number to an array contains 3 random number
    for (i = 0; i < 3; i++)
        // Random number 0 -> 9
        num[i] = rand() % 10;
}

int isLucky(int luckyNum[]) {
    if (luckyNum[0] == luckyNum[1] && luckyNum[0] == luckyNum[2]) {
        return 3;
    } else if (luckyNum[0] == luckyNum[1] || luckyNum[1] == luckyNum[2] || luckyNum[0] == luckyNum[2]) {
        return 2;
    } else
        return 1;
}

void shows(int num[]) {
    int i;
    printf("The slot machine shows ");
    // This for loop loop 3 times
    // Each time print a Integer number from the array to console
    for (i = 0; i < 3; i++)
        printf("%d", num[i]);
    printf(" .\n");
}

int intInput(int min, int max) {
    int i, output, check;
    char ch;
    while (1) {
        // This line scan 2 variables integer and character to get out-buffer-flow values or wrong input
        // fflush(stdin); clear junk value and out-buffer-flow values
        check = scanf("%d%c", &output, &ch);
        fpurge(stdin);
        //fpurge(stdin);
        // If scanf get more than 2 input, return 2, if fail to get input return 0
        // If scanf did not normally enter right type (a integer and an "enter" - 10 (ASCII) character) --> Not Pass, return to consolse wrong input
        if (check != 2 || ch != 10)
            printf("Wrong input!\nTry again: ");
            // If value input out of default range --> Not Pass, return to consolse wrong input
        else if (output < min || output > max)
            printf("Outrange input!(%d-%d)\nTry again: ", min, max);
        else return output;
    }
}

void menu(float budget) {
    printf("You have $%g\n", budget);
    printf("Choose one of the following menu options:\n");
    printf("1. Play the Slot machine.\n");
    printf("2. Save game.\n");
    printf("3. Cash out.\n");
}

void push1coin(float *budget) {
    int randomDigit[3];
    spinning(randomDigit);
    // This line get the case of prize
    int slotcase = isLucky(randomDigit);
    shows(randomDigit);
    // The condition follow the slotcase
    // 3 - add 10 to the budget
    // 2 - add 0.5 to the budget
    // 1 - nothing
    if (slotcase == 3) {
        *budget += 10;
        printf("You win the big prize, $10.00!\n");
    } else if (slotcase == 2) {
        *budget += 0.5;
        printf("You win 50 cents!\n");
    } else
        printf("Sorry you don't win anything.\n");
}

float openFile(char filename[]) {
    float output;
    FILE *save;
    // File manipulation, read plus mode
    // read file, if file doesnt exist, return NULL to pointer
    save = fopen(filename, "r+");
    // If file doesn't exist, create new one
    if (save == NULL) {
        fclose(save);
        // write mode, create new file by source
        // assign a default value to file
        save = fopen(filename, "w+");
        fprintf(save, "%f", 10.00);
        fclose(save);
        // re-open file by read mode
        save = fopen(filename, "r");
    }
    // get the value in the file to output and return
    fscanf(save, "%f", &output);
    fclose(save);
    return output;
}

void saveFile(char filename[], float input) {
    remove(filename);
    FILE *save;
    save = fopen(filename, "w+");
    fprintf(save, "%f", input);
    fclose(save);
}
/*
void login(char name[]){
        printf("Enter your profile: ");
        gets(name);
        char fileExtension[] = ".txt";
        strcat(name, fileExtension);
}
 */
// Drive functions

int main(int argc, char** argv) {
    srand(time(NULL));
    int loop = 1; // loop condition

    char filename[20];
    //    login(filename);
    strcpy(filename, "profile1.txt");
    float budget = openFile(filename);
    // Initialize a infinity loop, the loop break when loop condition turn 0-false
    while (loop) {
        menu(budget);
        // When player broken(buget less or equal 0), remove profile user and end game.
        if (budget <= 0) {
            remove(filename);
            printf("Sorry, you're out of wallet!\nThankyou for playing, see you next time!");
            break;
        }

        int choice = intInput(1, 3);
        switch (choice) {
            case 1:
            {
                budget -= 0.25;
                push1coin(&budget);
                break;
            }
            case 2:
            {
                saveFile(filename, budget);
                printf("Your money had saved.\n");
                break;
            }
            case 3:
            {
                printf("Thankyou for playing! You end with $%g!", budget);
                loop = 0; //loop condition = 0 -> break the loop
                break;
            }
        }
    }

    return (EXIT_SUCCESS);
}

