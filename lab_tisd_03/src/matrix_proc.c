#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix_proc.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

/* typedef struct
{
    double *arr_N;
    int *arr_I;
    int *arr_J;
} sparce_matrix;
 */

void mutiply_matrixes_standart(double *matrix_A, int Ai, int Aj, double *matrix_B, int Bj, double *matrix_C)
{
    double elem = 0;
    for (int i = 0; i < Ai; i++)
        for (int j = 0; j < Bj; j++)
        {
            for (int k = 0; k < Aj; k++)
                elem += matrix_A[i * Aj + k] * matrix_B[k * Bj + j];

            matrix_C[i * Bj + j] = elem;
            elem = 0;
        }
}

void mutiply_matrix_vector_sparse(int not_zeros_A, double *arr_AN, int *arr_AI, int Aj, int *arr_AJ, int not_zeros_B, double *arr_BN, int *arr_BI, int Ai, double *arr_C, int *not_zeros_C, double *arr_CN, int *arr_CI, int *arr_CJ)
{
    int start;
    int stop;
    for (int i = 0; i < not_zeros_B; i++)
    {
        start = arr_AJ[arr_BI[i]];
        if (start != -1)
        {
            stop = not_zeros_A;
            for (int j = arr_BI[i] + 1; j < Aj; j++)
                if (arr_AJ[j] != -1)
                {
                    stop = arr_AJ[j];
                    break;
                }

            for (int j = start; j < stop; j++)
                arr_C[arr_AI[j]] += arr_AN[j] * arr_BN[i];
        }   
    }

    for (int i = 0; i < Ai; i++)
    {
        if (fabs(arr_C[i]) > 1e-16)
        {
            arr_CN[(*not_zeros_C)++] = arr_C[i];
            arr_CI[(*not_zeros_C) - 1] = i;
            if (arr_CJ[i] == -1)
                    arr_CJ[i] = (*not_zeros_C) - 1;
        }
    }
}
