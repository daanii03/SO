#! /bin/bash

if test $# -gt 1
then
	echo "Error. Uso $0 $1(Fichero)"
	exit 1;

fi

if test $# -eq 0
then
	echo "Es necesario un parametro(nombre del fichero)"
	exit 2;
fi

FILENAME=$1



for DIRECTORY in $(echo $PATH | tr ":" " ")
do
	STRING=$(find $DIRECTORY -name "$FILENAME")
	if ! test -z $STRING
	then
		echo "El archivo $FILENAME esta en el directorio: $DIRECTORY"
	fi

done
