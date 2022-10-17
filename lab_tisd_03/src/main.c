#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_proc.h"
#include "matrix_io.h"
#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


int main(void)
{
	printf("\nProgramm is processing with matrix, to start choose the command:\n0) Exit the program\n1) Multiply matrix on vector.\n2) Multiply matrixes by standart method.\n3) time feature\n");
	int menu;
	char choose[10];
	int ret_err;
	while(1)
	{	
		printf("Input command number: ");
		if (scanf("%d", &menu) != 1)
		{
			input_flush();
			printf("\nWrong menu option, try one more time!\n");
			continue;
		}

		switch (menu)
		{
			case 0:
			{	
				printf("Shutting down program...\n");
				return EXIT_SUCCESS;
			}
			case 1:
			{
				printf("Do you want to interact with files or keyboard? Input 'file' or 'key': ");
				scanf("%s", choose);
				while (strlen(choose) > 5 || (! strcmp(choose, "file") && ! strcmp(choose, "key")))
				{
					printf("\nWrong option, try one more time!\n");
					input_flush();
					printf("\nInput 'file' or 'key': ");
					scanf("%s", choose);
				}
				input_flush();
				if (! strcmp(choose, "key"))
				{
					int Ai, Aj, Bi, Bj;


					printf("Input matrix A sizes: ");
					scanf("%d%d", &Ai, &Aj);
					input_flush();
					while (Ai <= 0 || Aj <= 0)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Ai, &Aj);
						input_flush();
					}

					int not_zeros_A = 0;
					double *arr_AN = malloc(Ai * Aj * M_SIZE);
					if (arr_AN == NULL)
					{
						printf("Can't allocate AN!\n");
       					return MEMORY_ERROR;
					}
					int *arr_AI = malloc(Ai * Aj * sizeof(int));
					if (arr_AI == NULL)
					{
						free(arr_AN);
						printf("Can't allocate AI!\n");
       					return MEMORY_ERROR;
					}
					int *arr_AJ = malloc(Aj * sizeof(int));
					if (arr_AJ == NULL)
					{
						free(arr_AN);
						free(arr_AI);
						printf("Can't allocate AJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < Aj; i++)
						arr_AJ[i] = -1;

					ret_err = read_matrix_sparse_key(Ai, Aj, arr_AN, arr_AI, arr_AJ, &not_zeros_A);
					while (ret_err != EXIT_SUCCESS)
					{
						ret_err = read_matrix_sparse_key(Ai, Aj, arr_AN, arr_AI, arr_AJ, &not_zeros_A);
					}


					printf("Input vertical vector B sizes: ");
					scanf("%d%d", &Bi, &Bj);
					while (Bi <= 0 || Bj != 1 || Aj != Bi)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Bi, &Bj);
						input_flush();
					}


					int not_zeros_B = 0;
					double *arr_BN = malloc(Bi * Bj * M_SIZE);
					if (arr_BN == NULL)
					{
						printf("Can't allocate BN!\n");
       					return MEMORY_ERROR;
					}
					int *arr_BI = malloc(Bi * Bj * sizeof(int));
					if (arr_BI == NULL)
					{
						free(arr_BN);
						free(arr_AN);
						free(arr_AI);
						printf("Can't allocate BI!\n");
       					return MEMORY_ERROR;
					}
					int *arr_BJ = malloc(Bj * sizeof(int));
					if (arr_BJ == NULL)
					{
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						printf("Can't allocate BJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < Bj; i++)
						arr_BJ[i] = -1;

					ret_err = read_matrix_sparse_key(Bi, Bj, arr_BN, arr_BI, arr_BJ, &not_zeros_B);
					while (ret_err != EXIT_SUCCESS)
					{
						ret_err = read_matrix_sparse_key(Bi, Bj, arr_BN, arr_BI, arr_BJ, &not_zeros_B);
					}
					
					printf("\nMatrix A:\n");
					print_matrix_sparse(arr_AN, not_zeros_A, arr_AI, Aj, arr_AJ);
					printf("\nVector B:\n");
					print_matrix_sparse(arr_BN, not_zeros_B, arr_BI, Bj, arr_BJ);

					int not_zeros_C = 0;

					double *arr_C = calloc(Ai * Bj, M_SIZE);
					if (arr_C == NULL)
					{
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						printf("Can't allocate answer array C!\n");
       					return MEMORY_ERROR;
					}

					double *arr_CN = malloc(Ai * Bj * M_SIZE);
					if (arr_CN == NULL)
					{
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						free(arr_C);
						printf("Can't allocate CN!\n");
       					return MEMORY_ERROR;
					}
					int *arr_CI = malloc(Ai * Bj * sizeof(int));
					if (arr_CI == NULL)
					{
						free(arr_CN);
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						free(arr_C);
						printf("Can't allocate CI!\n");
       					return MEMORY_ERROR;
					}
					int *arr_CJ = malloc(Bj * sizeof(int));
					if (arr_CJ == NULL)
					{
						free(arr_CN);
						free(arr_CI);
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						free(arr_C);
						printf("Can't allocate CJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < Bj; i++)
						arr_CJ[i] = -1;
					
					mutiply_matrix_vector_sparse(not_zeros_A, arr_AN, arr_AI, Aj, arr_AJ, not_zeros_B, arr_BN, arr_BI, Ai, arr_C, &not_zeros_C, arr_CN, arr_CI, arr_CJ);
					printf("\nResult vector C:\n");
					print_matrix_sparse(arr_CN, not_zeros_C, arr_CI, Bj, arr_CJ);

					free(arr_AN);
					free(arr_AI);
					free(arr_AJ);
					free(arr_BN);
					free(arr_BI);
					free(arr_BJ);
					free(arr_C);
					free(arr_CN);
					free(arr_CI);
					free(arr_CJ);

				}
				else if (! strcmp(choose, "file"))
				{
					int Ai, Aj, Bi, Bj;
					char dir_A[30];
					char dir_B[30];

					int not_zeros_A = 0;
					double *arr_AN;
					int *arr_AI, *arr_AJ;
					printf("Input file path with matrix A: ");
					scanf("%s", dir_A);

					FILE *fsrc_A = fopen(dir_A, "r");
					while (fsrc_A == NULL || (! strcmp(dir_A, "exit")))
					{
						if (! strcmp(dir_A, "exit"))
						{
							printf("Shutting down program...\n");
							return FILE_ERROR;
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_A);
						fsrc_A = fopen(dir_A, "r");
					}
					ret_err = read_matrix_sparce_file(fsrc_A, &not_zeros_A, &Ai, &Aj, &arr_AN, &arr_AI, &arr_AJ);
					if (ret_err != EXIT_SUCCESS)
					{
						printf("File is not capable of program needs!\n");
						continue;
					}
					printf("Matrix A readed!\n");
					fclose(fsrc_A);





					int not_zeros_B = 0;
					double *arr_BN;
					int *arr_BI, *arr_BJ;
					printf("Input file path with vertical vector B: ");
					scanf("%s", dir_B);

					FILE *fsrc_B = fopen(dir_B, "r");
					while (fsrc_B == NULL || (! strcmp(dir_B, "exit")))
					{
						if (! strcmp(dir_B, "exit"))
						{
							printf("Shutting down program...\n");
							{	
								free(arr_AN);
								free(arr_AI);
								free(arr_AJ);
								return FILE_ERROR;
							}
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_B);
						fsrc_B = fopen(dir_B, "r");
					}

					ret_err = read_matrix_sparce_file(fsrc_B, &not_zeros_B, &Bi, &Bj, &arr_BN, &arr_BI, &arr_BJ);
					if (ret_err != EXIT_SUCCESS)
					{
						printf("File is not capable of program needs!\n");
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						continue;
					}
					printf("Vector B readed!\n");
					fclose(fsrc_B);








					
					printf("\nMatrix A:\n");
					print_matrix_sparse(arr_AN, not_zeros_A, arr_AI, Aj, arr_AJ);
					printf("\nVector B:\n");
					print_matrix_sparse(arr_BN, not_zeros_B, arr_BI, Bj, arr_BJ);

					int not_zeros_C = 0;

					double *arr_C = calloc(Ai * Bj, M_SIZE);
					if (arr_C == NULL)
					{
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						printf("Can't allocate answer array C!\n");
       					return MEMORY_ERROR;
					}

					double *arr_CN = malloc(Ai * Bj * M_SIZE);
					if (arr_CN == NULL)
					{
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						free(arr_C);
						printf("Can't allocate CN!\n");
       					return MEMORY_ERROR;
					}
					int *arr_CI = malloc(Ai * Bj * sizeof(int));
					if (arr_CI == NULL)
					{
						free(arr_CN);
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						free(arr_C);
						printf("Can't allocate CI!\n");
       					return MEMORY_ERROR;
					}
					int *arr_CJ = malloc(Bj * sizeof(int));
					if (arr_CJ == NULL)
					{
						free(arr_CN);
						free(arr_CI);
						free(arr_BN);
						free(arr_BI);
						free(arr_AN);
						free(arr_AI);
						free(arr_AJ);
						free(arr_BJ);
						free(arr_C);
						printf("Can't allocate CJ!\n");
       					return MEMORY_ERROR;
					}
					for (int i = 0; i < Bj; i++)
						arr_CJ[i] = -1;
					
					mutiply_matrix_vector_sparse(not_zeros_A, arr_AN, arr_AI, Aj, arr_AJ, not_zeros_B, arr_BN, arr_BI, Ai, arr_C, &not_zeros_C, arr_CN, arr_CI, arr_CJ);
					printf("\nResult vector C:\n");
					print_matrix_sparse(arr_CN, not_zeros_C, arr_CI, Bj, arr_CJ);
					{
					free(arr_AN);
					free(arr_AI);
					free(arr_AJ);
					free(arr_BN);
					free(arr_BI);
					free(arr_BJ);
					free(arr_C);
					free(arr_CN);
					free(arr_CI);
					free(arr_CJ);
					}
				}
				break;
			}
			case 2:
			{
				printf("Do you want to interact with files or keyboard? Input 'file' or 'key': ");
				scanf("%s", choose);
				while (strlen(choose) > 5 || (! strcmp(choose, "file") && ! strcmp(choose, "key")))
				{
					printf("\nWrong option, try one more time!\n");
					input_flush();
					printf("\nInput 'file' or 'key': ");
					scanf("%s", choose);
				}
				input_flush();
				if (! strcmp(choose, "key"))
				{
					int Ai, Aj, Bi, Bj;
					printf("Input matrix A sizes: ");
					scanf("%d%d", &Ai, &Aj);
					input_flush();
					while (Ai <= 0 || Aj <= 0)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Ai, &Aj);
						input_flush();
					}
					double *matrix_A = malloc(Ai * Aj * sizeof(M_SIZE));
					if (matrix_A == NULL)
					{
						printf("Can't allocate matrix A!\n");
						return MEMORY_ERROR;
					}
					ret_err = read_matrix_key(matrix_A, Ai, Aj);
					while (ret_err != EXIT_SUCCESS)
					{
						ret_err = read_matrix_key(matrix_A, Ai, Aj);
					}


					printf("Input vertical vector B sizes: ");
					scanf("%d%d", &Bi, &Bj);
					while (Bi <= 0 || Bj != 1 || Aj != Bi)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Bi, &Bj);
						input_flush();
					}
					double *matrix_B = malloc(Bi * Bj * sizeof(M_SIZE));
					if (matrix_B == NULL)
					{
						printf("Can't allocate matrix B!\n");
						free(matrix_A);
						return MEMORY_ERROR;
					}
					ret_err = read_matrix_key(matrix_B, Bi, Bj);
					while (ret_err != EXIT_SUCCESS)
					{
						ret_err = read_matrix_key(matrix_B, Bi, Bj);
					}
					printf("Matrix A:\n");
					print_matrix_standart(matrix_A, Ai, Aj);
					printf("Matrix B:\n");
					print_matrix_standart(matrix_B, Bi, Bj);
					double *matrix_C = malloc(Ai * Bj * sizeof(M_SIZE));
					if (matrix_C == NULL)
					{
						printf("Can't allocate result matrix!\n");
						free(matrix_A);
						free(matrix_C);
						return MEMORY_ERROR;
					}
					mutiply_matrixes_standart(matrix_A, Ai, Aj, matrix_B, Bj, matrix_C);
					printf("Result matrix:\n");
					print_matrix_standart(matrix_C, Ai, Bj);
					free(matrix_A);
					free(matrix_B);
					free(matrix_C);
				}
				else if (! strcmp(choose, "file"))
				{
					int Ai, Aj, Bi, Bj;
					char dir_A[30];
					char dir_B[30];
					double *matrix_A, *matrix_B, *matrix_C;
					printf("Input file path with matrix A: ");
					scanf("%s", dir_A);

					FILE *fsrc_A = fopen(dir_A, "r");
					while (fsrc_A == NULL || (! strcmp(dir_A, "exit")))
					{
						if (! strcmp(dir_A, "exit"))
						{
							printf("Shutting down program...\n");
							return FILE_ERROR;
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_A);
						fsrc_A = fopen(dir_A, "r");
					}

					ret_err = read_matrix_file(fsrc_A, &matrix_A, &Ai, &Aj);
					if (ret_err != EXIT_SUCCESS)
					{
						printf("File is not capable of program needs!\n");
						continue;
					}
					printf("Matrix readed!\n");
					fclose(fsrc_A);

					printf("Input file path with vertical vector B: ");
					scanf("%s", dir_B);
					FILE *fsrc_B = fopen(dir_B, "r");
					while (fsrc_B == NULL || (! strcmp(dir_B, "exit")))
					{
						if (! strcmp(dir_B, "exit"))
						{
							printf("Shutting down program...\n");
							return FILE_ERROR;
						}
						printf("Wrong file or directory! Try one more time or input exit: ");
						scanf("%s", dir_B);
					}
					ret_err = read_matrix_file(fsrc_B, &matrix_B, &Bi, &Bj);
					if (ret_err != EXIT_SUCCESS)
					{
						fclose(fsrc_B);
						printf("File is not capable of program needs!\n");
						continue;
					}
					if (Bj != 1)
					{
						printf("Vector's width is not 1!\n");
						free(matrix_A);
						free(matrix_B);
						continue;
					}
					printf("Vector readed!\n");
					fclose(fsrc_B);
					
					if (Aj != Bi)
					{
						printf("Matrix can't be multiplied!\n");
						free(matrix_A);
						free(matrix_B);
						continue;
					}
					matrix_C = malloc(Ai * Bj * M_SIZE);
					if (matrix_C == NULL)
					{
						printf("Can't allocate result matrix!\n");
       					return MEMORY_ERROR;
					}

					mutiply_matrixes_standart(matrix_A, Ai, Aj, matrix_B, Bj, matrix_C);
					printf("Result matrix:\n");
					print_matrix_standart(matrix_C, Ai, Bj);

					free(matrix_A);
					free(matrix_B);
					free(matrix_C);
				}
				break;
			}
			case 3:
			{
				int row, col, percent;
				char file_name[30];
				printf("Input row and col sizes for random matrix: ");
				scanf("%d%d", &row, &col);
				printf("Input percentage of zeros: ");
				scanf("%d", &percent);
				if (generate_rand_matrix(file_name, row, col, percent) != EXIT_SUCCESS)
				{
					printf("Cant generate file with random matrix!\n");
					continue;
				}
				
				break;
			}
			default:
			{
				input_flush();
				printf("\nWrong menu option, try one more time!\n");
				continue;
			}
		}
	}

	return EXIT_SUCCESS;
}
