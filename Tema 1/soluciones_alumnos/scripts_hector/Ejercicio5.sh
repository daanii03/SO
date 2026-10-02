#! /bin/bash

if test $# -gt 1
then
	echo "Error. Uso: $0 $1"
	exit 1;
fi

if test $# -eq 1
then
	if test -d $1
	then
		DIR=$1
	else
		echo "$1 no es un directorio"
		exit 2;
	fi
else
	DIR="./"
fi

cd $DIR

du -b $(ls) | sort -g -r | head -2 ;
