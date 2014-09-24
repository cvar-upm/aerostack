#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage - prueba_date.sh 'date'"
    exit 1
fi
    echo $1
    ssh -t okto@okto-wlan sudo date --set='@'+$1 +%s # Atom
