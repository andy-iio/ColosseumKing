#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "training.h"  
#include "character.h" 
#include "gear.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int mainMenu() {
    int choice = 0;
    char input[MAXSIZE];
    STATSWITHCOLOR character;
    initializeCharacter(&character); // Initialize character attributes

    while (1) {
        do {
            printf("\033\n[1;31mMAIN MENU\n\033[0m");
            printf("1. New Game\n");
            printf("2. Load Game\n");
            printf("3. Buy Armor Set\n");
            printf("4. Training\n");
            printf("5. Settings\n");
            printf("6. Exit Game\n");
            printf("\nEnter your choice: ");

            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) > 1 || sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 6) {
                printf("\033[31mInvalid choice. Please enter a valid option (1-4).\n\033[0m");
                printf("****************************");
            }
        } while (choice < 1 || choice > 6);

        switch (choice) {
        case 1:
            printf("\033[1;31mStarting New Game...\n\033[0m");
            printf("****************************\n");
            printf("\033[1;31mTRAINING\n\033[0m");
            startTraining();  // Start the training module
            clearInputBuffer();
            return 0;
        case 2:
            if (loadGameMenu() == 0) {
                return 0; // Exit mainMenu after successful load
            }
            break;
        case 3:
            buyGear(&character);
            clearInputBuffer();
            break;
        case 4:
            trainingMenu();
            clearInputBuffer();
            break;
        case 5:
            if (settingsMenu() == 'c') {
                clearInputBuffer();
                continue; // Return to main menu
            }
            break;
        case 6:
            exitGameMenu();
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }
}

int loadGameMenu() {
    char filename[MAXSIZE];
    char input[MAXSIZE];
    int choice = 0;
    int count = 0;

    FILE* fp = fopen("save_files.txt", "r");
    if (fp == NULL) {
        printf("No save files found.\n");
        return 1;
    }

    printf("****************************\n");
    printf("\033[1;31mLOAD GAME\n\033[0m");

    // Read the save files and display them as menu options
    while (fgets(filename, sizeof(filename), fp)) {
        printf("%d. %s", ++count, filename);
    }
    fclose(fp);

    if (count == 0) {
        printf("No save files available.\n");
        return 1;
    }

    // Prompt the user to choose a file to load
    printf("\nEnter the number of the save file to load: ");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("\033[31mInvalid choice. Please enter a valid save file number (1-%d).\n\033[0m", count);
        return 1;
    }

    // Reopen the file to get the chosen save file
    fp = fopen("save_files.txt", "r");
    if (fp == NULL) {
        printf("Error reopening save files.\n");
        return 1;
    }

    count = 0;
    while (fgets(filename, sizeof(filename), fp)) {
        if (++count == choice) {
            printf("Loading save file: %s\n", filename);
            break;
        }
    }
    fclose(fp);
    inGameLoop();
    return 0;
}

char settingsMenu() {
    char subChoice;
    char input[MAXSIZE];

    while (1) {
        printf("****************************");
        printf("\n\033[1;31mSETTINGS\n\033[0m");
        printf("a) Sound\n");
        printf("b) How to Play\n");
        printf("c) Back to Menu\n");
        printf("\nEnter your choice: ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) != 1 || (input[0] != 'a' && input[0] != 'b' && input[0] != 'c')) {
            printf("\033[31mInvalid choice. Please enter 'a', 'b', or 'c'.\n\033[0m");
            continue;
        }

        subChoice = input[0];
        switch (subChoice) {
        case 'a':
            printf("\nSound settings...\n");
            break;
        case 'b':
            printf("\nHow to Play...\n");
            break;
        case 'c':
            printf("\n\033[1;34mReturning to menu...\n\033[0m");
            printf("****************************\n");
            return;
        }
    }
}

void exitGameMenu() {
    char subChoice;
    char input[MAXSIZE];

    while (1) {
        printf("a) Save and Exit\n");
        printf("b) Exit Game\n");
        printf("c) Cancel\n");
        printf("\nEnter your choice: ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) != 1 || (input[0] != 'a' && input[0] != 'b' && input[0] != 'c')) {
            printf("\033[31mInvalid choice. Please enter 'a', 'b', or 'c'.\n\033[0m");
            printf("****************************\n");
            continue;
        }

        subChoice = input[0];
        switch (subChoice) {
        case 'a':
            printf("\033[1;31mSaving and exiting game...\n\033[0m");
            exit(0);
        case 'b':
            printf("\033[1;31mExiting game...\n\033[0m");
            exit(0);
        case 'c':
            printf("Returning to menu...\n");
            printf("****************************");
            return;
        }
    }
}

int inGameMenu() {
    int choice;

    while (1) {
        printf("\033[1;31mIN GAME MENU\n\033[0m");
        printf("1. Save Game\n");
        printf("2. Settings\n");
        printf("3. Return Main Menu\n");
        printf("4. Exit Game\n");
        printf("\nEnter your choice: ");
        scanf(" %d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1:
            printf("Saving game...\n");
            // Save file function here
            break;
        case 2:
            settingsMenu();
            break;
        case 3:
            printf("\n\033[1;34mExiting game and returning to main menu...\n\033[0m");
            printf("****************************");
            mainMenu();
            break;
        case 4:
            exitGameMenu();
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }
}

void inGameLoop() {
    int ch;

    while (1) {
        printf("\033[1;36mGame running... Press ESC to open menu.\n\033[0m");
        ch = getch(); // Wait for a key press

        if (ch == 27) { // 27 is the ASCII value of the ESC key
            printf("****************************\n");
            inGameMenu();
        }
    }
}