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

