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




//MP3_header.h file is included here.

#include "MP3_header.h"


//mp3_edit() function definition to edit .mp3 file contents.

void mp3_edit(int argc, char* argv[])
{
	char* t[6] = {"-t", "-a", "-A", "-y", "-C", "-c"};
	char* tags[6] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};


	int ret, index;
	for(int i=0; i<6; i++)
	{
		ret = strcmp(argv[2], t[i]);
		if(ret == 0)
		{
			index = i;
			break;
		}
	}


	int l = strlen(argv[3]);
	

	//open temp.mp3 file in read mode and initialise its address to file pointer fp1.
	//open file in read mode which is entered by user in command line as 5rd parameter(at index 4) and initialise its address to file pointer fp2.
        //if user entered file fp2 is not present then NULL address will be returned to fp2.
        //so if fp2 is NULL address, then error usage message and file not found is printed and then remove temp.mp3 file.
	//And then program is terminated entirely.

	FILE* fp1 = fopen("temp.mp3", "w");
	FILE* fp2 = fopen(argv[4], "r");

	if(fp2 == NULL)
	{
		validate_args(1, argv, argc);
		printf("\n%s file is not present\n\n", argv[4]);
		remove("temp.mp3");
		exit(0);
	}


	//if user entered file is .mp3 file, then 3 characters are read from fp2 and stored in buffer.
        //if buffer string is not equal to "ID3", then print error usage message by calling validate_args() function.
        //And then print error it is not mp3 file, then remove temp.mp3 file and then terminate the whole program.

	char buffer[4];
	fread(buffer, (sizeof(buffer) - 1), 1, fp2);
	buffer[3] = '\0';

	if(!((strcmp(buffer, "ID3")) == 0))
        {
		validate_args(1, argv, argc);
                printf("\nError, %s is not a MP3 file\n\n", argv[4]);
                remove("temp.mp3");
		exit(0);
        }

	//then write buffer string to fp1 pointing .mp3 file. 

	fwrite(buffer, (sizeof(buffer) - 1), 1, fp1);
	

	//reads 7 characters of fp2 file and stores it in buffer2 string.
	//and writes that buffer into fp1 file.

	char buffer2[8];
	fread(buffer2, (sizeof(buffer2) - 1), 1, fp2);
	buffer2[7] = '\0';
	fwrite(buffer2, (sizeof(buffer2) - 1), 1, fp1);


	for(int i=0; i<6; i++)
	{
		int flag = 0;
		
		//reads 4 characters of fp2 file and stores it in tag string.

		char tag[5];
		fread(tag, (sizeof(tag) - 1), 1, fp2);
		tag[4] = '\0';

		//tag string is compared with user entered command line input at index 2.
		//if both are equal then flag value is updated to 1.

		char input_tag[5];
		strcpy(input_tag, tags[index]);
		input_tag[4] = '\0';
		if(strcmp(tag, input_tag) == 0)
		{
			flag = 1;
		}

		//writes tag string to fp1.

		fwrite(tag, (sizeof(tag) - 1), 1, fp1);

		
		//reads 4 bytes from fp2 which is size and stored in size as big endian.
		//if flag is 1, then l value is incremented by 1 since size is including null character.
		//then l value is converted to big endian, then this is written in fp1 pointing file. 
		//if flag is not 1, then directly size which is in big endian is written in fp1 pointing file. 

		int size;
		fread(&size, sizeof(int), 1, fp2);
		if(flag == 1)
		{
			l = l + 1;
			convert_BE_to_LE_or_LE_to_BE(&l);
			fwrite(&l, sizeof(int), 1, fp1);
		}
		else
		{
			fwrite(&size, sizeof(int), 1, fp1);
		}


		//reads 3 characters of fp2 file and stores it in flag_null string.
		//then writes flag_null string excluding null character into fp1 pointing file.

		char flag_null[4];
		fread(flag_null, (sizeof(flag_null) - 1), 1, fp2);
		flag_null[3] = '\0';
		fwrite(flag_null, (sizeof(flag_null) - 1), 1, fp1);

		
		//converts size value from big endian to little endian.

		convert_BE_to_LE_or_LE_to_BE(&size);
		

		//if flag is 1, then new user entered command line input at index 3 is replace in place of content of matching tag.
		//so, this 3rd index value which is copied to new_content is written in fp1 pointing file.
		//else if flag is not 1, then content is of size from zero to size minus 1 characters are read from fp2 and stored in char content.
		//and character by character of content is written in fp1 pointing file.  

		if(flag == 1)
		{
			convert_BE_to_LE_or_LE_to_BE(&l);

			char new_content[l];
			strcpy(new_content, argv[3]);
			new_content[l - 1] = '\0';
			
			fwrite(new_content, (sizeof(new_content) - 1), 1, fp1);

			fseek(fp2, (size - 1), SEEK_CUR);
		}
		else
		{
			char content;
			for(int j=0; j<(size - 1); j++)
			{
				fread(&content, sizeof(char), 1, fp2);
				fwrite(&content, sizeof(char), 1, fp1);
			}
		}
	}


	//fp2 position after content is stored in cur_pos.
	//then by using fseek, cursor in fp2 is moved to last character of file.
	//then position of end character is stored in end_pos.
	//then fp2 is rewinded that is, cursor is moved to starting position of the file f2.
	//then by using fseek, cursor is moved to cur_pos value position. 

	int cur_pos = ftell(fp2);

	fseek(fp2, cur_pos, SEEK_END);
	int end_pos = ftell(fp2);

	rewind(fp2);
	fseek(fp2, cur_pos, SEEK_CUR);

	
	//i value loops from cur_pos to end_pos.
	//reads character by character from fp2 and stores in ch.
	//and writes character by character from ch to fp1.

	char ch;
	for(int i=cur_pos; i<=end_pos; i++)
	{
		fread(&ch, sizeof(char), 1, fp2);
		fwrite(&ch, sizeof(char), 1, fp1);
	}


	//first remove user entered command line input file at index 4.
	//and then rename temp.mp3 file as user entered file at index 4 in command line.

	remove(argv[4]);
	rename("temp.mp3", argv[4]);


	//close file pointers fp1 and fp2.

	fclose(fp1);
	fclose(fp2);

	
	//print_edit_option() function is called to print edit details.

	print_edit_option(index, argv);
}



//print_edit_option() function definition and prints edit details.

void print_edit_option(int i, char* argv[])
{
	char *N[6] = {"Title", "Artist", "Album", "Year", "Content", "Comment"};

	printf("\n------------------------------Select Edit option---------------------------------------\n");
	printf("----------------------------Select %s change option--------------------------------\n", N[i]);
	printf("			      %s	:    %s\n", N[i], argv[3]);
	printf("-----------------------------%s changed successfully-------------------------------\n\n", N[i]);
}


