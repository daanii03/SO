#!/bin/bash

if test $# -ne 0
then
	echo 'Este script no necesita argumentos.'; exit 1;
fi


for BIN_FILE in `ls /bin`
do
	if ! test -e /usr/share/man/man1/$BIN_FILE.1.gz
	then
		echo $BIN_FILE
	fi
done