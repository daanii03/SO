#!/bin/bash

# Comprobar que recibe al menos 2 argumentos (origen + al menos 1 destino)
if test $# -lt 2
then
    echo "Error. Uso \"$0 dir_origen dir_destino1 [dir_destino2]\"" >&2
    exit 1
fi

# Comprobar que todos los argumentos son directorios
for DIR in $@
do
    if ! test -d $DIR
    then
        echo "$DIR no es un directorio o no existe." >&2
        exit 2
    fi
done

# Buscar ficheros con formato fic_AAAA_MM_DD.sec en el directorio origen
FILES=$(find $1 -type f -name "fic_[0-9][0-9][0-9][0-9]_[0-9][0-9]_[0-9][0-9].sec")

if test -z "$FILES"
then
    echo "No hay archivos con el formato adecuado en el directorio $1."
    exit 3
fi

# Copiar los ficheros encontrados a cada directorio destino
# Usamos el contador para saltar el primer argumento (directorio origen)
CONT=1
for DIR in $@
do
    if test $CONT -gt 1
    then
        find $1 -type f -name "fic_[0-9][0-9][0-9][0-9]_[0-9][0-9]_[0-9][0-9].sec" | xargs -r cp -t $DIR
    fi
    CONT=$(expr $CONT + 1)
done
