#! /bin/bash

if test $# -gt 1
then
	echo "error. Uso $1 Directorio busqueda"
	exit 1
fi

DIR="."

if test $# -eq 1
then
	if ! test -d $1
	then
		echo "$1 no es un directorio"
		exit 2
	else
		DIR=$1
	fi
fi

#LISTFILE=$(ls -R $DIR | grep "\.[ch]$")

TOTAL=0
NUMFILES=0
for FILE in $(find $DIR -type f \( -name "*.c" -o -name "*.h" \))
do
	NAMEFILE=$(basename $FILE)
	NUMTODO=$(grep -c "TODO" $FILE)
	echo "$NAMEFILE: $NUMTODO"
	TOTAL=$( expr $TOTAL + $NUMTODO)
	NUMFILES=$(expr $NUMFILES + 1)
done

echo "Numero de ficehros analizados: $NUMFILES"

if test $TOTAL -eq 0
then
	echo "No hay tareas pendientes"
fi
