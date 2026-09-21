#!/bin/bash
echo "Se han recibido $# argumentos: $*"
echo "Argumentos impresos de uno en uno:"
echo "	Argumento 0: $0"
contador=1
for i in $@
do
	echo "	Argumento $contador: $i"
	contador=$(($contador+1))
done
exit 0
