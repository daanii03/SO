#!/bin/bash

if test $# -lt 1
then
    echo "Error. Uso $0 dir [fichero1] [fichero2] [...]" >&2
    exit 1
fi

if ! test -d $1
then
    echo "Error: $1 no es un directorio o no existe. Uso $0 dir [fichero1] [fichero2] [...]" >&2
    exit 1
fi

DIR=$1
i=0
cd $DIR
for FILE in $@
do
    if test $i -gt 0
    then
        if test -f $FILE
        then
            du -b $FILE
        else
            echo "El fichero '$FILE' no existe ni en su ruta ni en '$DIR'."
        fi
    fi
    i=$(expr $i + 1)
done
