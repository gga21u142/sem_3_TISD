#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix_io.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

void input_flush(void)
{
    char check;
    scanf("%c", &check);
    for (char check1 = check; check1 != '\n'; scanf("%c", &check1)){}
}

int read_matrix_key(double *matrix, int row, int col)
{
    double elem;
    printf("Input matrix with %d rows and %d colums:\n\n", row, col);
    for (int i = 0; i < row; i++)
    {
        printf("Input %d'th row: ", i + 1);
        for (int j = 0; j < col; j++)
        {
            if (scanf("%lf", &elem) != 1)
            {
               printf("Wrong input!\n");
               return EXIT_FAILURE; 
            }
            matrix[i * col + j] = elem;
        }
        input_flush();
    }
    return EXIT_SUCCESS;
}

void print_matrix_standart(double *matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%15.6lf", matrix[i * col + j]);
        printf("\n");
    }
    printf("\n");
}

int read_matrix_file(FILE *fsrc, double **matrix, int *row, int *col)
{
    if (fscanf(fsrc, "%d%d", row, col) != 2)
        return FILE_ERROR;
    char check;
    fscanf(fsrc, "%c", &check);
    if (check != '\n')
        return FILE_ERROR;
    if (row <= 0 || col <= 0)
    	return FILE_ERROR;
    *matrix = malloc((*row) * (*col) * M_SIZE);
    if (*matrix == NULL)
        return MEMORY_ERROR;
    double elem;
    for (int i = 0; i < (*row); i++)
    {
        for (int j = 0; j < (*col); j++)
        {
            if (fscanf(fsrc, "%lf", &elem) != 1)
                return FILE_ERROR;
            (*matrix)[i * (*col) + j] = elem;
        }
        fscanf(fsrc, "%c", &check);
        if (check != '\n')
            return FILE_ERROR;
    }
    fscanf(fsrc, "%c", &check);
        if (check != '\n')
            return FILE_ERROR;
    if (! feof(fsrc))
        return FILE_ERROR;

    return EXIT_SUCCESS;
}

int read_matrix_sparse_key(int row, int col, double *AN, int *AI, int *AJ, int *not_zeros_A)
{
    double elem;
    printf("Input matrix with %d rows and %d colums:\n\n", row, col);
    for (int i = 0; i < col; i++)
    {
        printf("Input %d'th col: ", i + 1);
        for (int j = 0; j < row; j++)
        {
            if (scanf("%lf", &elem) != 1)
            {
               printf("Wrong input!\n");
               return EXIT_FAILURE; 
            }
            if (fabs(elem) > 1e-16)
            {
                AN[(*not_zeros_A)++] = elem;
                AI[(*not_zeros_A) - 1] = j;
                if (AJ[i] == -1)
                    AJ[i] = (*not_zeros_A) - 1;
            }
        }
        input_flush();
    }
    input_flush();
    return EXIT_SUCCESS;
}

void print_matrix_sparse(double *arr_AN, int not_zeros_A, int *arr_AI, int Aj, int *arr_AJ)
{
    printf("Array with not zero elemets:\n");
    for (int i = 0; i < not_zeros_A; i++)
        printf("%15.6lf", arr_AN[i]);
    printf("\nArray with their rows:\n");
    for (int i = 0; i < not_zeros_A; i++)
        printf("%d ", arr_AI[i]);
    printf("\nLinked array with positions of number that went first in column:\n");
    for (int i = 0; i < Aj; i++)
        printf("%d ", arr_AJ[i]);
    printf("\n");
    
}



int read_matrix_sparce_file(FILE *fsrc, int *not_zeros_A, int *row, int *col, double **arr_AN, int **arr_AI, int **arr_AJ)
{
    if (fscanf(fsrc, "%d%d", row, col) != 2)
        return FILE_ERROR;
    char check;
    fscanf(fsrc, "%c", &check);
    if (check != '\n')
        return FILE_ERROR;
    if (row <= 0 || col <= 0)
    	return FILE_ERROR;
    	
    *arr_AN = malloc((*row) * (*col) * M_SIZE);
	if (*arr_AN == NULL)
       	return MEMORY_ERROR;

	*arr_AI = malloc((*row) * (*col) * sizeof(int));
	if (*arr_AI == NULL)
	{
		free(*arr_AN);
       	return MEMORY_ERROR;
	}

	*arr_AJ = malloc((*col) * sizeof(int));
	if (*arr_AJ == NULL)
	{
		free(*arr_AN);
		free(*arr_AI);
       	return MEMORY_ERROR;
	}
	for (int i = 0; i < (*col); i++)
	    (*arr_AJ)[i] = -1;

    double elem;
    for (int i = 0; i < (*col); i++)
    {
        for (int j = 0; j < (*row); j++)
        {
            if (fscanf(fsrc, "%lf", &elem) != 1)
               return FILE_ERROR;
            if (fabs(elem) > 1e-16)
            {
                (*arr_AN)[(*not_zeros_A)++] = elem;
                (*arr_AI)[(*not_zeros_A) - 1] = j;
                if ((*arr_AJ)[i] == -1)
                    (*arr_AJ)[i] = (*not_zeros_A) - 1;
            }
        }
    }
    return EXIT_SUCCESS;
}


