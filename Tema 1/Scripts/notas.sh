#!/bin/bash

if test $# -lt 1 -o $# -gt 2
then
    echo "Error: Uso $0 entrada.txt [salida.txt]"
    exit 1
fi

if ! test -e $1
then
    echo "El fichero de entrada no existe."
    exit 2
fi 

if test $# -eq 2
then
    OUTPUT_FILE=$2
else
    OUTPUT_FILE=default.txt
fi

echo "Apartado a:" >> $OUTPUT_FILE
for LINE in $(sort $1)
do
    echo $LINE | cut -d ';' -f 2,3 >> $OUTPUT_FILE
    
done

echo "Apartado b:" >> $OUTPUT_FILE
for LINEB in $(sort -n $1)
do
    echo $LINEB | cut -d ';' -f 3 >> $OUTPUT_FILE
done
