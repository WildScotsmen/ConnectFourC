#include <stdio.h>
#include <stdlib.h>
#include "gamelogic.h"
#include "file_utils.h"
#include <string.h>

/************************************************************************************
* @author Jacob McCloughan
* @version 3/03/2017
* @see gamelogic.h
*
* Implementation for the Connect Four game logic. Includes all of the functions
* for operating the game and the variables for storing the game's state.
* 
* This post taught me how to use colored text in Linux.
* http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
*************************************************************************************/

/*
* Doubly array that will store the game board.
*/
char** gameBoard;

/*
* Height of the game board.
*/
int height;

/*
* Width of the game board.
*/
int width;

/*
* Length to win the game.
*/
int winLength;

/*
* Sets the board height to the parameter passed.
*
* @param h, the board height to be set to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int setHeight(int h) {
	height = h;
	return 1;
}

/*
* Sets the board width to the parameter passed.
*
* @param w, the board width to be set to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int setWidth(int w) {
	width = w;
	return 1;
}

/*
* Sets the win length to the parameter passed.
*
* @param l, the win length to be set to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int setWinLength(int l) {
	winLength = l;
	return 1;
}

/*
* Prints the current state of the board to the terminal.
*
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int printBoard() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (gameBoard[i][j] == 'o') {
			printf("\x1b[34m%c\x1b[0m", gameBoard[i][j]);
			} else if (gameBoard[i][j] == 'x') {
			printf("\x1b[31m%c\x1b[0m", gameBoard[i][j]);
			} else {
			printf("%c", gameBoard[i][j]);
			}
		}
		printf("\n");
	}
	
	return 1;
}

/*
* Resets the board with the current board parameters.
*
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int populateBoard() {
	gameBoard = malloc(sizeof(char*) * height);
	for (int i = 0; i < height; i++) {
		gameBoard[i] = malloc(sizeof(char) * width);
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			gameBoard[i][j] = '*';
		}
	}
	
	return 1;
}

/*
* Places a chip in the desired column. Designed to emulate
* putting a chip into a column in the actual game of Connect
* Four.
*
* @param col, the desired column.
* @param p, the player placing the chip.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int placeChip(int col, int p) {
	// Handles bad arguments
	if (col > width - 1 || col < 0) {
		return 0;
	}

	// Checks to make sure the move is valid and places if so
	for (int i = height - 1; i >= 0; i--) {
		if (i > 0 && (gameBoard[i][col] == 'o' || gameBoard[i][col] == 'x')) {
			continue;
		}
		else if (i == 0 && gameBoard[i][col] != '*') {
			return 0;
		}
		else {
			if (p == 1) {
				gameBoard[i][col] = 'o';
			}
			if (p == 2) {
				gameBoard[i][col] = 'x';
			}
			break;
		}
	}

	return 1;
}

/*
* Saves the current game. Puts the game's state into 
* a text file so that it can be loaded later on.
*
* @param filename, the name of the file to be saved to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int saveGame(char* filename) {
	// Variables and character array setup
	char* buffer;
	int count = 33;
	buffer = malloc((sizeof(char) * width * height) + (33 * sizeof(char)));
	char* widthVal = malloc(10 * sizeof(char));
	char* heightVal = malloc(10 * sizeof(char));
	char* winVal = malloc(10 * sizeof(char));
	
	// Stores board parameter and win length as strings
	sprintf(widthVal, "%010d", width);
	sprintf(heightVal, "%010d", height);
	sprintf(winVal, "%010d", winLength);
	
	/* Copies the board parameters and win length character
	by character to the buffer to be saved to memory */
	buffer[0] = widthVal[0];
	buffer[1] = widthVal[1];
	buffer[2] = widthVal[2];
	buffer[3] = widthVal[3];
	buffer[4] = widthVal[4];
	buffer[5] = widthVal[5];
	buffer[6] = widthVal[6];
	buffer[7] = widthVal[7];
	buffer[8] = widthVal[8];
	buffer[9] = widthVal[9];
	buffer[10] = '\n';
	buffer[11] = heightVal[0];
	buffer[12] = heightVal[1];
	buffer[13] = heightVal[2];
	buffer[14] = heightVal[3];
	buffer[15] = heightVal[4];
	buffer[16] = heightVal[5];
	buffer[17] = heightVal[6];
	buffer[18] = heightVal[7];
	buffer[19] = heightVal[8];
	buffer[20] = heightVal[9];
	buffer[21] = '\n';
	buffer[22] = winVal[0];
	buffer[23] = winVal[1];
	buffer[24] = winVal[2];
	buffer[25] = winVal[3];
	buffer[26] = winVal[4];
	buffer[27] = winVal[5];
	buffer[28] = winVal[6];
	buffer[29] = winVal[7];
	buffer[30] = winVal[8];
	buffer[31] = winVal[9];
	buffer[32] = '\n';

	// Saves the state of the board to the buffer
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			buffer[count] = gameBoard[i][j];
			count++;
		}
		if (count >(width * height + 32)) {
			break;
		}
	}

	count = 0;

	// Writes the buffer into memory.
	write_file(filename, buffer, (sizeof(char) * width * height) + (33 * sizeof(char)));

	return 1;
}

/*
* Loads a previous game. Reloads a previous game's
* state from a text file so that a past game can be
* continued.
*
* @param filename, the name of the file to be loaded from.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int loadGame(char* filename) {
	// Variables
	char* buffer;
	int count = 33;
	char* sub;
	
	// Reads in the previous game to memory
	if (read_file(filename, &buffer) == 0) {
		return 0;
	}

	// Copies the board and victory data
	sub = malloc(10 * sizeof(char));
	strncpy(sub, buffer, 10);
	setWidth(atoi(sub));
	strncpy(sub, buffer + 11, 10);
	setHeight(atoi(sub));
	strncpy(sub, buffer + 22, 10);
	setWinLength(atoi(sub));

	// Resets board with new board parameters
	populateBoard();

	// Copies past game's state to board.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			gameBoard[i][j] = buffer[count];
			count++;
		}
	}

	return 1;
}

/*
* Checks if the current state of the board is a victory
* for the player token passed as a parameter.
*
* @param p, the player token being checked for.
* @return 0 if the player passed has not won, and 1 if the 
* player passed has won.
*/
int checkWin(char p) {
	// Variables for the diagonal check algorithm
	int row = 0;
	int col = 0;
	
	// Handles 1 by 1 boards
	if (height == 1 && width == 1 && winLength == 1 ) {
		if (gameBoard[0][0] == p) {
			return 1;
		}
		else {
			return 0;
		}
	}
	
	
	// Checks horizontally
	int count = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (gameBoard[i][j] == p) {
				count++;
			} else {
				count = 0;
			}
			if (count == winLength) {
				return 1;
			}
		}
		count = 0;
	}

	// Checks vertically
	count = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (gameBoard[j][i] == p) {
				count++;
			} else {
				count = 0;
			}
			if (count == winLength) {
				return 1;
			}
		}
		count = 0;
	}
	
	// Checks negative slope diagonal
	count = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			row = i;
			col = j;
			count = 0;
			while (row < height && col < width) {
				if (gameBoard[row][col] == p) {
					count++;
					row++;
					col++;
				} else {
					row++;
					col++;
					count = 0;
				}
				if (count == winLength) {
					return 1;
				}
			}
		}
	}
	
	// Checks positive slope diagonal
	count = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			row = i;
			col = j;
			count = 0;
			while (row >= 0 && col < width) {
				if (gameBoard[row][col] == p) {
					count++;
					row--;
					col++;
				} else {
					row--;
					col++;
					count = 0;
				}
				if (count == winLength) {
					return 1;
				}
			}
		}
	}
	
	return 0;
}

/*
* Modifies the position passed on the board to whatever
* character is passed. Mostly used for testing.
*
* @param row, the row of the position.
* @param col, the column of the position.
* @param c, the character that the position will be set to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int modifyPostition(int row, int col, char c) {
	gameBoard[row][col] = c;
	return 1;
}
