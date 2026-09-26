#!/bin/bash

if test $# -lt 1 -o $# -gt 2
then
    echo "Error. Uso \"$0 nombre_fichero [dir]\"."
    exit 1
fi

if test $# -eq 2
then
    DIR=$2
else
    DIR=.
fi

find $DIR -type f -name "$1[0-9].txt" -printf "%f\n"
