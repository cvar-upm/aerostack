#!/bin/bash

if [[ "$#" -lt 1 ]]; then
  echo "Usage ./stop_docker.sh <container_name>"
  exit 1
fi

container_name=$1; shift

sudo docker stop $container_name 
