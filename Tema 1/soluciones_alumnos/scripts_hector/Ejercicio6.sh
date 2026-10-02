#! /bin/bash

if $# -eq 0
then 
	echo"Error. $0 necesita un archivo .tgz"
	exit 1;
fi

if $# -gt 1
then 
	echo "Error. Uso: $0 $1"
	exit 2;
fi


DIRTEMP=$(mktemp -d) #Guarda la ruta donde se crea el archivo temporal
tar -xzf $1 -C $DIRTEMP
find $DIRTEMP -type f -size +8k | xargs rm
tar -czf $1 -C $DIRTEMP .
rm -rf $DIRTEMP

