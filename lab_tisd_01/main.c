#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#define M_SIGNIFICANT 30
#define M_EXPONENT 5

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EMPTY_INPUT 2
#define WRONG_CHARACTER 3
#define INPUT_FAILURE 4

typedef struct
{
	char sign;
	int significant[M_SIGNIFICANT + 2];
} integer_t;

typedef struct     
{
	char sign;
	int significant[M_SIGNIFICANT + 2];
	int exponent;
} float_t;             // будет выглядеть в таком же формате, что и выходное число (0. значение массива significant)

/*
typedef struct
{
	char sign;
	int significant[M_SIGNIFICANT * 2];
	int exponent;
} number_t; */

int input_integer_t(integer_t *src_integer)
{
	char temp;
	if (scanf("%c", &temp) != 1 || temp == '\n')
		return EMPTY_INPUT;
	
	size_t digits = 0;
	{
	src_integer->sign = '+';
	if (temp == '-')
		src_integer->sign = '-'; 
	else if (isdigit(temp))
	{
		if (temp != '0')
		{
			digits++;
			src_integer->significant[digits - 1] = (temp - '0');
		}
	}
	else if (temp != ' ' && temp != '+')
		return WRONG_CHARACTER;
	}
	if (scanf("%c", &temp) != 1)
		return WRONG_CHARACTER;

	while (temp != '\n')
	{
		if (digits > M_SIGNIFICANT)
			return INPUT_FAILURE;

		if (isdigit(temp))
		{
			if (temp == '0' && digits != 0)
			{
				digits++;
				src_integer->significant[digits - 1] = 0;
			}
			else if (temp != '0')
			{
				digits++;
				src_integer->significant[digits - 1] = (temp - '0');
			}
		}
		else if (temp != ' ')
			return WRONG_CHARACTER;
		
		if (scanf("%c", &temp) != 1)
			return WRONG_CHARACTER;
	}
	src_integer->significant[digits] = -1;
	return EXIT_SUCCESS;
}

int input_float_t(float_t *src_float)
{
	src_float->exponent = 0;
	char temp;
	if (scanf("%c", &temp) != 1 || temp == '\n')
		return EMPTY_INPUT;
	
	size_t significant_digits = 0;
	size_t zeros_digits = 0;
	size_t exp_add = 0;
	size_t dot_flag = 0;

	{
	src_float->sign = '+';
	if (temp == '-')
		src_float->sign = '-'; 
	else if (isdigit(temp))
	{
		if (temp != '0')
		{
			significant_digits++;
			src_float->significant[significant_digits - 1] = (temp - '0');
		}
	}
	else if (temp == '.')
		dot_flag = 1;
	else if (temp != ' ' && temp != '+')
		return WRONG_CHARACTER;

	if (scanf("%c", &temp) != 1)
		return INPUT_FAILURE;
	}

	while (temp != '\n')
	{
		if (significant_digits > M_SIGNIFICANT)
			return INPUT_FAILURE;

		if (isdigit(temp))
		{
			if (temp == '0')
				zeros_digits++;
			else
			{
				if (dot_flag || significant_digits != 0)
					for (size_t i = 0; i < zeros_digits; i++)
					{
						significant_digits++;
						src_float->significant[significant_digits - 1] = 0;
					}
				else if (dot_flag && significant_digits == 0)
				{
					exp_add = -1 * zeros_digits;
				}

				zeros_digits = 0;
				significant_digits++;
				src_float->significant[significant_digits - 1] = (temp - '0');
			}
		}
		else if (temp == '.')
		{
			if (dot_flag)
				return WRONG_CHARACTER;
			if (significant_digits != 0)
			{
				exp_add = significant_digits + zeros_digits;
				for (size_t i = 0; i < zeros_digits; i++)
				{
					significant_digits++;
					src_float->significant[significant_digits - 1] = 0;
				}
			}
			dot_flag = 1;
			zeros_digits = 0;
		}
		else if (temp == 'e' || temp == 'E')
		{
			if (! dot_flag && significant_digits != 0)
				exp_add = significant_digits + zeros_digits;

			zeros_digits = 0;

			int exp_sign = 1;
			int exp_digits = 0;
			int digit_flag = 0;
			char exp_char[M_EXPONENT];

			if (scanf("%c", &temp) != 1 || temp == '\n')
				return INPUT_FAILURE;

			if (temp == '-')
				exp_sign = -1;
			else if (isdigit(temp))
			{	
				if (temp != '0')
				{	
					digit_flag = 1;
					exp_digits++;
					exp_char[exp_digits - 1] = (temp - '0');
				}
			}
			else if (temp != ' ' && temp != '+')
				return WRONG_CHARACTER;
			
			if (scanf("%c", &temp) != 1)
				return INPUT_FAILURE;

			while (temp != '\n')
			{
				if (exp_digits > M_EXPONENT)
					return INPUT_FAILURE;
				if (isdigit(temp))
				{
					if (temp == '0' && digit_flag)
					{
						exp_digits++;
						exp_char[exp_digits - 1] = '0';
					}
					else
					{
						digit_flag = 1;
						exp_digits++;
						exp_char[exp_digits - 1] = (temp - '0');
					}
				}
				else if (temp != ' ')
					return INPUT_FAILURE;
			}

			src_float->exponent = exp_sign * atoi(exp_char) + exp_add;
			if (significant_digits == 0)
			{
				significant_digits++;
				src_float->significant[significant_digits - 1] = 0;
			}
			src_float->significant[significant_digits] = -1;
			return EXIT_SUCCESS;
		}
		else if (temp != ' ')
			return WRONG_CHARACTER;
		
		if (scanf("%c", &temp) != 1)
			return WRONG_CHARACTER;
	}
	if (! dot_flag && significant_digits != 0)
		exp_add = significant_digits + zeros_digits;
	src_float->exponent = exp_add;
	if (significant_digits == 0)
		{
			significant_digits++;
			src_float->significant[significant_digits - 1] = 0;
		}
	src_float->significant[significant_digits] = -1;
	return EXIT_SUCCESS;
}


int main(void)
{
	//printf("Данная программа моделирует операцию умножения целого числа длиной до 30 десятичных цифр на\nдействительное число в форме +/- m.n E +/- K, где суммарная длина мантиссы m+n содержит до 30\nзначащих цифр, а величина порядка K - до 5 цифр. Результат выдается в форме +/- 0.m1 E +/- K1,\nгде m1 - до 30 значащих цифр, а K1 - до 5 цифр.\n");
	printf("------------------------------------------------------------------------------------------------\n");
	integer_t src_integer;
	float_t src_float;
	
	{
	printf("Введите целое число, как указано в условии: ");
	int int_error = input_integer_t(&src_integer);
	if (int_error != 0)
	{
		printf("Введено неверное целое число!\n");
		return int_error;
	}

	printf("Введенное целое число : %c", src_integer.sign);
	for (int i = 0; src_integer.significant[i] != -1; i++)
		printf("%d", src_integer.significant[i]);
	printf("\n");
	}

	printf("Введите вещественное число, как указано в условии: ");
	int float_error = input_float_t(&src_float);

	if (float_error != 0)
	{
		printf("Введено неверное вещественное число!\n");
		return float_error;
	}

	printf("Введенное вещественное число : %c0.", src_float.sign);
	for (int i = 0; src_float.significant[i] != -1; i++)
		printf("%d", src_float.significant[i]);
	printf(" E ");
	printf("%d", src_float.exponent);
	printf("\n------------------------------------------------------------------------------------------------\n");

	return EXIT_SUCCESS;
}
