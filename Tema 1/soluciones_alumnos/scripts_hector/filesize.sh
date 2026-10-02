#! /bin/bash

if test $# -lt 1
then
	echo "Error. Uso: filesize.sh directorio [fichero1] [fichero2] […] "
	exit 1;
fi

if ! test -d $1
then
	echo "$1 no es un directorio"
	exit 2;
fi

if test $# -eq 1
then 
	echo "No se han escrito ficheros"
	exit 3;
fi

DIR=$1

shift #Mueve el numero de argumentos, el $2 -> $1. (El $0 siempre se mantiene)

cd $DIR

for FILE
do
	if test -f $FILE
	then
		du -b $FILE
	else
		echo "no existe el fichero"
	fi
done
