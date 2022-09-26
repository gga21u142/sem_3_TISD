#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "prints.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
	number_t src_integer;
	number_t src_float;

	print_info();
	//Ввод целого числа

	printf("Введите целое число, как указано в условии: ");
	int int_error = input_integer(&src_integer);
	if (int_error != 0)
	{
		print_input_error_message(int_error);
		return int_error;
	}

	// Вывод целого числа в стандартном виде
	/* 
	printf("Введенное целое число : ");
	print_number_t(&src_integer); */

	//Ввод вещественного числа

	printf("\nВведите вещественное число, как указано в условии: ");
	int float_error = input_float(&src_float);
	if (float_error != 0)
	{
		print_input_error_message(float_error);
		return float_error;
	}

	// Вывод вещественного числа в стандартном виде
	/* 
	printf("Введенное вещественное число : ");
	print_number_t(&src_float); */

	answer_t dst_answer;
	int multi_error = multiply_integer_float(&src_integer, &src_float, &dst_answer);
	if (multi_error != 0)
	{
		printf("Операция умножения не удалась!\n");
		return multi_error;
	}

	print_answer_t(&dst_answer);

	return EXIT_SUCCESS;
}