#!/bin/bash

if test $# -gt 1
then
	echo "Error. Uso: $0 $1"
	exit 1;
fi

if test $# -eq 1
then
	if ! test -d $1
	then
		echo "$1 debe de ser un directorio"
		exit 2;
	else
		DIR=$1
	fi
else
	DIR="./"
fi

for FILE in $(find $DIR -name "*.sh")
do
	chmod u+x $FILE
done
