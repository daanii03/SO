#!/bin/bash

if ! test $# -eq 0
then 
	echo"Error. Uso: $0";
	exit 1;
fi 

for FILE in $(ls /bin)
do
	if ! test -e /usr/share/man/man1/$FILE.1.gz
	then
		echo "El mandato $FILE no tiene pagina 1 en el manual"
	fi
done
