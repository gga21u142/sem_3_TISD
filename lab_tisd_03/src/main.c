#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "matrix_proc.h"
#include "matrix_io.h"
#include "time_exp.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2


int main(void)
{
	printf("\nProgramm is processing with matrix, to start choose the command:\n0) Exit the program\n1) Multiply matrix on vector by linked arrays method.\n2) Multiply matrix on vector by standart method.\n3) Compare work time for random matrix between standart and linked arrays method.\n");
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
					if (scanf("%d%d", &Ai, &Aj) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					input_flush();
					while (Ai <= 0 || Aj <= 0)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Ai, &Aj);
						input_flush();
					}

					int not_zeros_A = 0;
					double *arr_AN = calloc(Ai * Aj, M_SIZE);
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
					///
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 5 || (! strcmp(choose, "pos") && ! strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_sparse_key(Ai, Aj, arr_AN, arr_AI, arr_AJ, &not_zeros_A);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_sparse_key(Ai, Aj, arr_AN, arr_AI, arr_AJ, &not_zeros_A);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						printf("\nInput positions (input -1 -1 if you want to stop): ");
						while (scanf("%d%d", &it, &jt) == 2)
						{
							input_flush();
							if (it == -1 && jt == -1)
								break;
							printf("\nInput number: ");
							if (scanf("%lf", &tempd) == 1 && it < Ai && jt < Aj)
								arr_AN[it * Ai + jt] = tempd;
							else
								break;
							printf("\nInput positions (input -1 -1 if you want to stop): ");
						}
						read_matrix_sparse_key_coord(Ai, Aj, arr_AN, arr_AI, arr_AJ, &not_zeros_A);
					}
					///
					


					printf("Input vertical vector B sizes: ");
					
					if (scanf("%d%d", &Bi, &Bj) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					while (Bi <= 0 || Bj != 1 || Aj != Bi)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Bi, &Bj);
						input_flush();
					}


					int not_zeros_B = 0;
					double *arr_BN = calloc(Bi * Bj, M_SIZE);
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
					///
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 5 || (! strcmp(choose, "pos") && ! strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_sparse_key(Bi, Bj, arr_BN, arr_BI, arr_BJ, &not_zeros_B);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_sparse_key(Bi, Bj, arr_BN, arr_BI, arr_BJ, &not_zeros_B);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						printf("\nInput positions (input -1 -1 if you want to stop): ");
						while (scanf("%d%d", &it, &jt) == 2)
						{
							input_flush();
							if (it == -1 && jt == -1)
								break;
							printf("\nInput number: ");
							if (scanf("%lf", &tempd) == 1 && it < Bi && jt < Bj)
								arr_AN[it * Bi + jt] = tempd;
							else
								break;
							printf("\nInput positions (input -1 -1 if you want to stop): ");
						}
						read_matrix_sparse_key_coord(Bi, Bj, arr_BN, arr_BI, arr_BJ, &not_zeros_B);
					}
					///
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
					if (scanf("%d%d", &Ai, &Aj) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					input_flush();
					while (Ai <= 0 || Aj <= 0)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Ai, &Aj);
						input_flush();
					}
					double *matrix_A = calloc(Ai * Aj, sizeof(M_SIZE));
					if (matrix_A == NULL)
					{
						printf("Can't allocate matrix A!\n");
						return MEMORY_ERROR;
					}
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 3 || (! strcmp(choose, "pos") && ! strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_key(matrix_A, Ai, Aj);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_key(matrix_A, Ai, Aj);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						printf("\nInput positions (input -1 -1 if you want to stop): ");
						while (scanf("%d%d", &it, &jt) == 2)
						{
							input_flush();
							if (it == -1 || jt == -1)
								break;
							printf("\nInput number: ");
							if (scanf("%lf", &tempd) == 1 && it < Ai && jt < Aj)
								matrix_A[it * Ai + jt] = tempd;
							else
								break;
							printf("\nInput positions (input -1 -1 if you want to stop): ");
						}
					}
					printf("Input vertical vector B sizes: ");
					if (scanf("%d%d", &Bi, &Bj) != 2)
					{
						input_flush();
						printf("Wrong sizes!\n");
						continue;
					}
					while (Bi <= 0 || Bj != 1 || Aj != Bi)
					{
						printf("Wrong sizes! Try one more time: ");
						scanf("%d%d", &Bi, &Bj);
						input_flush();
					}
					double *matrix_B = calloc(Bi * Bj, sizeof(M_SIZE));
					if (matrix_B == NULL)
					{
						printf("Can't allocate matrix B!\n");
						free(matrix_A);
						return MEMORY_ERROR;
					}
					printf("Do you want to inpu all or by pos? Input pos or all: ");
					scanf("%s", choose);
					while (strlen(choose) > 3 || (! strcmp(choose, "pos") && ! strcmp(choose, "all")))
					{
						printf("\nWrong option, try one more time!\n");
						input_flush();
						printf("\nInput 'pos' or 'all': ");
						scanf("%s", choose);
					}
					if (! strcmp(choose, "all"))
					{
						ret_err = read_matrix_key(matrix_B, Bi, Bj);
						while (ret_err != EXIT_SUCCESS)
						{
							ret_err = read_matrix_key(matrix_B, Bi, Bj);
						}
					}
					else
					{
						double tempd;
						int it, jt;
						printf("\nInput positions (input -1 -1 if you want to stop): ");
						while (scanf("%d%d", &it, &jt) == 2)
						{
							input_flush();
							if (it == -1 || jt == -1)
								break;
							printf("\nInput number: ");
							if (scanf("%lf", &tempd) == 1 && it < Bi && jt < Bj)
								matrix_B[it * Bi + jt] = tempd;
							else
								break;
							printf("\nInput positions (input -1 -1 if you want to stop): ");
						}

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
				printf("Input row and col sizes for random matrix: ");
				scanf("%d%d", &row, &col);
				input_flush();
				printf("Input percentage of zeros: ");
				scanf("%d", &percent);
				input_flush();
				if (generate_rand_matrix("matrix_A.txt", row, col, percent) != EXIT_SUCCESS)
				{
					printf("Cant generate file with random matrix!\n");
					continue;
				}
				if (generate_rand_matrix("vector_B.txt", row, 1, 0) != EXIT_SUCCESS)
				{
					printf("Cant generate file with random vector!\n");
					continue;
				}
				int not_zeros_A = 0;
				double *arr_AN;
				int *arr_AI, *arr_AJ;
				int not_zeros_B = 0;
				double *arr_BN;
				int *arr_BI, *arr_BJ;
				int Bj;
				int mem_A, mem_B, mem_C;
				int mem_A_sparce, mem_B_sparce, mem_C_sparce;
				// подcчет времени и памяти для разреженного метода
				FILE *fsrc_A = fopen("matrix_A.txt", "r");
				read_matrix_sparce_file(fsrc_A, &not_zeros_A, &row, &col, &arr_AN, &arr_AI, &arr_AJ);
				mem_A_sparce = row * col * M_SIZE + row * col * sizeof(int) + col * sizeof(int);

				FILE *fsrc_B = fopen("vector_B.txt", "r");
				read_matrix_sparce_file(fsrc_B, &not_zeros_B, &col, &Bj, &arr_BN, &arr_BI, &arr_BJ);
				mem_B_sparce = row * 1 * M_SIZE + row * 1 * sizeof(int) + 1 * sizeof(int);


				int not_zeros_C = 0;
				double *arr_C = calloc(row * 1, M_SIZE);
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
				double *arr_CN = malloc(row * 1 * M_SIZE);
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
				int *arr_CI = malloc(row * 1 * sizeof(int));
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
				int *arr_CJ = malloc(1 * sizeof(int));
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
				for (int i = 0; i < 1; i++)
					arr_CJ[i] = -1;
				
				mem_C_sparce = row * 1 * M_SIZE + row * 1 * M_SIZE + row * 1 * sizeof(int) + 1 * sizeof(int);

				struct timespec t_beg, t_end;
				unsigned long long sparce_time, standart_time;
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
				mutiply_matrix_vector_sparse(not_zeros_A, arr_AN, arr_AI, col, arr_AJ, not_zeros_B, arr_BN, arr_BI, row, arr_C, &not_zeros_C, arr_CN, arr_CI, arr_CJ);
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	

				
				sparce_time = calc_elapsed_time(&t_beg, &t_end);
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
				

				// подcчет времени и памяти для стандартного метода
				rewind(fsrc_A);
				rewind(fsrc_B);
				double *matrix_A, *matrix_B, *matrix_C;
				read_matrix_file(fsrc_A, &matrix_A, &row, &col);
				mem_A = row * col * M_SIZE;
				fclose(fsrc_A);
				read_matrix_file(fsrc_B, &matrix_B, &col, &Bj);
				mem_B = row * 1 * M_SIZE;
				fclose(fsrc_B);

				matrix_C = malloc(row * 1 * M_SIZE);
				if (matrix_C == NULL)
				{
					printf("Can't allocate result matrix!\n");
       				return MEMORY_ERROR;
				}

				mem_C = row * 1 * M_SIZE;
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
				mutiply_matrixes_standart(matrix_A, row, col, matrix_B, Bj, matrix_C);
				clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);	

				
				standart_time = calc_elapsed_time(&t_beg, &t_end);
				free(matrix_A);
				free(matrix_B);
				free(matrix_C);
				

				printf("\nFor standart method was used bytes:\n");
				printf("For matrix A: %10d\n", mem_A);
				printf("For vector B: %10d\n", mem_B);
				printf("For vector C: %10d\n", mem_C);
				printf("\nIn total was used: %10d bytes or %10.1lf Kbytes or %10.1lf Gbytes\n", mem_A + mem_B + mem_C, (mem_A + mem_B + mem_C) / 1024.0, (mem_A + mem_B + mem_C) / 1024.0 / 1024.0);

				printf("\nFor linked arrays method was used bytes:\n");
				printf("For matrix A: %10d\n", mem_A_sparce);
				printf("For vector B: %10d\n", mem_B_sparce);
				printf("For vector C: %10d\n", mem_C_sparce);
				printf("\nIn total was used: %10d bytes or %10.1lf Kbytes or %10.1lf Gbytes\n", mem_A_sparce + mem_B_sparce + mem_C_sparce, (mem_A_sparce + mem_B_sparce + mem_C_sparce) / 1024.0, (mem_A_sparce + mem_B_sparce + mem_C_sparce) / 1024.0 / 1024.0);

				printf("\nTime that was used to multiply matrix on vector in microseconds:\n");
				printf("| standart: %15lld | linked arrays: %15lld |\n", standart_time ,sparce_time);


				FILE *fdst_st, *fdst_sp;
				fdst_st = fopen("time_for_standart.txt", "a+");
				fdst_sp = fopen("time_for_sparce.txt", "a+");
				fprintf(fdst_st, "%d %d %d %lld\n", row, col, percent, standart_time);
				fprintf(fdst_sp, "%d %d %d %lld\n", row, col, percent, sparce_time);
				fclose(fdst_st);
				fclose(fdst_sp);
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
