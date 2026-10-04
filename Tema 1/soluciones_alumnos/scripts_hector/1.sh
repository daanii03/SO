#! /bin/bash

if test $# -lt 2
then
	echo "Error. Uso: $0 Dir_origen Dir_dest1 Dir_dest2 ..."
	exit 1
fi

for DIR
do
	if ! test -d $DIR
	then
		echo "$DIR no es un directorio"
		exit 2
	fi
done

DIRORI=$1

LISTFILE=$(find $DIRORI -type f -name "fic_[0-9][0-9][0-9][0-9]_[0-9][0-9]_[0-9][0-9].sec")

shift

for DIRDEST
do
	for FILE in $LISTFILE
	do
		cp $FILE $DIRDEST
	done
done


