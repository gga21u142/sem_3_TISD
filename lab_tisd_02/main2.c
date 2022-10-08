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
	
	if (argc != 2)
	{
		printf("Program is processing file with countries, to proceed start program with directory to database.\n");
		fflush(stdout);
		return ARG_ERROR;
	}
	
	country_t countries_arr[M_COUNTRIES];
	country_sort keys_arr[M_COUNTRIES];
	int volume = 0;	
	char menu[10];
	while (1)
	{
		printf("Input one of commands names (read - to read file, print - to read and print file, add - to add\ncountry to file, delete - to delete country from file, sort - to sort main or keys table or\nsearch - to search country by continent and sport type)");
		fflush(stdout);
		scanf("%s", menu);
		if (! strcmp(menu, "read"))
		{
			fsrc = fopen(argv[1], "r");
			if (fsrc == NULL)
			{
				printf("Could not open %s because of %s\n", menu, strerror(errno));
				fflush(stdout);
				return FILE_ERROR;
			}



			if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
			{	
				printf("File is empty or damaged!\n");
				fflush(stdout);
				fclose(fsrc);
				return FILE_ERROR;
			}		
			fclose(fsrc);
		}
		
		else if (! strcmp(menu, "print") && volume != 0)
		{
			print_countries(volume, countries_arr);
		}
	 
		else if (! strcmp(menu, "add") && volume != 0)
		{
			fsrc = fopen(argv[1], "a");
			if (fsrc == NULL)
			{
				printf("Could not open %s because of %s\n", menu, strerror(errno));
				fflush(stdout);
				return FILE_ERROR;
			}

			if (add_country(fsrc) != EXIT_SUCCESS)
			{
				printf("Input record is not as it intended to be!\n");
				fflush(stdout);
			}
			fclose(fsrc);
			
			fsrc = fopen(argv[1], "r");
			if (fsrc == NULL)
			{
				printf("Could not open %s because of %s\n", menu, strerror(errno));
				fflush(stdout);
				return FILE_ERROR;
			}

			if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
			{	
				printf("File is empty or damaged!\n");
				fflush(stdout);
				fclose(fsrc);
				return FILE_ERROR;
			}		
			fclose(fsrc);
		}

		else if (! strcmp(menu, "delete") && volume != 0)
		{
			fsrc = fopen(argv[1], "r");
			if (fsrc == NULL)
			{
				printf("Could not open %s because of %s\n", menu, strerror(errno));
				fflush(stdout);
				return FILE_ERROR;
			}

			if (read_countries(fsrc, &volume, countries_arr, keys_arr) != EXIT_SUCCESS)
			{	
				printf("File is empty or damaged!\n");
				fflush(stdout);
				fclose(fsrc);
				return FILE_ERROR;
			}
			fclose(fsrc);

			char continent_search[M_CONTINENT];
			char sport_search[M_TOURISM];
			printf("You can delete countries by continent and sports type, to proceed type one of continents names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
			fflush(stdout);
			if (scanf("%s", continent_search) != 1)
			{
				printf("Empty input or wrong name!\n");
				fflush(stdout);
				continue;
			}

			printf("Input one of sports types 'skiing', 'climbing' or 'surfing' : ");
			if (scanf("%s", sport_search) != 1)
			{
				printf("Empty input or wrong type!\n");
				fflush(stdout);
				continue;
			}

			if (! strcmp(continent_search, "Africa") || ! strcmp(continent_search, "Asia") || ! strcmp(continent_search, "Australia") || ! strcmp(continent_search, "Europe") || ! strcmp(continent_search, "North_America") || ! strcmp(continent_search, "South_America"))
			{
				if (! strcmp(sport_search, "skiing") || ! strcmp(sport_search, "climbing") || ! strcmp(sport_search, "surfing"))
				{
					fsrc = fopen(argv[1], "w");
					delete_country(fsrc, volume, countries_arr, continent_search, sport_search);
					printf("Countries was deleted!\n");
					fflush(stdout);
				}
			}
			else
			{
				printf("Wrong continent name or sport type!\n");
				fflush(stdout);
			}
		}

		else if (! strcmp(menu, "sort") && volume != 0)
		{
			
			char sort_type[10];
			printf("Choose what to sort main table or keys table (input main or key): ");
			fflush(stdout);
			if (scanf("%s", sort_type) != 1)
			{
				printf("Wrong sort type!\n");
				fflush(stdout);
				continue;
			}

			if (! strcmp(sort_type, "main"))
			{
				printf("What sort algorithm do you want? Input s for standart and q for quick: ");
				fflush(stdout);
				char choice;
				scanf("\n%c", &choice);
				if (choice == 's')
					sort_main_table(volume, countries_arr);
				else if (choice == 'q')
					qsort(countries_arr, volume, COUNTRY_T_SIZE, country_cmp);
				else
				{
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}

				printf("Main table was sorted!\n");
				printf("Do you want to print the main table? Input y or n: ");
				fflush(stdout);
				scanf("\n%c", &choice);
				if (choice == 'y')
					print_countries(volume, countries_arr);
				else if (choice != 'n')
				{
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}
			}

			else if (! strcmp(sort_type, "key"))
			{
				printf("What sort algorithm do you want? Input s for standart and q for quick: ");
				fflush(stdout);
				char choice;
				scanf("\n%c", &choice);
				if (choice == 's')
					sort_keys_table(volume, keys_arr);
				else if (choice == 'q')
					qsort(keys_arr, volume, COUNTRY_SORT_SIZE, country_key_cmp);
				else
				{
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}

				
				printf("Keys table was sorted!\n");
				printf("Do you want to print the keys table? Input y or n: ");
				fflush(stdout);
				scanf("\n%c", &choice);
				if (choice == 'y')
					print_key_table(volume, keys_arr);
				else if (choice != 'n')
				{
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}

				printf("Do you want to print sorted main table? Input y or n: ");
				fflush(stdout);
				scanf("\n%c", &choice);
				if (choice == 'y')
					print_main_table_by_keys(volume, countries_arr, keys_arr);
				else if (choice != 'n')
				{
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}
			}

			else
			{
				printf("Wrong sort type!\n");
				fflush(stdout);
				continue;
			}
		}

		else if (! strcmp(menu, "search") && volume != 0)
		{

			char continent_search[M_CONTINENT];
			char sport_search[M_TOURISM];
			printf("You can search countries by continent and sports type, to proceed type one of continents names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
			fflush(stdout);
			if (scanf("%s", continent_search) != 1)
			{
				printf("Empty input or wrong name!\n");
				fflush(stdout);
				continue;
			}

			printf("Input one of sports types 'skiing', 'climbing' or 'surfing' : ");
			fflush(stdout);
			if (scanf("%s", sport_search) != 1)
			{
				printf("Empty input or wrong type!\n");
				fflush(stdout);
				continue;
			}

			if (! strcmp(continent_search, "Africa") || ! strcmp(continent_search, "Asia") || ! strcmp(continent_search, "Australia") || ! strcmp(continent_search, "Europe") || ! strcmp(continent_search, "North_America") || ! strcmp(continent_search, "South_America"))
			{
				if (! strcmp(sport_search, "skiing") || ! strcmp(sport_search, "climbing") || ! strcmp(sport_search, "surfing"))
					print_match_countries(volume, countries_arr, continent_search, sport_search);
			}
			else
			{
				printf("Wrong continent name or sport type!\n");
				fflush(stdout);
				continue;
			}

		}
		
		else
		{
			printf("Wrong function name or file not readed.\n");
			fflush(stdout);
		}
	}
	
	return EXIT_SUCCESS;
}
