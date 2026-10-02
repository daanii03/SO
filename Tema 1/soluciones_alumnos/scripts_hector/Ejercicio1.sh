#!/bin/bash
if test $# -ne 0
then
	echo "Error. Uso: $0"
	exit 1
fi
##Esto es un comentario
for VAR in $(ls /bin)
do
	if ! test -e /usr/share/man/man1/$VAR.1.gz ;
	then
		echo $VAR
	fi
done
