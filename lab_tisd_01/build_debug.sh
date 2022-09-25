#!/bin/bash

gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -ggdb -Wvla -c main.c
gcc -o app.exe main.o -lm
