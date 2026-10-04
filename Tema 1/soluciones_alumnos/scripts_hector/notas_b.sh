#! /bin/bash

if test $# -lt 1
then
	echo "Error. Uso $0 fichero entrada [fichero salida]"
	exit 1
fi
if test $# -gt 2
then
	echo "Error. Numero de argumentos superado. Uso: $0 fichero_entrada [fichero salida]"
	exit 2
fi

if test $# -eq 2
then
	SALIDA=$2
else
	SALIDA=default.txt
fi

cut -d ';' -f 3 < $1 | sort >>  $SALIDA

