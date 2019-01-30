#!/bin/bash

if [[ "$#" -lt 1 ]]; then
  echo "Usage ./launch_docker.sh <container_name> [<zsh> (default:true)]"
  exit 1
fi

container_name=$1; shift
shell=zsh

if [[ "$#" -gt 0 ]]; then
  shell=$1; shift
fi

dock_auth=$(sudo docker inspect --format='{{ .Config.Hostname }}' $container_name)

# xhost ensures the container is able to modify the X11 socket
if [[ ! `xhost | tail -n 1` = *"$dock_auth"* ]]; then
  xhost +local:$dock_auth
fi

sudo docker exec -it -e SHELL="/usr/bin/$shell" $container_name $shell

if [[ `xhost | tail -n 1` = *"$dock_auth"* ]]; then
  xhost -local:$dock_auth
fi
