#ifndef __MATRIX_IO_H__
#define __MATRIX_IO_H__

#define M_SIZE sizeof(double)

int read_matrix_key(double *matrix, int row, int col);
void print_matrix_standart(double *matrix, int row, int col);
void input_flush(void);
int read_matrix_file(FILE *fsrc, double **matrix, int *row, int *col);

int read_matrix_sparse_key(int row, int col, double *AN, int *AI, int *AJ, int *not_zeros_A);
void print_matrix_sparse(double *arr_AN, int not_zeros_A, int *arr_AI, int Aj, int *arr_AJ);


int read_matrix_sparce_file(FILE *fsrc, int *not_zeros_A, int *row, int *col, double **arr_AN, int **arr_AI, int **arr_AJ);


#endif // __MATRIX_IO_H__