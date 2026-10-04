#! /bin/bash

if  test $# -eq 0
then
	echo "Error. Faltan paramentros. Uso: $0 (nombre del fichero) [directorio de busqueda]"
	exit 1
fi

if test $# -gt 2
then
	echo "Error. Exceso de paramentros. Uso: $0 (nombre del fichero) [directorio de busqueda]"
	exit 3
fi

DIR="./"

if  test $# -eq 2
then
	DIR=$2
fi

ls -R "$DIR" | grep "$1[0-9].txt$"
