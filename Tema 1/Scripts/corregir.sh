#!/bin/bash

if test $# -ne 1
then
    echo "Error: Uso $0 fichero_entrada.txt"
    exit 1
fi

if ! test -f $1
then
    echo "Error: $1 no existe o no es un fichero regular" >&2
    exit 1
fi

INPUT=$(realpath $1)
USERS=$(ls /home)
for USER in $USERS
do
    cd /home/$USER
    if test -f practica.c
    then
        echo "$USER no tiene practica.c" > error.txt
    fi 

    gcc practica.c -o practica 2> error.txt
    if test -f practica
    then
        ./practica < $INPUT > salida.txt 2> error.txt
        rm practica
    fi
done