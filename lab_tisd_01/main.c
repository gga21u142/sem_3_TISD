#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define M_SIGNIFICANT 30
#define M_EXPONENT 5

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EMPTY_INPUT 2
#define WRONG_CHARACTER 3

typedef char integer_t [M_SIGNIFICANT + 2];

typedef struct
{
	char significant[M_SIGNIFICANT + 2];
	int exponent;
} float_t;

typedef struct
{
	char significant[M_SIGNIFICANT * 2 + 1];
	int exponent;
} number_t;

int input_integer(integer_t src_integer)
{
	size_t sign_flag = 0;
	char temp;
	if (scanf("%c", &temp) != 1)
		return EMPTY_INPUT;
	if (temp == '+' || temp == '-')
	{
		src_integer[0] = temp;
		sign_flag = 1;
	}
	
	for (size_t i = 1; i < M_SIGNIFICANT + 1; i++)
	{
		if (scanf("%c", &temp) != 1 || ! isdigit(temp))
			return WRONG_CHARACTER;
		
	}
}

int main(void)
{
	printf("Данная программа моделирует операцию умножения целого числа длиной до 30 десятичных цифр на действительное число в форме +\- m.n E +\- K, где суммарная длина мантиссы m+n содержит до 30 значащих цифр, а величина порядка K - до 5 цифр. Результат выдается в форме +\- 0.m1 E +\- K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.");
	printf("----------------------------------------------------------------------------");
	integer_t src_integer;
	src_integer[0] = '+';
	float_t src_float;
	printf("Введите целое число, как указано в условии: ");

	printf("Введите действительное число, как указано в условии: ");
	return EXIT_SUCCESS;
}
