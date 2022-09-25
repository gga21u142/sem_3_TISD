#!/bin/bash

gcc -std=gnu99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -ggdb -Wvla -c main.c
gcc -std=gnu99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -ggdb -Wvla -D_XOPEN_SOURCE=500 -c student_t.c
gcc -std=gnu99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -ggdb -Wvla -c students.c
gcc -o main.exe main.o student_t.o students.o -lm
