#!/bin/bash

if test $# -gt 1 
then
    echo "Error: Uso \"$0 [directorio]\"."
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

FILES=0
TOTAL_TODO=0
for RUTA in $(find "$DIR" -type f \( -name "*.c" -o -name "*.h" \))
do

    NAME=$(basename "$RUTA")
    TODO=$(grep -c "TODO" "$RUTA")
    echo "$NAME:$TODO"
    TOTAL_TODO=$(expr $TOTAL_TODO + $TODO)
    FILES=$(expr $FILES + 1)
done

echo "Número de ficheros analizados $FILES"

if test "$TOTAL_TODO" -eq 0
then
    echo "No hay tareas pendientes."
fi
exit 0