#!/bin/bash

echo "-----------------------"
echo "Installing ncurses"
echo "-----------------------"
sudo apt-get install libncurses5
sudo apt-get install ncurses-bin
sudo apt-get install ncurses-dev
sudo apt-get install libncursesw5-dev

echo "-----------------------"
echo "Installing boost"
echo "-----------------------"
sudo apt-get install libboost1.54-dev

echo "-----------------------"
echo "Installing expect"
echo "-----------------------"
sudo apt-get install expect

echo "---------------------------"
echo "Installing Lapack, Blas, protobuf and F2C Libraries"
echo "---------------------------"
sudo apt-get install liblapack3 liblapack-dev
sudo apt-get install libblas3 libblas-dev
sudo apt-get install libf2c2 libf2c2-dev
sudo apt-get install protobuf-compiler

echo "---------------------------"
echo "Installing ARdrone Autonomy dependencies"
echo "---------------------------"
sudo apt-get install libsdl1.2-dev
sudo apt-get install libudev-dev
sudo apt-get install libiw-dev

if [ "$ROS_DISTRO" = "kinetic" ]
then
	echo "----------------------------"
	echo "Install driver common required in kinectic"
	echo "----------------------------"
	mkdir -p /tmp/driver_common/src
	cd /tmp/driver_common/src
	git clone https://github.com/ros-drivers/driver_common
	cd ..
	catkin_make install -DCMAKE_INSTALL_PREFIX=/tmp/ros/$ROS_DISTRO
	sudo cp -R /tmp/ros/$ROS_DISTRO /opt/ros/
	rm -rf /tmp/ros
	rm -rf /tmp/driver_common

	echo "----------------------------"
	echo "Install keyboard required in kinectic"
	echo "----------------------------"
	mkdir -p /tmp/keyboard/src
	cd /tmp/keyboard/src
	git clone https://github.com/lrse/ros-keyboard.git
	cd ..
	catkin_make install -DCMAKE_INSTALL_PREFIX=/tmp/ros/$ROS_DISTRO
	sudo cp -R /tmp/ros/$ROS_DISTRO /opt/ros/
	rm -rf /tmp/ros
	rm -rf /tmp/keyboard

	echo "---------------------------"
	echo "Installing Sound Play & Dependencies"
	echo "---------------------------"
	sudo apt-get install ros-$ROS_DISTRO-audio-common
	sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev

	echo "------------------------------------------------------"
	echo "Installing qwt library"
	echo "------------------------------------------------------"
	sudo apt-get install libqwt-headers
	sudo apt-get install libqwt-qt5-dev
	sudo apt-get install libzbar-dev

fi

if [ "$ROS_DISTRO" = "melodic" ]
	then
	echo "----------------------------"
	echo "Install driver common required in melodic"
	echo "----------------------------"
	mkdir -p /tmp/driver_common/src
	cd /tmp/driver_common/src
	git clone https://github.com/ros-drivers/driver_common
	cd ..
	catkin_make install -DCMAKE_INSTALL_PREFIX=/tmp/ros/$ROS_DISTRO
	sudo cp -R /tmp/ros/$ROS_DISTRO /opt/ros/
	rm -rf /tmp/ros
	rm -rf /tmp/driver_common

	echo "----------------------------"
	echo "Install keyboard required in melodic"
	echo "----------------------------"
	mkdir -p /tmp/keyboard/src
	cd /tmp/keyboard/src
	git clone https://github.com/lrse/ros-keyboard.git
	cd ..
	catkin_make install -DCMAKE_INSTALL_PREFIX=/tmp/ros/$ROS_DISTRO
	sudo cp -R /tmp/ros/$ROS_DISTRO /opt/ros/
	rm -rf /tmp/ros
	rm -rf /tmp/keyboard
	
	echo "------------------------------------------------------"
	echo "Installing qwt library"
	echo "------------------------------------------------------"
	sudo apt-get install git build-essential cmake qt5-default qtscript5-dev libssl-dev qttools5-dev qttools5-dev-tools qtmultimedia5-dev libqt5svg5-dev libqt5webkit5-dev libsdl2-dev libasound2 libxmu-dev libxi-dev freeglut3-dev libasound2-dev libjack-jackd2-dev libxrandr-dev libqt5xmlpatterns5-dev libqt5xmlpatterns5

	echo "---------------------------"
	echo "Installing opencv_apps"
	echo "---------------------------"
	sudo apt-get install ros-opencv-apps

	echo "---------------------------"
	echo "Installing joystick_drivers"
	echo "---------------------------"
	sudo apt-get install ros-melodic-joystick-drivers

	echo "---------------------------"
	echo "Installing lib_usb"
	echo "---------------------------"
	sudo apt-get install libusb-dev

	echo "---------------------------"
	echo "Installing octomap"
	echo "---------------------------"
	sudo apt-get install ros-melodic-octomap 

	echo "---------------------------"
	echo "Installing spnav"
	echo "---------------------------"
	sudo apt-get install libspnav-dev 

	echo "---------------------------"
	echo "Installing cwiid"
	echo "---------------------------"
	sudo apt install libcwiid-dev 

	echo "---------------------------"
	echo "Updating mavros logging system"
	echo "---------------------------"
	cd $AEROSTACK_STACK/stack/hardware_interface/drivers_platforms/driver_pixhawk/mavros
	find ./ -type f -readable -writable -exec sed -i "s/[[:blank:]]logError/ CONSOLE_BRIDGE_logError/g" {} \;
	find ./ -type f -readable -writable -exec sed -i "s/[[:blank:]]logInform/ CONSOLE_BRIDGE_logInform/g" {} \;
	find ./ -type f -readable -writable -exec sed -i "s/[[:blank:]]logDebug/ CONSOLE_BRIDGE_logDebug/g" {} \;
	find ./ -type f -readable -writable -exec sed -i "s/[[:blank:]]logWarn/ CONSOLE_BRIDGE_logWarn/g" {} \;
	cd $AEROSTACK_STACK
	
	echo "---------------------------"
	echo "Installing libARCommands"
	echo "---------------------------"
	git clone https://github.com/Parrot-Developers/libARCommands $AEROSTACK_STACK/libraries/libARCommands

	echo "------------------------------------------------------"
	echo "Updating gazebo"
	echo "------------------------------------------------------"
	cd $AEROSTACK_STACK/stack/simulation_system/rotors_simulator
	git checkout -f  stable/gazebo9 
	
	echo "------------------------------------------------------"
	echo "Exporting parrot_arsdk lib"
	echo "------------------------------------------------------"
	echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$AEROSTACK_WORKSPACE/devel/lib/parrot_arsdk" >> ~/.bashrc

	echo "------------------------------------------------------"
	echo "Updating Eigen"
	echo "------------------------------------------------------"
	sudo ln -s /usr/include/eigen3/Eigen /usr/local/include/Eigen

	echo "---------------------------"
	echo "Installing Sound Play & Dependencies"
	echo "---------------------------"
	sudo apt-get install ros-$ROS_DISTRO-audio-common
	sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
	touch  $AEROSTACK_STACK/stack_deprecated/audio_common/CATKIN_IGNORE
fi

echo "------------------------------------------------------"
echo "Updating driver_bebop"
echo "------------------------------------------------------"
cd $AEROSTACK_STACK/stack/hardware_interface/drivers_platforms/driver_bebop/bebop_autonomy
git checkout -f indigo-devel

echo "---------------------------"
echo "Installing Voices for Sound Play"
echo "---------------------------"
sudo apt-get install festlex-cmu
sudo apt-cache search festvox
# British English male speaker for festival, 16khz sample rate [voice_rab_diphone]
sudo apt-get install festvox-rablpc16k
# American English male speaker for festival, 16khz sample rate [voice_kal_diphone]
sudo apt-get install festvox-kallpc16k
# Castilian Spanish male speaker for Festival [voice_el_diphone]
sudo apt-get install festvox-ellpc11k

echo "------------------------------------------------------"
echo "Installing xfce4-terminal"
echo "------------------------------------------------------"
sudo apt-get install xfce4-terminal -y
echo "------------------------------------------------------"
echo "Installing Ueyecamera drivers"
echo "------------------------------------------------------"
sudo ${AEROSTACK_STACK}/installation/drivers/ueyesdk-setup-4.80-usb-amd64.gz.run

echo "------------------------------------------------------"
echo "Installing All ROS dependencies"
echo "------------------------------------------------------"
rosdep update
rosdep install -r --from-paths ${AEROSTACK_WORKSPACE} --ignore-src --rosdistro=$ROSDISTRO
