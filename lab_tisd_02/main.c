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
		country_sort keys_arr[M_COUNTRIES];
		int volume = 0;

		if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
		{	
			printf("File is empty or damaged!\n");
			fclose(fsrc);
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
			fclose(fsrc);
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
		country_sort keys_arr[M_COUNTRIES];
		int volume = 0;

		if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
		{	
			printf("File is empty or damaged!\n");
			fclose(fsrc);
			return FILE_ERROR;
		}
		fclose(fsrc);

		char continent_search[M_CONTINENT];
		char sport_search[M_TOURISM];
		printf("You can delete countries by continent and sports type, to proceed type one of continents names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
		if (scanf("%s", continent_search) != 1)
		{
			printf("Empty input or wrong name!\n");
			return EXIT_FAILURE;
		}

		printf("Input one of sports types 'skiing', 'climbing' or 'surfing' : ");
		if (scanf("%s", sport_search) != 1)
		{
			printf("Empty input or wrong type!\n");
			return EXIT_FAILURE;
		}

		if (! strcmp(continent_search, "Africa") || ! strcmp(continent_search, "Asia") || ! strcmp(continent_search, "Australia") || ! strcmp(continent_search, "Europe") || ! strcmp(continent_search, "North_America") || ! strcmp(continent_search, "South_America"))
		{
			if (! strcmp(sport_search, "skiing") || ! strcmp(sport_search, "climbing") || ! strcmp(sport_search, "surfing"))
			{
				fsrc = fopen(argv[1], "w");
				delete_country(fsrc, volume, countries_arr, continent_search, sport_search);
				printf("Countries was deleted!\n");
			}
		}
		else
		{
			printf("Wrong continent name or sport type!\n");
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
		country_sort keys_arr[M_COUNTRIES];
		int volume = 0;

		if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
		{	
			printf("File is empty or damaged!\n");
			fclose(fsrc);
			return FILE_ERROR;
		}	


		char sort_type[10];
		printf("Choose what to sort main table or keys table (input main or key): ");
		if (scanf("%s", sort_type) != 1)
		{
			printf("Wrong sort type!\n");
			fclose(fsrc);
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
				qsort(countries_arr, volume, COUNTRY_T_SIZE, country_cmp);
			else
			{
				printf("Wrong input!\n");
				fclose(fsrc);
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
				fclose(fsrc);
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
				qsort(keys_arr, volume, country_sort_SIZE, country_key_cmp);
			else
			{
				printf("Wrong input!\n");
				fclose(fsrc);
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
				fclose(fsrc);
				return EXIT_FAILURE;
			}

			printf("Do you want to print sorted main table? Input y or n: ");
			scanf("\n%c", &choice);
			if (choice == 'y')
				print_main_table_by_keys(volume, countries_arr, keys_arr);
			else if (choice != 'n')
			{
				printf("Wrong input!\n");
				fclose(fsrc);
				return EXIT_FAILURE;
			}
		}

		else
		{
			printf("Wrong sort type!\n");
			fclose(fsrc);
			return EXIT_FAILURE;
		}
	}

	else if (! strcmp(argv[2], "search"))
	{
		fsrc = fopen(argv[1], "r");
		if (fsrc == NULL)
		{
			printf("Could not open %s because of %s\n", argv[2], strerror(errno));
			return FILE_ERROR;
		}

		country_t countries_arr[M_COUNTRIES];
		country_sort keys_arr[M_COUNTRIES];
		int volume = 0;

		if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
		{	
			printf("File is empty or damaged!\n");
			fclose(fsrc);
			return FILE_ERROR;
		}		

		char continent_search[M_CONTINENT];
		char sport_search[M_TOURISM];
		printf("You can search countries by continent and sports type, to proceed type one of continents names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
		if (scanf("%s", continent_search) != 1)
		{
			printf("Empty input or wrong name!\n");
			fclose(fsrc);
			return EXIT_FAILURE;
		}

		printf("Input one of sports types 'skiing', 'climbing' or 'surfing' : ");
		if (scanf("%s", sport_search) != 1)
		{
			printf("Empty input or wrong type!\n");
			fclose(fsrc);
			return EXIT_FAILURE;
		}

		if (! strcmp(continent_search, "Africa") || ! strcmp(continent_search, "Asia") || ! strcmp(continent_search, "Australia") || ! strcmp(continent_search, "Europe") || ! strcmp(continent_search, "North_America") || ! strcmp(continent_search, "South_America"))
		{
			if (! strcmp(sport_search, "skiing") || ! strcmp(sport_search, "climbing") || ! strcmp(sport_search, "surfing"))
				print_match_countries(volume, countries_arr, continent_search, sport_search);
		}
		else
		{
			printf("Wrong continent name or sport type!\n");
			fclose(fsrc);
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
