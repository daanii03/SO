#!/bin/bash

# Comprobar que recibe 1 o 2 argumentos
if test $# -lt 1 -o $# -gt 2
then
    echo "Error. Uso \"$0 directorio_para_buscar [directorio_para_copiar]\"" >&2
    exit 1
fi

# Comprobar que el primer argumento es un directorio
if ! test -d $1
then
    echo "$1 no es un directorio o no existe." >&2
    exit 2
fi

# Si hay segundo argumento, comprobar que es un directorio
if test $# -eq 2
then
    if test -d $2
    then
        DIR=$2
    else
        echo "$2 no es un directorio o no existe." >&2
        exit 3
    fi
else
    # Si no hay segundo argumento, copiar al directorio actual
    DIR=.
fi

# Buscar todos los .mp3 en $1 recursivamente y copiarlos a $DIR
# xargs -r: no ejecutar cp si find no encuentra nada
# cp -t $DIR: copiar al directorio destino
find $1 -type f -name "*.mp3" | xargs -r cp -t $DIR