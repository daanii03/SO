
#!/bin/bash

if test $# -lt 1 -o $# -gt 2
then
    echo "Error. Uso $0 dir_destino. O $0 dir_origen dir_destino."
    exit 1
fi

if test $# -eq 1
then
    DIR_ORIGEN="."
    DIR_DESTINO="$1"
else
    DIR_ORIGEN="$1"
    DIR_DESTINO="$2"
fi

if ! test -d "$DIR_DESTINO"
then
    echo "$DIR_DESTINO no es un directorio o no existe"
    exit 2
fi

if ! test -d "$DIR_ORIGEN"
then
    echo "$DIR_ORIGEN no es un directorio o no existe"
    exit 3
fi

VULNERABLES=0

for FILE in $(find $DIR_ORIGEN -type f \( -name "*.json" -o -name "*.xml" \))
do
    if grep -q "VULNERABLE" "$FILE"
    then
        chmod o-rw $FILE
        mv $FILE $DIR_DESTINO
        VULNERABLES=$(expr $VULNERABLES + 1) 
    fi
done

if ! tar -czf "$DIR_DESTINO.tar.gz" $DIR_DESTINO
then
    echo "No se ha podido comprimir."
    exit 4
fi
if test $VULNERABLES -gt 0
then
    echo "Número de vulnerables: $VULNERABLES"
else
    echo "No se han encontrado configuraciones vulnerables."
fi
exit 0