#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file_utils.h"

/************************************************************************************
* @author Jacob McCloughan
* @version 3/03/2017
* @see file_utils.h
*
* Implementation for file_utils.h. Contains functions
* for reading from a file and putting it into a selected array
* and for writing the array backwards into a selected file.
*
* This post taught me everything I now know about files in C:
* http://stackoverflow.com/questions/22697407/reading-text-file-into-char-array
*************************************************************************************/

/*
* Reads the .txt file passed as a parameter into the array (buffer)
* pointed to as a parameter.
*
* @param filename, the name of the .txt file being read from.
* @param buffer, a pointer to the array that will have the data read in.
* @return 0 if the operation failed and the number of bytes if it succeeded.
*/
int read_file(char* filename, char **buffer) {
	// Variables. The stat struct is from Professor Woodring.
	FILE *fil;
	struct stat st;
	stat(filename, &st);
	int size = st.st_size;

	// Opens up the file for extracting the data. If statement is for error-checking.
	fil = fopen(filename, "r");
	if (!fil) {
		fprintf(stderr, "Unable to read file.");
		return 0;
	}

	// Creates the space for our array. If statement is for error-checking.
	*buffer = malloc((size) * sizeof(char));
	if (!*buffer) {
		fprintf(stderr, "Unable to allocate memory.");
		fclose(fil);
		return 0;
	}

	/* Reads the data into our array. If statement is for error-checking, but it also contains the 
	command that reads in the data. */
	if (fread(*buffer, size, 1, fil) != 1) {
		fprintf(stderr, "Error copying file to memory.");
		fclose(fil);
		return 0;
	}

	// Closes the file and returns the size of the array.
	fclose(fil);
	return size;
}

/*
* Writes to the filename passed as a parameter from the array (buffer)
* passed as a parameter. The size of the array must be specified.
*
* @param filename, the name of the .txt file being written to.
* @param buffer, the array that the data is being written from.
* @param size, the size of the array. If read in properly by the read_file 
* function, this should have been returned.
* @return 0 if the operation failed and 1 if it succeeded.
*/
int write_file(char* filename, char *buffer, int size) {
	// File being operated on.
	FILE *fil;

	// Opens up the file for printing the data. If statement is for error-checking.
	fil = fopen(filename, "w");
	if (!fil) {
		fprintf(stderr, "Unable to write to that file.");
		fclose(fil);
		return 0;
	}

	/* Iterates through the buffer passed and prints it backwards to a text file. 
	If statement is for error-checking, but it also contains the command that writes the data. */
	for (int i = 0; i < size; i++) {
		if (fprintf(fil, "%c", buffer[i]) != 1) {
			fprintf(stderr, "Error when writing to file.");
			fclose(fil);
			return 0;
		}
	}

	// Closes the file and returns 1.
	fclose(fil);
	return 1;
}