#!/bin/bash

if test $# -ne 2
then
    echo "Error. Uso \"$0 (Borrar|PermisoW) <nombre_fichero>\"."
    exit 1
fi

if test $1 = Borrar
then
    if rm $2 2>/dev/null
    then
        echo "Fichero eliminado correctamente."
    else
        echo "Error: no se pudo eliminar $2." >&2
    fi
elif test $1 = PermisoW
then
    if chmod ug+w $2
    then
        echo "Permiso de W otorgado al fichero $2."
    fi 
else
    echo "Error. Uso \"$0 (Borrar|PermisoW) <nombre_fichero>\"."
    exit 2
fi