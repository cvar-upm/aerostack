#!/bin/bash

touch $AEROSTACK_STACK/stack/utils/audio_common/CATKIN_IGNORE
git clone https://github.com/ros-perception/opencv_apps $AEROSTACK_STACK/stack_devel/opencv_apps
sudo apt-get install git build-essential cmake qt5-default qtscript5-dev libssl-dev qttools5-dev qttools5-dev-tools qtmultimedia5-dev libqt5svg5-dev libqt5webkit5-dev libsdl2-dev libasound2 libxmu-dev libxi-dev freeglut3-dev libasound2-dev libjack-jackd2-dev libxrandr-dev libqt5xmlpatterns5-dev libqt5xmlpatterns5
git clone https://github.com/ros-drivers/joystick_drivers $AEROSTACK_STACK/stack_devel/joystick_drivers
sudo apt-get install libusb-dev
git clone https://github.com/OctoMap/octomap_ros $AEROSTACK_STACK/stack_devel/octomap_ros

cd $AEROSTACK_STACK
find ./ -type f -readable -writable -exec sed -i "s/logError/CONSOLE_BRIDGE_logError/g" {} \;
find ./ -type f -readable -writable -exec sed -i "s/logInform/CONSOLE_BRIDGE_logInform/g" {} \;
find ./ -type f -readable -writable -exec sed -i "s/logDebug/CONSOLE_BRIDGE_logDebug/g" {} \;
find ./ -type f -readable -writable -exec sed -i "s/logWarn/CONSOLE_BRIDGE_logWarn/g" {} \;

sudo apt-get install libspnav-dev

touch $AEROSTACK_STACK/stack/hardware_interface/drivers_sensors/driver_usb_cam/usb_cam/CATKIN_IGNORE
touch $AEROSTACK_STACK/stack/hardware_interface/drivers_sensors/utils/rosserial/CATKIN_IGNORE


touch $AEROSTACK_STACK/stack/hardware_interface/drivers_platforms/driver_asctec_autopilot/CATKIN_IGNORE
touch $AEROSTACK_STACK/stack/simulation_system/drone_simulator/asctec_pelican_simulator_process/CATKIN_IGNORE
touch $AEROSTACK_STACK/stack/hardware_interface/drivers_platforms/driver_parrot_ardrone/CATKIN_IGNORE
touch $AEROSTACK_STACK/stack/logging/dronePelicanLoggerROSModule/CATKIN_IGNORE




git clone https://github.com/abstrakraft/cwiid $AEROSTACK_STACK/stack_devel/cwiid 
sudo apt-get install libcwiid-dev



git clone https://github.com/Parrot-Developers/libARCommands $AEROSTACK_STACK/stack_devel/libARCommands
touch $AEROSTACK_STACK/stack/hardware_interface/drivers_platforms/driver_dji_matrice/CATKIN_IGNORE

cd $AEROSTACK_STACK/stack/simulation_system/drone_simulator/rotors_simulator_gazebo/rotors_simulator
git checkout -f  stable/gazebo9 

cd $AEROSTACK_STACK/stack/hardware_interface/drivers_platforms/driver_bebop/bebop_autonomy
git checkout -f indigo-devel

echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$AEROSTACK_WORKSPACE/devel/lib/parrot_arsdk" >> ~/.bashrc

sudo ln -s /usr/include/eigen3/Eigen /usr/local/include/Eigen

