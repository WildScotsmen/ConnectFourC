#ifndef FILE_UTILS
#define FILE_UTILS

/************************************************************************************
* @author Jacob McCloughan
* @version 3/03/2017
*
* Header file for file utilities for reading in a file to an array and then
* writing that file backwards to another file.
*************************************************************************************/

/*
* Reads the .txt file passed as a parameter into the array (buffer)
* pointed to as a parameter.
*
* @param filename, the name of the .txt file being read from.
* @param buffer, a pointer to the array that will have the data read in.
* @return 0 if the operation failed and the number of bytes if it succeeded.
*/
int read_file(char* filename, char** buffer);

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
int write_file(char* filename, char* buffer, int size);

#endif
