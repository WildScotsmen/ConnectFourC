#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamelogic.h"
#include "arghandler.h"

/************************************************************************************
* @author Jacob McCloughan
* @version 3/03/2017
* @see gamelogic.h
* @see arghandler.h
*
* Includes the main method for our Connect Four game. Uses <argp.h> to handle
* command line arguments.
*
* This post taught me how to use colored text in Linux.
* http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
*************************************************************************************/

/*
* Main method for the Connect Four game. Uses all of the functions from the
* game logic file and allows the player to play the game.
*
* @param argc, number of command line arguments.
* @param argv, the command line arguments.
* @return 0 if the operation failed and 1 if it succeeded.
*/
int main(int argc, char** argv) {
	// Variables and array setup
	char* input = malloc(100 * sizeof(char));
	int player = 1;
	setup(argc, argv);

	// Fixes invalid height or width arguments
	if (hei <= 0 || hei > 2147483647 || wid <= 0 || wid > 2147483647) {
		setHeight(7);
		setWidth(7);
	}
	else {
		setHeight(hei);
		setWidth(wid);
	}

	// Fixes invalid win length arguments
	if (winlen <= 0 || winlen > 2147483647) {
		setWinLength(4);
	}
	else {
		setWinLength(winlen);
	}
	
	// Fixes invalid square dimension arguments
	if (sqr > 0 && sqr <= 2147483647) {
		setHeight(sqr);
		setWidth(sqr);
	}

	// Either starts new game or loads from argument
	printf("%sWelcome to Connect Four!\nType 'save' to save, 'load' to load, and 'quit' to quit.\n%s", "\x1B[32m", "\033[0m");
	if (loadFile != NULL) {
		if (loadGame(loadFile) == 0) {
			printf("\nInvalid file.\n");
			return 0;
		}
		printBoard();
	} else {
		populateBoard();
		printBoard();
	}

	// While loop for the game logic
	while (1) {
		// Checks if player 1 has won
		if (checkWin('o') == 1) {
			printf("Player 1 wins!\n");
			printf("Would you like to play again? Type 'yes' for yes or 'no' for no.\n");
			while (1) {
				scanf("%s", input);
				if ((strcmp("yes", input) == 0)) {
					printf("\n");
					populateBoard();
					player = 1;
					printBoard();
					break;
				} 
				if ((strcmp("no", input) == 0)) {
					printf("\n");
					return 1;
				} else {
					printf("Invalid input.\n");
					continue;
				}
			}	
		}
		
		// Checks if player 2 has won
		if (checkWin('x') == 1) {
			printf("Player 2 wins!\n");
			printf("Would you like to play again? Type 'yes' for yes or 'no' for no.\n");
			while (1) {
				scanf("%s", input);
				if ((strcmp("yes", input) == 0)) {
					populateBoard();
					player = 1;
					printBoard();
					printf("\n");
					break;
				} if ((strcmp("no", input) == 0)) {
					return 1;
				} else {
					printf("Invalid input.\n");
					continue;
				}
			}
		}

		// User input
		printf("\nPlayer %d's turn.\n", player);
		printf("Input a column (from 1 to %d) to place a token:\n", width);
		scanf("%s", input);
		
		// For quitting
		if (strcmp("quit", input) == 0) {
			return 1;
		}

		// Saving functionality
		if (strcmp("save", input) == 0) {
			printf("Input a filename:\n");
			scanf("%s", input);
			saveGame(input);
			printf("Game saved.\n");
			continue;
		}

		// Loading functionality
		if (strcmp("load", input) == 0) {
			printf("Input a filename:\n");
			scanf("%s", input);
			if (loadGame(loadFile) == 0) {
				printf("\nInvalid file.\n");
				continue;
			} else {
				printBoard();
				printf("\nGame loaded.\n");
				continue;
			}
		}

		// Checks to make sure input is valid
		if (atoi(input) < 1 || atoi(input) > width) {
			printf("Invalid input. Input another column:\n");
			continue;
		}
		
		// Checks to make sure input is valid
		if (placeChip(atoi(input) - 1, player) == 0) {
			printf("Invalid input. Input another column:\n");
		} else {
			if (player == 1) {
				player = 2;
			}
			else {
				player = 1;
			}
			printBoard();
		}
	}
	
	return 1;
}
