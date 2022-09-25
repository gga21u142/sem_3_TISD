#!/bin/bash

gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c main.c 
gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c func.c 
gcc -o main.exe main.o func.o --coverage -O0 -lm
