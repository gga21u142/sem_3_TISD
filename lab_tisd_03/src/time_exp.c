#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int generate_rand_matrix(char *file_name, int row, int col, int percentage)
{
	if (percentage > 100 || percentage < 0)
		return EXIT_FAILURE;
	srand(time(NULL));
	FILE *fdst = fopen(file_name, "w");
	if (fdst == NULL)
		return FILE_ERROR;
	printf("Empty file generated!\n");
	
	int division = row * col + 1;
	if (percentage != 0)
		division = 100 / percentage;
	fprintf(fdst, "%d %d\n", row, col);
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if ((i * row + j) % division)
				fprintf(fdst, "%.6lf", randfrom(-100000, 100000));
			else
				fprintf(fdst, "%.6lf", 0.0);
			if (j != row - 1)
				fprintf(fdst, " ");
		}
		fprintf(fdst, "\n");
	}
	fclose(fdst);
	return EXIT_SUCCESS;
}
