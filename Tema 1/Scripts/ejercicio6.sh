#!/bin/bash

if test $# -ne 1
then
    echo "Error. Uso: $0 archivo.tgz"
    exit 1
fi

DIR_TMP=$(mktemp -d)
FILE=$1

tar -xzf $FILE -C $DIR_TMP 
find $DIR_TMP -type f -size +8k -delete
tar -czf $FILE -C $DIR_TMP .
rm -rf $DIR_TMP
