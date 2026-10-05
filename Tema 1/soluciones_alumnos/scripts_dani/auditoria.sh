#!/bin/bash

if test $# -lt 1 -o $# -gt 2
then
    echo "Error. Uso \"$0 extension_sin_punto [dir|.]\"."
    exit 1
fi

if grep -q "^\..." "$1"
then
    echo "La extensión no tiene que tener ."
    exit 2
else
    EXTENSION="$1"
fi

if test $# -eq 1
then
    DIR="."
else
    DIR="$2"
fi

if ! test -d $DIR
then
    echo "$DIR no es un directorio o no existe."
    exit 3
fi 

for RUTA in $(find $DIR -type f -name "*.$EXTENSION")
do

done 