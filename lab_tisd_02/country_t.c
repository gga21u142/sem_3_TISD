#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "country_t.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int read_countries(FILE *fsrc, int *volume, country_t *country_arr, continent_sort *keys_arr)
{
	int temp_err = 0;
	char country_name [M_COUNTRY];
	int population;
	char capital_name [M_CAPITAL];
	char continent_name [M_CONTINENT];
	int vaccine_need;
	char main_tourism [M_TOURISM];

	char sub_info_s [M_SUBINFO];
	int sub_info_d1;
	int sub_info_d2;
	int sub_info_d3;

	temp_err = fscanf(fsrc, "%s %d %s %s %d %s ", country_name, &population, capital_name, continent_name, &vaccine_need, main_tourism);
	while (temp_err == 6 && *volume < M_COUNTRIES)
	{
		if ( ! strcmp(main_tourism, "tour"))
		{
			if (fscanf(fsrc, "%d %s\n", &sub_info_d1, sub_info_s) != 2)
				return EXIT_FAILURE;
			country_arr[*volume].tourism_info.tour.objects_count = sub_info_d1;
			strcpy(country_arr[*volume].tourism_info.tour.tour_type, sub_info_s);
		}
		else if ( ! strcmp(main_tourism, "beach"))
		{
			if (fscanf(fsrc, "%s %d %d %d\n", sub_info_s, &sub_info_d1, &sub_info_d2, &sub_info_d3) != 4)
				return EXIT_FAILURE;
			strcpy(country_arr[*volume].tourism_info.beach.main_season, sub_info_s);
			country_arr[*volume].tourism_info.beach.air_temperature = sub_info_d1;
			country_arr[*volume].tourism_info.beach.water_temperature = sub_info_d2;
			country_arr[*volume].tourism_info.beach.flight_time = sub_info_d3;
		}
		
		else if ( ! strcmp(main_tourism, "sport"))
		{
			if (fscanf(fsrc, "%s %d\n", sub_info_s, &sub_info_d1) != 2)
				return EXIT_FAILURE;			
			strcpy(country_arr[*volume].tourism_info.sport.sport_type, sub_info_s);
			country_arr[*volume].tourism_info.sport.min_cost = sub_info_d1;
		}
		else
			return EXIT_FAILURE;

		strcpy(country_arr[*volume].country_name, country_name);
		country_arr[*volume].population = population;
		strcpy(country_arr[*volume].capital_name, capital_name);
		strcpy(country_arr[*volume].continent_name, continent_name);
		country_arr[*volume].vaccine_need = vaccine_need;
		strcpy(country_arr[*volume].main_tourism, main_tourism);

		keys_arr[*volume].src_index = *volume;
		strcpy(keys_arr[*volume].continent_name, continent_name);
	
		(*volume)++;

		temp_err = fscanf(fsrc, "%s %d %s %s %d %s ", country_name, &population, capital_name, continent_name, &vaccine_need, main_tourism);
	}

	if (temp_err != EOF || *volume == 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int print_countries(int volume, country_t *countries_arr)
{
	for (int i = 0; i < volume; i++)
	{	
		const country_t *ptr = &countries_arr[i];
		printf("%s %d %s %s %d %s ", ptr->country_name, ptr->population, ptr->capital_name, ptr->continent_name, ptr->vaccine_need, ptr->main_tourism);
		if ( ! strcmp(ptr->main_tourism, "tour"))
			printf("%d %s\n", ptr->tourism_info.tour.objects_count, ptr->tourism_info.tour.tour_type);

		else if ( ! strcmp(ptr->main_tourism, "beach"))
			printf("%s %d %d %d\n", ptr->tourism_info.beach.main_season, ptr->tourism_info.beach.air_temperature, ptr->tourism_info.beach.water_temperature, ptr->tourism_info.beach.flight_time);

		else if ( ! strcmp(ptr->main_tourism, "sport"))
			printf("%s %d\n", ptr->tourism_info.sport.sport_type, ptr->tourism_info.sport.min_cost);

		else
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int add_country(FILE* fsrc)
{
	char country_name [M_COUNTRY];
	int population;
	char capital_name [M_CAPITAL];
	char continent_name [M_CONTINENT];
	int vaccine_need;
	char main_tourism [M_TOURISM];

	char sub_info_s [M_SUBINFO];
	int sub_info_d1;
	int sub_info_d2;
	int sub_info_d3;

	printf("Input country name (if theres space in name put '_' instead: ");
	if (scanf("%s", country_name) != 1 || strlen(country_name) > M_COUNTRY - 2)
	{
		printf("Wrong country name lenght!\n");
		return EXIT_FAILURE;
	}

	printf("Input population: ");
	if (scanf("%d", &population) != 1)
	{
		printf("\nWrong population number!\n");
		return EXIT_FAILURE;
	}

	printf("Input capital name (if theres space in name put '_' instead: ");
	if (scanf("%s", capital_name) != 1 || strlen(capital_name) > M_CAPITAL - 2)
	{
		printf("\nWrong capital name lenght!\n");
		return EXIT_FAILURE;
	}

	printf("Input continent name (Asia, Europe, North_America, South_America, Africa or Australia): ");
	if (scanf("%s", continent_name) != 1 || strlen(continent_name) > M_CONTINENT - 2)
		 if (strcmp(continent_name, "Asia") && strcmp(continent_name, "Europe") && strcmp(continent_name, "North_America") && strcmp(continent_name, "South_America") && strcmp(continent_name, "Africa") && strcmp(continent_name, "Australia"))
		{
			printf("\nWrong continent name lenght!\n");
			return EXIT_FAILURE;
		}

	printf("Input 0 if vaccine not needed, else 1: ");
	if (scanf("%d", &vaccine_need) != 1 || (vaccine_need != 1 && vaccine_need != 0))
	{
		printf("\nWrong vaccine status!\n");
		return EXIT_FAILURE;
	}

	printf("Input tourism type (tour, beach or sport): ");
	if (scanf("%s", main_tourism) != 1 || strlen(main_tourism) > M_TOURISM - 2)
	{
		printf("\nWrong tourism type lenght!\n");
		return EXIT_FAILURE;
	}
	

	if (! strcmp(main_tourism, "tour"))
	{
		printf("Input tour objects quntity: ");
		if (scanf("%d", &sub_info_d1) != 1)
		{
			printf("\nWrong tour objects quntity!\n");
			return EXIT_FAILURE;
		}

		printf("Input tour type (historic, nature or art): ");
		if (scanf("%s", sub_info_s) != 1 || strlen(sub_info_s) > M_SUBINFO - 2)
			if (strcmp(sub_info_s, "historic") && strcmp(sub_info_s, "nature") && strcmp(sub_info_s, "art"))
			{
				printf("\nWrong tour type!\n");
				return EXIT_FAILURE;
			}
	}

	else if (! strcmp(main_tourism, "beach"))
	{
		printf("Input main season for beach tour (summer, autumn, winter or spring): ");
		if (scanf("%s", sub_info_s) != 1 || strlen(sub_info_s) > M_SUBINFO - 2)
			if (strcmp(sub_info_s, "summer") && strcmp(sub_info_s, "autumn") && strcmp(sub_info_s, "winter") && strcmp(sub_info_s, "spring"))
			{
				printf("\nWrong main season for beach tour!\n");
				return EXIT_FAILURE;
			}

		printf("Input air temperature: ");
		if (scanf("%d", &sub_info_d1) != 1)
		{
			printf("\nWrong air temperature!\n");
			return EXIT_FAILURE;
		}

		printf("Input water temperature: ");
		if (scanf("%d", &sub_info_d2) != 1)
		{
			printf("\nWrong water temperature!\n");
			return EXIT_FAILURE;
		}

		printf("Input flight time for beach tour in minutes: ");
		if (scanf("%d", &sub_info_d3) != 1)
		{
			printf("\nWrong flight time for beach tour!\n");
			return EXIT_FAILURE;
		}
	}

	else if (! strcmp(main_tourism, "sport"))
	{
		printf("Input sport type (skiing, climbing or surfing): ");
		if (scanf("%s", sub_info_s) != 1 || strlen(sub_info_s) > M_SUBINFO - 2)
			if (strcmp(sub_info_s, "skiing") && strcmp(sub_info_s, "climbing") && strcmp(sub_info_s, "surfing"))
			{
				printf("\nWrong sport type!\n");
				return EXIT_FAILURE;
			}

		printf("Input minimal cost for sport tour: ");
		if (scanf("%d", &sub_info_d1) != 1)
		{
			printf("\nWrong minimal cost for sport tour!\n");
			return EXIT_FAILURE;
		}
	}

	else
	{
		printf("\nWrong tourism type name!\n");
		return EXIT_FAILURE;
	}


	fprintf(fsrc, "%s %d %s %s %d %s ", country_name, population, capital_name, continent_name, vaccine_need, main_tourism);
	if ( ! strcmp(main_tourism, "tour"))
		fprintf(fsrc, "%d %s\n", sub_info_d1, sub_info_s);

	else if ( ! strcmp(main_tourism, "beach"))
		fprintf(fsrc, "%s %d %d %d\n", sub_info_s, sub_info_d1, sub_info_d2, sub_info_d3);

	else if ( ! strcmp(main_tourism, "sport"))
		fprintf(fsrc, "%s %d\n", sub_info_s, sub_info_d1);
	
	return EXIT_SUCCESS;
}


