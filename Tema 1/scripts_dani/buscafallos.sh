#!/bin/bash

if test $# -lt 1 -o $# -gt 2 
then
    echo "Error. Uso \"$0 dir_destino\". O \"$0 dir_origen dir_destino\"." >&2
    exit 1
fi

if test $# -eq 1 
then
    DIR_ORIGEN="."
    DIR_DESTINO="$1"
else
    DIR_ORIGEN="$1"
    DIR_DESTINO="$2"
fi

if ! test -d "$DIR_ORIGEN"
then
    echo "Error: '$DIR_ORIGEN' no es un directorio o no existe.">&2
    exit 2
fi

if ! test -d "$DIR_DESTINO"
then
    echo "Error: '$DIR_DESTINO' no es un directorio o no existe.">&2
    exit 3
fi

FALLOS=0
for FILE in $(find "$DIR_ORIGEN" -type f -name "*.log")
do
    if grep -q "fallo" "$FILE"
    then
        FALLOS=$(expr $FALLOS + 1)
        chmod a-x "$FILE"
        mv "$FILE" "$DIR_DESTINO"
    fi
done

if ! tar -czf "${DIR_DESTINO}.tgz" "$DIR_DESTINO"
then
    echo "No se ha podido comprimir.">&2
    exit 4
fi

if test $FALLOS -eq 0
then
    echo "No se han encontrado ficheros con fallos"
else
    echo "Total de archivos que contienen fallos: $FALLOS"
fi
exit 0