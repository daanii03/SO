#!/bin/bash

if test $# -lt 1 -o $# -gt 2
then
    echo "Error: Uso $0 entrada.txt [salida.txt]" >&2
    exit 1
fi

if ! test -f $1
then
    echo "El fichero de entrada no existe o no es un fichero regular." >&2
    exit 2
fi 

if test $# -eq 2
then
    OUTPUT_FILE=$2
else
    OUTPUT_FILE=default.txt
fi

# Apartado a: ordenar por primer apellido (columna 2), mostrar apellido y nota
echo "Apartado a:" > $OUTPUT_FILE
sort -t ';' -k 2 $1 | cut -d ';' -f 2,3 >> $OUTPUT_FILE

# Apartado b: ordenar por nota (columna 3) de menor a mayor, mostrar solo nota
echo "Apartado b:" >> $OUTPUT_FILE
sort -t ';' -k 3 -n $1 | cut -d ';' -f 3 >> $OUTPUT_FILE
