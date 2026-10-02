#!/bin/bash 

for j in *.txt
do
	cp $j $j".bak"
done
