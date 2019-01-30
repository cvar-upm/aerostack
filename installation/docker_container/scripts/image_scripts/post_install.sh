#!/bin/zsh

if [[ $# -lt 1 ]]; then
	echo "Usage $0 <git_url>"
	exit 1
fi

url=$1; shift;

. /ros_entrypoint.sh
. /root/.bashrc

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
touch $AEROSTACK_WORKSPACE/src/aerostack_stack/stack_devel/droneDrivers/driversPlatforms/parrot_arsdk/CATKIN_IGNORE
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
