#! /bin/bash

if test $# -eq 0
then
	echo "Error. Uso $0 Directorio Directorio"
	exit 1
elif test $# -gt 2
then
	echo "Error. Numero de paramentros superado. Uso: $0 $1 $2"
	exit 2
fi

if ! test -d $1
then
	echo "$1 no es un directorio"
	exit 3

elif test $# -eq 1
then
	DIRDEST=$1
	DIRORI="."

else

	DIRDEST=$2
	DIRORI=$1
fi

NUMFALLOS=0

for FILE in $(find $DIRORI -type f -name "*.log")
do
	NUM=$(grep -c "fallo" $FILE)

	if test $NUM -gt 0
	then
		chmod a-x $FILE
		mv $FILE $DIRDEST
		NUMFALLOS=$( expr $NUMFALLOS + 1)
	fi
done

if test $NUMFALLOS -eq 0
then
	echo "No se han encontraos fallos"
else
	echo "Total archivos con fallos: $NUMFALLOS"
fi
