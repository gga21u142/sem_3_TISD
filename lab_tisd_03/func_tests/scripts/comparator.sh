#!/bin/bash

if cmp "$1" "$2" > /dev/null; then
	exit 0
else
	exit 1
fi
