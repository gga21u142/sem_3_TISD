#!/bin/bash

args=""
if [ "$#" -gt 2 ]; then
	args="../data/$3"
fi

if [ -n "$USE_VALGRIND" ]; then
	eval valgrind --leak-check=yes ../../main.exe "$args" < ../data/"$1" > program_output.txt
	./comparator.sh ../data/"$2" program_output.txt
else
	eval ../../main.exe "$args" < ../data/"$1" > program_output.txt
	./comparator.sh ../data/"$2" program_output.txt
fi

exit $?
