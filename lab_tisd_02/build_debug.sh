#!/bin/bash

gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -ggdb -Wvla -c main2.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -ggdb -Wvla -c country_t2.c
gcc -o app.exe main2.o country_t2.o -lm
