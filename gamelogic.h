#ifndef GAME_LOGIC
#define GAME_LOGIC

/************************************************************************************
* @author Jacob McCloughan
* @version 3/03/2017
*
* Header file for the Connect Four game logic.
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
int setHeight(int h);

/*
* Sets the board width to the parameter passed.
*
* @param w, the board width to be set to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int setWidth(int w);

/*
* Sets the win length to the parameter passed.
*
* @param l, the win length to be set to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int setWinLength(int l);

/*
* Prints the current state of the board to the terminal.
*
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int printBoard();

/*
* Resets the board with the current board parameters.
*
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int populateBoard();

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
int placeChip(int col, int p);

/*
* Saves the current game. Puts the game's state into
* a text file so that it can be loaded later on.
*
* @param filename, the name of the file to be saved to.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int saveGame(char* filename);

/*
* Loads a previous game. Reloads a previous game's
* state from a text file so that a past game can be
* continued.
*
* @param filename, the name of the file to be loaded from.
* @return 0 if the operation failed, and 1 if the operation
* succeeded.
*/
int loadGame(char* filename);

/*
* Checks if the current state of the board is a victory
* for the player token passed as a parameter.
*
* @param p, the player token being checked for.
* @return 0 if the player passed has not won, and 1 if the
* player passed has won.
*/
int checkWin(char p);

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
int modifyPostition(int row, int col, char c);

#endif