#ifndef __MATRIX_PROC_H__
#define __MATRIX_PROC_H__


void mutiply_matrixes_standart(double *matrix_A, int Ai, int Aj, double *matrix_B, int Bj, double *matrix_C);
void mutiply_matrix_vector_sparse(int not_zeros_A, double *arr_AN, int *arr_AI, int Aj, int *arr_AJ, int not_zeros_B, double *arr_BN, int *arr_BI, int Bj, double *arr_C, int *not_zeros_C, double *arr_CN, int *arr_CI, int *arr_CJ);

#endif // __MATRIX_PROC_H__