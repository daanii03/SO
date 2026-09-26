#!/bin/bash

if test $# -lt 2
then
    echo "Error. Uso \"$0 dir_origen dir_destino1 [dir_destino2]\""
    exit 1
fi

for DIR in $@
do
    if ! test -d $DIR
    then
        echo "$DIR no es un directorio o no exite."
        exit 2
    fi
done

FILES=$(find $1 -type f -name "fic_[0-9][0-9][0-9][0-9]_[0-9][0-9]_[0-9][0-9].sec")

if test -z $FILES
then
    echo "No hay archivos con el formato adecuado en el directorio $1."
    exit 3
fi

CONT=1
for DIR in $@
do
    if test $CONT -gt 1
    then
        echo $FILES | xargs -r cp -t $DIR
    fi 
    CONT=$(expr $CONT + 1)
done

