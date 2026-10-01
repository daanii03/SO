#!/bin/bash

if test $# -ne 1
then
    echo "Error. Uso $0 name_archivo"
    exit 1
fi

FILE=$1
FOUND=0

for DIR in $(echo $PATH | tr ':' '\n')
do
    OUTPUT=$(find $DIR -name $FILE)
    if ! test -z $OUTPUT
    then
        echo "$FILE está en $OUTPUT"
        FOUND=1
    fi
done

if test $FOUND -ne 1
then
    echo "$FILE no está en ningún directorio incluido en el PATH"
    exit 2
fi