/*
        Name            :       Ashith P Amin

        Date            :       28 / 10 / 2025

        Description     :       MP3 Tag Reader and Editor

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




#include "MP3_header.h"

int main(int argc, char *argv[])
{
	//argc value is copied to len.

        int len = argc;


        //validate_args() function is called.

        if(validate_args(argc, argv, len) == 1)
        {
                return 0;
        }


        if(argc == 1)
        {
                return 0;
        }


        //if argv[1] is "-v" and argc is 3, then if condition is true.
        //then inside if condition mp3_view() function is called.

        if(strcmp(argv[1], "-v") == 0 && argc == 3)
        {
                mp3_view(argc, argv);
        }


        //if argv[1] is "-e" and argc is 5, then if condition is true.
        //then inside if condition mp3_edit() funtion is called.

        if(strcmp(argv[1], "-e") == 0 && argc == 5)
        {
                mp3_edit(argc, argv);
        }


        return 0;
}
