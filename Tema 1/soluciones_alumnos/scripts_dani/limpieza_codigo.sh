#!/bin/bash

if test $# -gt 1
then
    echo "Error. Uso \"$0 [dir]\"."
    exit 1
fi

if test $# -eq 1
then
    DIR="$1"
else
    DIR="."
fi

if ! test -d "$DIR"
then 
    echo "$DIR no es un directorio o no existe."
    exit 2
fi


TOTAL_FILES=0
TOTAL_DEBUG=0
for RUTA in $(find "$DIR" -type f \( -name "*.js" -o -name "*.ts" \))
do
    DEBUG=$(grep -c "DEBUG" "$RUTA")
    echo "$RUTA:$DEBUG"
    TOTAL_DEBUG=$(expr $TOTAL_DEBUG + $DEBUG)
    TOTAL_FILES=$(expr $TOTAL_FILES + 1)
done

echo "Número de ficheros analizados: $TOTAL_FILES"

if test $TOTAL_DEBUG -eq 0
then
    echo "El código está limpio para producción."
fi