#!/bin/bash

if test $# -gt 1
then
    echo "Error. Uso $0 [dir]"
    exit 1
fi

if test $# -eq 1
then
    if test -d $1
    then
        DIR=$1
    else
        echo "El primer argumento debe ser un directorio"
        exit 2
    fi
else
    DIR=.
fi

find $DIR -name '[ab]*' | grep -v '~'