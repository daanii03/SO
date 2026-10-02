#! /bin/bash

if ! test $# -eq  1
then
	echo "Error. Uso: $0 $1 [fichero.txt]"
	exit 1;
fi


if ! test -f $1
then
	echo "Error. $1 debe de ser un fichero.txt"
	exit 2
fi

USERS=$(ls /home)

for USER in $USERS
do
	cd /home/$USER
	if test -f practica.c
	then
		gcc practica.c -o practica 2> error.txt  #Esto genera el ejecutable, y si se genera un error lo redirige a "error.txt
		./practica <$1 > salida.txt 2> error.txt #Ejecuta, recibe como entrada el $1 y redirige la salida segun si el error
		rm -f practica
	else
		echo "No existe el fichero practica.c" > error.txt
	fi
done

