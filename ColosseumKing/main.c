//ColosseumKing
//Andy Guest | Alexa Bowman | Ceren Askin | Grae Watson

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // for srand()
#include <time.h> // to use time for srand()
#include "menu.h"
#include "training.h"
//all our modules, rename yours if you want to
#include "character.h"
//#include "menu.h"
//#include "attack.h"
//#include "training.h"
//#include "fileManagement.h"

int main(void) {

	//char filename[] = "ascii-art.txt";
	char filename[] = "ascii.txt";

	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		printf("Could not open file: %s\n", filename);
		return 1;
	}
	char ch;

	while ((ch = fgetc(file)) != EOF) {
		putchar(ch);
	}

	fclose(file);
	mainMenu();
	inGameLoop(); // Start the game and run the game loop

	srand(time(NULL)); //seeding the random number generator used in character module

	//-------------------------------------------
	//temporary testing for character module, I will remove later, feel free to comment it out -andy
	struct Player player1;
	struct Enemy zorb;

	loadPlayer(&player1, "abcde", 50, 70, 80, 90, 100, 1);
	initializeEnemy(&zorb, MONSTER);
	printf("player health: %d enemy health: %d\n", player1.health, zorb.health);
	player1.health++;
	zorb.health++;
	printf("player health: %d enemy health: %d\n", player1.health, zorb.health);
	player1.health--;
	zorb.health--;
	printf("player health: %d enemy health: %d\n", player1.health, zorb.health);
	randomHealthIncrease(&player1);
	printf("player health: %d enemy health: %d\n", player1.health, zorb.health);
	//end of character module temmporary testing
	//-------------------------------------------


	return 0;
}
