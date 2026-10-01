                              
#!/bin/bash

if test $# -gt 1
then
        echo "Error. Poner $0 [dir]."
fi

if test -e $1
then
        LIST=$(find $1 -type f -name '*.sh')
        for ITEM in $LIST
        do
                chmod u+x $ITEM
        done
fi
