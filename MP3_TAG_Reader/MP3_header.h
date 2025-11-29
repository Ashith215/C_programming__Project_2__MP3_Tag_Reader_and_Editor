/*
	Name		:	Ashith P Amin

	Date		:	28 / 10 / 2025

	Description	:	MP3 Tag Reader and Editor

				1. Validating command line input.
					-> print help message, if argc is 2 and argv[1] is "--help".
					-> print error usage message, if argc is 2 and argv[1] is not "--help".
					-> print error usage message, if argc is 3 and argv[1] is not "-v".
					-> print error usage message, if argc is 5 and argv[1] is not "-e".
					-> print error usage message, if argc is 1, 4 or greater than 5.
					-> print error usage message, if argc is 3 and argv[1] is "-e". 
					-> or also print error usage message, if argc is 5 and argv[1] is not "-t/-a/-A/-y/-C/-c". 
				2. View .mp3 file contents.
					-> if input file is not present, then print file is not present.
					-> if input file is present, then check is the file .mp3 or not and if not then print not mp3 file message.
					-> if input file is a .mp3 file then print the contents of the same file.
				3. Edit .mp3 file contents.
					-> if input file is not present, then print file is not present.
					-> if input file is present, then check is the file .mp3 or not and if not then print not mp3 file message.
					-> if input file is a .mp3 file, then replace the choosen content of .mp3 file with user entered value.
*/



#ifndef MP3_header_h
#define MP3_header_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




//All used function prototypes.

int validate_args(int, char *[], int);
void mp3_view(int, char *[]);
void mp3_edit(int, char *[]);
void convert_BE_to_LE_or_LE_to_BE(int *);
void print_edit_option(int, char*[]);




#endif
