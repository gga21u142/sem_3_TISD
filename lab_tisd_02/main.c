#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "country_t.h"

#define ARG_ERROR -2
#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define INPUT_ERROR 2

int main(int argc, char **argv)
{
	FILE *fsrc;
	
	if (argc < 3)
	{
		printf("Wrong amount of arguments!\n");
		return ARG_ERROR;
	}

	if (! strcmp(argv[2], "print"))
	{
		fsrc = fopen(argv[1], "r");
		if (fsrc == NULL)
		{
			printf("Could not open %s because of %s\n", argv[2], strerror(errno));
			return FILE_ERROR;
		}

		country_t countries_arr[M_COUNTRIES];
		continent_sort keys_arr[M_COUNTRIES];
		int volume = 0;

		if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
		{	
			printf("File is empty or damaged!\n");
			return FILE_ERROR;
		}		

		if (print_countries(volume, countries_arr) != EXIT_SUCCESS)
		{	
			printf("File is damaged!\n");
			return FILE_ERROR;
		}
	}
 
	else if (! strcmp(argv[2], "add"))
	{
		fsrc = fopen(argv[1], "a");
		if (fsrc == NULL)
		{
			printf("Could not open %s because of %s\n", argv[2], strerror(errno));
			return FILE_ERROR;
		}

		if (add_country(fsrc) != EXIT_SUCCESS)
		{	
			printf("Input record is not as it intended to be!\n");
			return INPUT_ERROR;
		}
	}
/*
	else if (! strcmp(argv[2], "delete"))
	{

	}

	else if (! strcmp(argv[2], "sort"))
	{
		char sort_type[10];
		printf("Choose what to sort main table or keys table (input main or key): ");

	}
*/
	else
	{
		printf("Wrong mode argument!\n");
		return ARG_ERROR;
	}

	fclose(fsrc);
	return EXIT_SUCCESS;
}
