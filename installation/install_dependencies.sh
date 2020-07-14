#!/bin/bash

echo "-----------------------"
echo "Installing ncurses"
echo "-----------------------"
sudo apt-get -y install libncurses5
sudo apt-get -y install ncurses-bin
sudo apt-get -y install ncurses-dev
sudo apt-get -y install libncursesw5-dev

echo "-----------------------"
echo "Installing boost"
echo "-----------------------"
sudo apt-get -y install libboost1.54-dev

echo "-----------------------"
echo "Installing pyinotify"
echo "-----------------------"
sudo apt-get -y install python-pyinotify

echo "-----------------------"
echo "Installing expect"
echo "-----------------------"
sudo apt-get -y install expect

echo "---------------------------"
echo "Installing Lapack, Blas, protobuf and F2C Libraries"
echo "---------------------------"
sudo apt-get -y install liblapack3 liblapack-dev
sudo apt-get -y install libblas3 libblas-dev
sudo apt-get -y install libf2c2 libf2c2-dev
sudo apt-get -y install protobuf-compiler

echo "---------------------------"
echo "Installing ARdrone Autonomy dependencies"
echo "---------------------------"
sudo apt-get -y install libsdl1.2-dev
sudo apt-get -y install libsdl-image1.2-dev
sudo apt-get -y install libudev-dev
sudo apt-get -y install libiw-dev

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
	sudo apt-get -y install ros-$ROS_DISTRO-audio-common
	sudo apt-get -y install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev

	echo "------------------------------------------------------"
	echo "Installing qwt library"
	echo "------------------------------------------------------"
	sudo apt-get -y install libqwt-headers
	sudo apt-get -y install libqwt-qt5-dev
	sudo apt-get -y install libzbar-dev
		
	echo "---------------------------"
	echo "Installing libARCommands"
	echo "---------------------------"
	git clone https://github.com/Parrot-Developers/libARCommands $AEROSTACK_STACK/libraries/libARCommands

	echo "------------------------------------------------------"
	echo "Updating gazebo"
	echo "------------------------------------------------------"
	cd $AEROSTACK_STACK/stack/simulation_system/rotors_simulator
	git checkout -f  stable/kinetic 

	echo "------------------------------------------------------"
	echo "Exporting parrot_arsdk lib"
	echo "------------------------------------------------------"
	echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$AEROSTACK_WORKSPACE/devel/lib/parrot_arsdk" >> ~/.bashrc
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
	sudo apt-get -y install git build-essential cmake qt5-default qtscript5-dev libssl-dev qttools5-dev qttools5-dev-tools qtmultimedia5-dev libqt5svg5-dev libqt5webkit5-dev libsdl2-dev libasound2 libxmu-dev libxi-dev freeglut3-dev libasound2-dev libjack-jackd2-dev libxrandr-dev libqt5xmlpatterns5-dev libqt5xmlpatterns5

	echo "---------------------------"
	echo "Installing opencv_apps"
	echo "---------------------------"
	sudo apt-get -y install ros-opencv-apps

	echo "---------------------------"
	echo "Installing joystick_drivers"
	echo "---------------------------"
	sudo apt-get -y install ros-melodic-joystick-drivers

	echo "---------------------------"
	echo "Installing lib_usb"
	echo "---------------------------"
	sudo apt-get -y install libusb-dev

	echo "---------------------------"
	echo "Installing octomap"
	echo "---------------------------"
	sudo apt-get -y install ros-melodic-octomap 

	echo "---------------------------"
	echo "Installing spnav"
	echo "---------------------------"
	sudo apt-get -y install libspnav-dev 

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
	sudo apt-get -y install ros-$ROS_DISTRO-audio-common
	sudo apt-get -y install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
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
sudo apt-get -y install festlex-cmu
sudo apt-cache search festvox
# British English male speaker for festival, 16khz sample rate [voice_rab_diphone]
sudo apt-get -y install festvox-rablpc16k
# American English male speaker for festival, 16khz sample rate [voice_kal_diphone]
sudo apt-get -y install festvox-kallpc16k
# Castilian Spanish male speaker for Festival [voice_el_diphone]
sudo apt-get -y install festvox-ellpc11k

echo "------------------------------------------------------"
echo "Installing xfce4-terminal"
echo "------------------------------------------------------"
sudo apt-get -y install xfce4-terminal
echo "------------------------------------------------------"
echo "Installing Ueyecamera drivers"
echo "------------------------------------------------------"
sudo ${AEROSTACK_STACK}/installation/drivers/ueyesdk-setup-4.80-usb-amd64.gz.run

echo "------------------------------------------------------"
echo "Installing All ROS dependencies"
echo "------------------------------------------------------"
rosdep update
rosdep -y install -r --from-paths ${AEROSTACK_WORKSPACE} --ignore-src --rosdistro=$ROS_DISTRO

#########Install possible missing dependencies
DEPENDENCIES=""
apt-get update
rosdep update
TEMP=$(rospack list)
TEMP=$(grep -E "$AEROSTACK_WORKSPACE|UTR" <<< "$TEMP" | cut -d' ' -f1)
for p in $(echo $TEMP)
do
	echo "Calculating Dependencies for $p"
	TEMP2+=" $(echo -e $(rospack depends $p  2>/dev/null))"
done

TEMP=$(tr -s [:space:] \\n <<< $TEMP2 | sort | uniq)

TEMP=$(echo "$TEMP" | sed 's/_/-/g')
TEMP=$(echo "$TEMP" | sed 's/^/ /')
TEMP=$(echo "$TEMP" | sed "s/ / ros-$ROS_DISTRO-/g")
for p in $(echo $TEMP)
do
	echo "Checking whether $p is installed or not"
	apt-cache show $p > /dev/null 2>&1
	test $? -ne 0 || DEPENDENCIES="$DEPENDENCIES $p"
done
sudo apt-get install -y ros-$ROS_DISTRO-mavlink ros-$ROS_DISTRO-octomap-msgs ros-opencv-apps ros-$ROS_DISTRO-opencv-apps ros-$ROS_DISTRO-joystick-drivers ros-$ROS_DISTRO-nmea-msgs ros-$ROS_DISTRO-octomap-ros ros-$ROS_DISTRO-control-toolbox ros-$ROS_DISTRO-parrot-arsdk $DEPENDENCIES
#########
sudo apt-get remove -y ros-melodic-rotors-gazebo-plugins

echo "All dependencies installed succesfully"
