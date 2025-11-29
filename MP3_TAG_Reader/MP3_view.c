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


//mp3_view() function definition to view .mp3 file contents.

void mp3_view(int argc, char *argv[])
{
	char *N[6] = {"Title", "Artist", "Album", "Year", "Content", "Comment"};

	//open file in read mode which is entered by user in command line as 3rd parameter(at index 2).
	//if user entered file is not present then NULL address will be returned to fp.
	//so if fp is NULL address, then error usage message and file not found is printed and then the program is terminated entirely.  

	FILE* fp = fopen(argv[2], "r");
	if(fp == NULL)
	{
		validate_args(1, argv, argc);
		printf("\n%s File is not present\n\n", argv[2]);
		exit(0);
	}


	//if user entered file is .mp3 file, then 3 characters are read from fp and stored in buffer.
	//if buffer string is equal to "ID3", then print it is a MP3 file.
	//else print error usage message and print error not mp3 file and then terminate the whole program.

	char buffer[4];
	fread(buffer, (sizeof(buffer)-1), 1, fp);
	buffer[3] = '\0';
	
	if((strcmp(buffer, "ID3")) == 0)
	{
		printf("\n%s is a MP3 file\n\n", argv[2]);
	}
	else
	{
		validate_args(1, argv, argc);
		printf("\nError, %s is not a MP3 file\n\n", argv[2]);
		exit(0);
	}

	printf("----------------------------------------------------------------------------------\n");
	printf("MP3 Tag Reader and Editor for ID3v2\n");
	printf("----------------------------------------------------------------------------------\n");


	//skip 7 characters of .mp3 file.

	fseek(fp, 7, SEEK_CUR);


	for(int i=0; i<6; i++)
	{
		printf("%s", N[i]);
		

		//reads 4 characters of .mp3 file and stores it in tag string.

		char tag[5];
		fread(tag, (sizeof(tag)-1), 1, fp);
		tag[4] = '\0';


		//4 bytes of size stored in .mp3 file is read as big endian and stores that data to size as big endian.
		//convert big endian to little endian using convert_BE_to_LE_or_LE_BE() function.

		int size;
		fread(&size, sizeof(int), 1, fp);

		convert_BE_to_LE_or_LE_to_BE(&size);


		//skip 3 bytes using fseek.

		fseek(fp, 3, SEEK_CUR);
		

		//reads each contents of length from zero to size minus 1 characters and stores it in content string.
		//then print that stored content string.
		
		char content[size];
		for(int j=0; j<(size - 1); j++)
		{
			fread(&content[j], sizeof(char), 1, fp);
		}
		content[size - 1] = '\0';

		printf("		:	%s\n", content);
	}
	printf("----------------------------------------------------------------------------------\n");

	
	//opened file fp is closed.

	fclose(fp);
}


//convert_BE_to_LE_or_LE_to_BE() function definition to convert big endian to little endian and vice versa.

void convert_BE_to_LE_or_LE_to_BE(int *size)
{
	//char* typecasted size address is initialised to char pointer ptr. 

        char *ptr = (char*)size;

	
	//i loop runs from 0 to 1(2 times).
	//swaping is done using char temp one byte by one byte.

        for(int i=0; i<2; i++)
        {
                char temp = ptr[i];
                ptr[i] = ptr[3 - i];
                ptr[3 - i] = temp;
        }
}


//validate_args() function definition to validate user command line input is valid or not.

int validate_args(int argc, char *argv[], int len)
{
	//if argc is 2, 3 or 5, then if condition is true else error usage message is printed and return 0.

	if(argc == 2 || argc == 3 || argc == 5)
	{
		//if argc is 2, then if condition is true.

		if(argc == 2)
        	{
			//if user entered command line input at index 1 is "--help", then print help message and return 0.
			//else print error usage message and return 0.

                	if(strcmp(argv[1], "--help") == 0)
                	{
                        	printf("\n----------------------------------------------------------------------------------\n");
                        	printf("usage: mp3tag -[taAyCc] \"value\" file1\n");
                        	printf("       mp3tag -v\n");
                        	printf("-t    Modifies a Title tag\n");
                        	printf("-a    Modifies an Artist tag\n");
                        	printf("-A    Modifies an Album tag\n");
                        	printf("-y    Modifies a Year tag\n");
                        	printf("-C    Modifies a Content tag\n");
                        	printf("-c    Modifies a Comment tag\n");
                        	printf("----------------------------------------------------------------------------------\n\n");
				return 0;
                	}
                	else
                	{
                        	validate_args(1, argv, len);
                        	return 0;
                	}
        	}

		//if argc is 3, then if condition is true.

		if(argc == 3)
        	{
			//if user entered command line input at index 1 is "-e", then print error usage message and return 0.

                	if(strcmp(argv[1], "-e") == 0)
                	{
				validate_args(1, argv, len);
                        	return 0;
                	}

			//if user entered command line input at index 1 is not "-v", then print error usage message and return 0.
	
			if(strcmp(argv[1], "-v") != 0)
			{
				validate_args(1, argv, len);
				return 0;
			}
		}

		//if argc is 5, then if condition is true.

		if(argc == 5)
                {
			//if user entered command line input at index 1 is not "-e", then print error usage message and return 0.

			if(strcmp(argv[1], "-e") != 0)
			{
				validate_args(1, argv, len);
				return 0;
			}

			//if user entered command line input at index 2 is not either of one input amomg - "-t"/"-a"/"-A"/"-y"/"-C"/"-c", then
			//print error usage message and return 1. 

                        if(strcmp(argv[2], "-t") && strcmp(argv[2], "-a") && strcmp(argv[2], "-A") && strcmp(argv[2], "-y") && strcmp(argv[2], "-C") && strcmp(argv[2], "-c"))
                        {
                                validate_args(1, argv, len);
                                return 1;
                        }
                }
		return 0;
	}

	printf("\n----------------------------------------------------------------------------------\n");
	printf("Error: ");
	for(int c=0; c<len; c++)
	{
		printf("%s ",argv[c]);
	}	
	printf(": INVALID ARGUMENTS\nUSAGE:\n");
	printf("To get help please pass like	:  ./a.out --help\n");
	printf("To view please pass like	:  ./a.out -v mp3filename\n");
	printf("To edit please pass like	:  ./a.out -e -t/-a/-A/-y/-C/-c \"value\" mp3filename\n");
	printf("----------------------------------------------------------------------------------\n\n");
	return 0;
}
