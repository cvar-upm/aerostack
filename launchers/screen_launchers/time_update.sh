#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage - prueba_date.sh 'date'"
    exit 1
fi
    echo $1
    ssh -t asctec@10.0.157.10 sudo date --set='@'+$1 +%s # Atom
    #ssh -t asctec@10.0.100.3 sudo date --set='@'+$1 +%s # Mastermind
