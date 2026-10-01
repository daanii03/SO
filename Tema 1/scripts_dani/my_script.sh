#!/bin/bash

# Comprobar que recibe exactamente 2 argumentos
if test $# -ne 2
then
    echo "Error. Uso \"$0 (Borrar|PermisoW) <nombre_fichero>\"." >&2
    exit 1
fi

# Comprobar la acción solicitada
if test $1 = Borrar
then
    # Intentar borrar el fichero, redirigir errores de rm a /dev/null
    if rm $2 2>/dev/null
    then
        echo "Borrado el fichero $2."
    else
        echo "Error al borrar el fichero." >&2
    fi
elif test $1 = PermisoW
then
    # Dar permiso de escritura al usuario y al grupo
    if chmod ug+w $2
    then
        echo "Permiso de W otorgado al fichero $2."
    fi
else
    # Acción no reconocida
    echo "Error. Uso \"$0 (Borrar|PermisoW) <nombre_fichero>\"." >&2
    exit 2
fi