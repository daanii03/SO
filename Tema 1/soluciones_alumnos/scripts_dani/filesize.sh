#!/bin/bash

# ============================================================
# APARTADO A: Comprobar número de argumentos y que el primer
#             argumento es un directorio existente.
# ============================================================

# Al menos 1 argumento (el directorio)
if test $# -lt 1
then
    echo "Error. Uso: $0 directorio [fichero1] [fichero2] [...]" >&2
    exit 1
fi

# Comprobar que el primer argumento existe Y es un directorio
if ! test -d "$1"
then
    echo "Error: '$1' no existe o no es un directorio." >&2
    echo "Uso: $0 directorio [fichero1] [fichero2] [...]" >&2
    exit 1
fi

# Si solo se pasa el directorio (sin ficheros), mostrar mensaje y salir
if test $# -eq 1
then
    echo "No existen ficheros."
    exit 0
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

# ============================================================
# APARTADO C: Cambios para escribir en un fichero de salida
# ============================================================
# Para que el resultado se escriba en un fichero pasado como
# segundo argumento, habría que hacer los siguientes cambios:
#
# 1) El formato de uso pasaría a ser:
#      filesize.sh directorio fichero_salida [fichero1] [fichero2] [...]
#
# 2) Cambiar la comprobación de argumentos mínimos a 2:
#      if test $# -lt 2
#
# 3) Guardar el segundo argumento como fichero de salida:
#      SALIDA=$2
#
# 4) Cambiar el contador i para que empiece en 0 y solo procese
#    ficheros a partir del tercer argumento (i -gt 1):
#      i=0
#      if test $i -gt 1
#
# 5) Redirigir cada echo de resultado al fichero de salida con >>:
#      du -b $FILE >> $SALIDA