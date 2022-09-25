#!/bin/bash

re="[-+]?[0-9]+"
if [ "$(grep -Eo "$re" "$1")" == "$(grep -Eo "$re" "$2")" ]; then
	exit 0
else
	exit 1
fi
