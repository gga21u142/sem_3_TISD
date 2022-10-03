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

		print_countries(volume, countries_arr);
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

	else if (! strcmp(argv[2], "delete"))
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
		fclose(fsrc);
		printf("You can delete all countries by continent, to proceed type one of these names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
		char continent_delete[M_CONTINENT];
		if (scanf("%s", continent_delete) != 1)
		{
			printf("Wrong continent name!\n");
			return EXIT_FAILURE;
		}

		if (! strcmp(continent_delete, "Africa") || ! strcmp(continent_delete, "Asia") || ! strcmp(continent_delete, "Australia") || ! strcmp(continent_delete, "Europe") || ! strcmp(continent_delete, "North_America") || ! strcmp(continent_delete, "South_America"))
		{
			fsrc = fopen(argv[1], "w");
			delete_countries_by_cont(fsrc, volume, countries_arr, continent_delete);
			printf("Countries was deleted!\n");
		}
		else
		{
			printf("Wrong continent name!\n");
			return EXIT_FAILURE;
		}
	}

	else if (! strcmp(argv[2], "sort"))
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


		char sort_type[10];
		printf("Choose what to sort main table or keys table (input main or key): ");
		if (scanf("%s", sort_type) != 1)
		{
			printf("Wrong sort type!\n");
			return EXIT_FAILURE;
		}

		if (! strcmp(sort_type, "main"))
		{
			printf("What sort algorithm do you want? Input s for standart and q for quick: ");
			char choice;
			scanf("\n%c", &choice);
			if (choice == 's')
				sort_main_table(volume, countries_arr);
			else if (choice == 'q')
				qsort(countries_arr, volume, COUNTRY_T_SIZE, continent_cmp);
			else
			{
				printf("Wrong input!\n");
				return EXIT_FAILURE;
			}

			printf("Main table was sorted!\n");
			printf("Do you want to print the main table? Input y or n: ");
			scanf("\n%c", &choice);
			if (choice == 'y')
				print_countries(volume, countries_arr);
			else if (choice != 'n')
			{
				printf("Wrong input!\n");
				return EXIT_FAILURE;
			}
		}

		else if (! strcmp(sort_type, "key"))
		{
			printf("What sort algorithm do you want? Input s for standart and q for quick: ");
			char choice;
			scanf("\n%c", &choice);
			if (choice == 's')
				sort_keys_table(volume, keys_arr);
			else if (choice == 'q')
				qsort(keys_arr, volume, CONTINENT_SORT_SIZE, continent_key_cmp);
			else
			{
				printf("Wrong input!\n");
				return EXIT_FAILURE;
			}

			
			printf("Keys table was sorted!\n");
			printf("Do you want to print the keys table? Input y or n: ");
			scanf("\n%c", &choice);
			if (choice == 'y')
				print_key_table(volume, keys_arr);
			else if (choice != 'n')
			{
				printf("Wrong input!\n");
				return EXIT_FAILURE;
			}

			printf("Do you want to print sorted main table? Input y or n: ");
			scanf("\n%c", &choice);
			if (choice == 'y')
				print_main_table_by_keys(volume, countries_arr, keys_arr);
			else if (choice != 'n')
			{
				printf("Wrong input!\n");
				return EXIT_FAILURE;
			}
		}

		else
		{
			printf("Wrong sort type!\n");
			return EXIT_FAILURE;
		}
	}

	else
	{
		printf("Wrong mode argument!\n");
		return ARG_ERROR;
	}

	fclose(fsrc);
	return EXIT_SUCCESS;
}
