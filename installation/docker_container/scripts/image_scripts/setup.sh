#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo "Usage $0 <git_url>"
	exit 1
fi

url=$1; shift;

if [[ "$url" == "" ]]; then
	echo "Git url must not be empty"
	exit 1
fi

source /ros_entrypoint.sh
source /root/.bashrc

export TERM=xterm

echo "----------------------------"
echo "Install driver common required in kinectic"
echo "----------------------------"
mkdir -p /tmp/driver_common/src
cd /tmp/driver_common/src
git clone https://github.com/ros-drivers/driver_common
cd ..
catkin_make install -DCMAKE_INSTALL_PREFIX=/tmp/ros/kinetic
sudo cp -R /tmp/ros/kinetic /opt/ros/
rm -rf /tmp/ros
rm -rf /tmp/driver_common

echo "----------------------------"
echo "Install keyboard required in kinectic"
echo "----------------------------"
mkdir -p /tmp/keyboard/src
cd /tmp/keyboard/src
git clone https://github.com/lrse/ros-keyboard.git
cd ..
catkin_make install -DCMAKE_INSTALL_PREFIX=/tmp/ros/kinetic
sudo cp -R /tmp/ros/kinetic /opt/ros/
rm -rf /tmp/ros
rm -rf /tmp/keyboard

#######################
# The user should fill this variables

# Absolute path of the aerostack workspace
AEROSTACK_WS_PATH="$HOME/workspace/ros/aerostack_catkin_ws"

# Relative path of the aerostack. The parent path is ${AEROSTACK_WS_PATH}/src
AEROSTACK_STACK_SUBPATH="aerostack_stack"

# ROS DISTRO
ROS_DISTRO="kinetic"


#
# End of user configuration
##################################

clear

echo "------------------------------------------------------"
echo "Setting Aerostack Paths"
echo "------------------------------------------------------"
AEROSTACK_WORKSPACE=$AEROSTACK_WS_PATH
AEROSTACK_STACK="$AEROSTACK_WS_PATH/src/$AEROSTACK_STACK_SUBPATH"
echo "-The Aerostack WS path is: $AEROSTACK_WORKSPACE"
echo "-The Aerostack stack path is: $AEROSTACK_STACK"





echo "------------------------------------------------------"
echo "Removing previous installs of Aerostack (If Installed)"
echo "------------------------------------------------------"
rm -rf $AEROSTACK_STACK
rm -rf $AEROSTACK_WORKSPACE
sed -i '/AEROSTACK_WORKSPACE/d' $HOME/.bashrc
sed -i '/AEROSTACK_STACK/d' $HOME/.bashrc


echo "------------------------------------------------------"
echo "Creating the ROS Workspace for Downloading the Aerostack and the Aerostack path"
echo "------------------------------------------------------"
mkdir -p $AEROSTACK_WORKSPACE/src
mkdir -p $AEROSTACK_STACK


echo "-------------------------------------------------------"
echo "Downloading the Aerostack"
echo "-------------------------------------------------------"
cd $AEROSTACK_STACK
git clone -b master $url ./

echo "--------------------------------------------------------------------"
echo "Installing the environment Variables AEROSTACK_WORKSPACE and AEROSTACK_STACK"
echo "--------------------------------------------------------------------"
cd $AEROSTACK_WORKSPACE
$AEROSTACK_STACK/installation/installers/installWS.sh

cd $AEROSTACK_STACK
./installation/installers/installStack.sh

export AEROSTACK_WORKSPACE
export AEROSTACK_STACK

echo "------------------------------------------------------"
echo "Creating the ROS Workspace"
echo "------------------------------------------------------"
source /opt/ros/$ROS_DISTRO/setup.bash
cd $AEROSTACK_WORKSPACE/src
catkin_init_workspace
cd $AEROSTACK_WORKSPACE
#touch $AEROSTACK_WORKSPACE/src/aerostack_stack/stack_devel/droneDrivers/driversPlatforms/parrot_arsdk/CATKIN_IGNORE
catkin_make


echo "-------------------------------------------------------"
echo "Sourcing the ROS Aerostack WS"
echo "-------------------------------------------------------"
. ${AEROSTACK_WORKSPACE}/devel/setup.bash

set +e

echo "-------------------------------------------------------"
echo "Fetching the required git submodule"
echo "-------------------------------------------------------"
cd ${AEROSTACK_STACK}
git submodule update --init --recursive configs
git submodule update --init --recursive documentation
git submodule update --init --recursive etc
git submodule update --init --recursive installation
git submodule update --init --recursive launchers
git submodule update --init --recursive logs

git submodule update --init --recursive stack
git submodule update --init --recursive stack_deprecated
#git submodule update --init --recursive stack_devel
#git submodule update --init --recursive stack_obsolete


echo "-------------------------------------------------------"
echo "Installing dependencies"
echo "-------------------------------------------------------"
cd ${AEROSTACK_STACK}
# ./installation/installation_dep_script.sh
	echo "------------------------------------------------------"
	echo "Installing Ueyecamera drivers"
	echo "------------------------------------------------------"
	${AEROSTACK_STACK}/installation/drivers/ueyesdk-setup-4.80-usb-amd64.gz.run

	echo "------------------------------------------------------"
	echo "Installing All ROS dependencies"
	echo "------------------------------------------------------"
	rosdep update
	rosdep install -r -y --from-paths ${AEROSTACK_WORKSPACE} --ignore-src --rosdistro=$ROSDISTRO


echo "-------------------------------------------------------"
echo "Fixing CMakeLists.txt to be able to open QTCreator"
echo "-------------------------------------------------------"
cd $AEROSTACK_WORKSPACE/src
rm CMakeLists.txt
cp /opt/ros/$ROS_DISTRO/share/catkin/cmake/toplevel.cmake CMakeLists.txt

echo "-------------------------------------------------------"
echo "Compiling the Aerostack"
echo "-------------------------------------------------------"
. ${AEROSTACK_STACK}/setup.sh
cd ${AEROSTACK_WORKSPACE}
# patch, deprecated driver in kinetic
touch src/aerostack_stack/stack/hardware_interface/drivers_sensors/driver_hokuyo/hokuyo_node/CATKIN_IGNORE
touch src/aerostack_stack/stack/hardware_interface/drivers_platforms/driver_bebop/bebop_autonomy/bebop_driver/CATKIN_IGNORE
# ToDo, catkin_make fails to setup gazebo_plugins for protobuf, patch the cmake file
# https://github.com/ethz-asl/rotors_simulator/issues/352
catkin_make
