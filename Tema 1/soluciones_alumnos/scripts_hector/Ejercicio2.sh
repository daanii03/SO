#! /bin/bash

if test $# -gt 1 
then
	echo "Error.Uso: $0 (Directory)"; exit 1;

elif test $# -eq 1
then
	if test -d $1
	then
		WDIR = $1
	else
		echo "$1 no existe o o es un directorio"; exit 2;
	fi
else
	WDIR="./"
fi

for FILE in $(find $WDIR -name "*.sh"
do
	chmod u+x $FILE
done




