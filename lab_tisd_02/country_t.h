#ifndef __COUNTRY_T_H__
#define __COUNTRY_T_H__

#define M_COUNTRIES 100
#define M_COUNTRY 30
#define M_CAPITAL 30
#define M_CONTINENT 30
#define M_TOURISM 10
#define M_SUBINFO 20

typedef struct tourism_tour_n
{
	int objects_count;
	char tour_type[M_SUBINFO];
} tourism_tour;

typedef struct tourism_beach_n
{
	char main_season[M_SUBINFO];
	int air_temperature;
	int water_temperature;
	int flight_time;
} tourism_beach;

typedef struct tourism_sport_n
{
	char sport_type[M_SUBINFO];
	int min_cost;
} tourism_sport;

typedef union
{
	struct tourism_tour_n tour;
	struct tourism_beach_n beach;
	struct tourism_sport_n sport;
} tourism_type;

typedef struct 
{
	char country_name[M_COUNTRY];
	int population;
	char capital_name[M_CAPITAL];
	char continent_name[M_CONTINENT];
	int vaccine_need;
	char main_tourism[M_TOURISM];
	tourism_type tourism_info;
} country_t;

typedef struct
{
	int src_index;
	char continent_name[M_CONTINENT];
} continent_sort;


int read_countries(FILE *fsrc, int *volume, country_t *country_arr, continent_sort *keys_arr);
int print_countries(int volume, country_t *countries_arr);

#endif //__COUNTRY_T_H__