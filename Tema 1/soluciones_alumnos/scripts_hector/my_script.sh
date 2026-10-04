#! /bin/bash

if ! test $# -eq 2
then
	echo "Error. Uso: $0 Borrar/PermisoW nombre_fichero"
	exit 1
fi

if ! test -f $2
then
	echo "Error. $2 no es un fichero"
	exit 2
fi

if test $1 = "Borrar"
then
	rm $2
	if test $? -eq 0
	then
		echo "Borrado el fichero $2"
	else
		echo "Error al borrar $2"
	fi

elif test $1 = "PermisoW"
then
	chmod ug+w $2
	echo "Permiso de W otorgado al fichero $2"
else
	echo "La orden $1 no existe"
	exit 3
fi
