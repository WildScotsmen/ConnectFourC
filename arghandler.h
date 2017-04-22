#ifndef ARG_HANDLER
#define ARG_HANDLER
#include <argp.h>

/************************************************************************************
* @author Scoots
* @version 3/03/2017
* @see argp.h
*
* My implementation for argp. Will handle arguments for the Connect Four game.
*************************************************************************************/

/*
* Saved width board parameter.
*/
int wid;

/*
* Saved height board parameter.
*/
int hei;

/*
* Saved square board parameter.
*/
int sqr;

/*
* Saved win length parameter.
*/
int winlen;

/*
* Saved filename for loading.
*/
char* loadFile;

/*
* Argument values for flags.
*/
struct arguments {
	int width;
	int height;
	int square;
	int winL;
	char* loadFile;
};

/*
* Function that sets up values post-parsing.
*/
error_t parse_opt(int key, char* arg, struct argp_state *state);

/*
* Parses arguments.
*/
void setup(int argc, char** argv);

#endif
