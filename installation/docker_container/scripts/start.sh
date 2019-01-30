#!/bin/bash

if [[ "$#" -lt 2 ]]; then
  echo "Usage ./start.sh <working_dir> <image_name> [<instance_name> <gpu_support>]"
  exit 1
fi

cwd=$(realpath $1); shift
img_name=$1; shift
instance_name=$1; shift
graphic_support="$#";
port=11311

if [[ -z $instance_name ]]; then
  instance_name="${img_name}_instance"
fi

# globals: instance_name
set_name(){
  local running_instances=$(sudo docker ps -a -f name=$instance_name | wc -l)
  running_instances=$(( $running_instances -1 ))
  if [[ $running_instances -gt 0 ]]; then
    instance_name="${instance_name}_${running_instances}"
  fi
}

# globals: port
set_port(){
  local running_instances=$(sudo docker ps -a -q)
  local check_port=$port
  for instance in ${running_instances[@]}; do
    port_taken=$(sudo docker port $instance | grep -Eo "[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}:$check_port")
    if [[ $(echo $port_taken | wc -l) -gt 0 ]]; then
      check_port=$(( ++check_port ))
    fi
  done
  port=$check_port
}

set_name
set_port

mkdir -p $cwd/{catkin_ws,workspace,gazebo_ws}

args="--env=DISPLAY --env=QT_X11_NO_MITSHM=1 "

if [[ $graphic_support -eq 1 ]]; then
  # are these really necessary?
  args+="--privileged "
  args+="--device=/dev/snd:/dev/snd "
  args+="--device=/dev/dri:/dev/dri "
fi

#args+='--volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" '
args+="--volume=$cwd/catkin_ws:/root/catkin_ws "
args+="--volume=$cwd/workspace:/root/workspace "
args+="--volume=$cwd/gazebo_ws:/root/gazebo_ws "
args+="-p $port:11311 "
args+="--name $instance_name "
args+="$img_name "

echo "starting with args --volume=\"/tmp/.X11-unix:/tmp/.X11-unix:rw\" $args"

# ToDo := Test if there is a previous docker running
sudo docker run -dt --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" $args
