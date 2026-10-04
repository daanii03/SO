#! /bin/bash

if test $# -eq 0
then
	echo "Error. Uso $0 directorio_origen [directorio_destino]"
	exit 1;

elif test $# -gt 2
then
	echo "Error. Numero de argumentos excedido. Uso: $0 $1 $2"
fi

if ! test -d $1
then
	echo "Error. $1 no es un directorio"
	exit 2;
fi

if test $# -eq 2
then
	if test -d $2
	then
		DIRDEST=$2
	else
		echo "Error. $2 no es un directorio"
		exit 3;
	fi
else
	DIRDEST="./"
fi

DIRORI=$1

LISTMP=$(find $DIRORI -type f -name "*.mp3")

for MP3 in $LISTMP
do
	cp $MP3 $DIRDEST
done
