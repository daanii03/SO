#!/bin/bash

if test $# -lt 2
then
    echo "Error. Uso $0 dir [fichero1] [fichero2] [...]" >&2
    exit 1
fi

if ! test -d $1
then
    echo "Error: $1 no es un directorio. Uso $0 dir [fichero1] [fichero2] [...]" >&2
    exit 1
fi

for i
