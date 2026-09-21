#!/bin/bash

if test $# -gt 1
then
    echo "Error. Uso: $0 [dir]."
    exit 1
fi

if test $# -eq 1
then
    if test -d $1
    then
        DIR=$1
    else
        echo "No es un directorio o no existe."
        exit 2
    fi
else
    DIR=.
fi

# Comprueba si el directorio está vacío
if test -z $(ls $DIR | tr '\n' ';')
then
    echo "El directorio está vacío"
    exit 3
fi

cd $DIR || exit 2
# ls -p hace que los directorios acaben con /, y al aplicar grep -v '/$', hace que se ignoren los directorios y solo se aplique con ficheros
# sort -nr hace que se ordene por los números (los números que devuelve du) y el r hace que se ordenen de mayor a menor, si no se aplica se puede usar tail -n 2
# du muestra el espacio ocupado por cada archivo junto a su nombre.
# La opción -b fuerza el cálculo en bytes exactos (tamaño aparente).
du -b $(ls -p $DIR | grep -v '/$')| sort -nr | head -n 2