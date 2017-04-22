#include <stdio.h>
#include <stdlib.h>
#include "arghandler.h"

/************************************************************************************
* @author Scoots
* @version 3/03/2017
* @see arghandler.h
*
* My implementation for argp. Handles arguments for the Connect Four game.
*************************************************************************************/

/*
* Program version.
*/
const char *argp_program_version = "Connect Four (Version 3/03/2017)";

/*
* My email address for bug reports.
*/
const char *argp_program_bug_address = "mcclougj@mail.gvsu.edu";

/*
* Game description.
*/
char doc[] = "Connect Four: Game where you place tokens until a player connects four!";

/*
* Accepted arguments. Unused, but defined.
*/
char args_doc[] = "";

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

struct argp_option options[] = {
	{ "width",	'w',	"WIDTH",	0,	"Width dimension for board." },
	{ "height",	'h',	"HEIGHT",	0,	"Height dimension for board." },
	{ "square",	's',	"SQUARE",	0,	"Dimensions for a square board (width and height will be overrided)." },
	{ "connect", 'c',	"CONNECT",	0,	"Length to win the game." },
	{ "load",	'l',	"LOAD", 	0, 	"Load a previous saved game." },
	{ 0 }
};

/*
* Required arguments for the argp struct.
*/
struct argp argp = { options, parse_opt, args_doc, doc };

/*
* Argument values for flags.
*/
struct arguments arguments;

/*
* Function that sets up values post-parsing.
*
* @param key, the key of the argument.
* @param arg, the argument being passed.
* @param state, the state of parser.
*/
error_t parse_opt(int key, char* arg, struct argp_state *state) {
	struct arguments *arguments = state->input;
	switch (key) {
	case 'w':
		arguments->width = atoi(arg);
		break;
	case 'h':
		arguments->height = atoi(arg);
		break;
	case 's':
		arguments->square = atoi(arg);
		break;
	case 'c':
		arguments->winL = atoi(arg);
		break;
	case 'l':
		arguments->loadFile = arg;
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/*
* Parses arguments.
* @param argc, number of command line arguments.
* @param argv, the command line arguments.
*/
void setup(int argc, char** argv) {
	wid= 0;
	hei= 0;
	sqr = 0;
	winlen = 0;
	loadFile = NULL;

	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	wid = arguments.width;
	hei = arguments.height;
	sqr = arguments.square;
	winlen = arguments.winL;
	
	if (arguments.loadFile != NULL) {
		loadFile = arguments.loadFile;
	}
}
