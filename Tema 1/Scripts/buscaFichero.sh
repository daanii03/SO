#!/bin/bash

# Comprobar que recibe 1 o 2 argumentos
if test $# -lt 1 -o $# -gt 2
then
    echo "Error. Uso \"$0 nombre_fichero [dir]\"." >&2
    exit 1
fi

# Si hay segundo argumento, comprobar que es un directorio
if test $# -eq 2
then
    if ! test -d $2
    then
        echo "Error: $2 no es un directorio o no existe." >&2
        exit 1
    fi
    DIR=$2
else
    # Si no hay segundo argumento, buscar desde el directorio actual
    DIR=.
fi

# Buscar ficheros que se llamen $1 seguido de un dígito (0-9) con extensión .txt
# -type f: solo ficheros regulares
# -name: patrón de nombre
# -printf "%f\n": imprime solo el nombre del fichero (sin ruta)
find $DIR -type f -name "$1[0-9].txt" -printf "%f\n"
