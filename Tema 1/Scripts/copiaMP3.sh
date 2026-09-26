#!/bin/bash

if test $# -lt 1 -o $# -gt 2
then
    echo "Error. Uso \"$0 directorio_para_buscar [directorio_para_copiar]\""
    exit 1
fi

if ! test -d $1
then
    echo "$1 no es un directorio o no existe."
    exit 2
fi
if test $# -eq 2
then
    if test -d $2
    then
        DIR=$2
    else
        echo "$2 no es un directorio o no existe."
        exit 3
    fi
else
    DIR=.
fi

find $1 -type f -name "*.mp3" | xargs -r cp -t $DIR