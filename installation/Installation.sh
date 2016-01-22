echo "-----------------------"
echo "Installing ncurses"
echo "-----------------------"
sudo apt-get install libncurses5
sudo apt-get install ncurses-bin
sudo apt-get install ncurses-dev
sudo apt-get install libboost1.54-dev
echo "-----------------------"
echo "Installing expect"
echo "-----------------------"
sudo apt-get install expect
echo "---------------------------"
echo "Installing ARdrone Autonomy dependencies"
echo "---------------------------"
sudo apt-get install libsdl1.2-dev
sudo apt-get install libudev-dev
sudo apt-get install libiw-dev
echo "---------------------------"
echo "Installing Bebop Autonomy dependencies"
echo "---------------------------"
echo sudo apt-get install build-essential python-rosdep python-catkin-tools
echo "---------------------------"
echo "Installing Sound Play"
echo "---------------------------"
sudo apt-get install ros-$ROS_DISTRO-audio-common
sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev 
echo "---------------------------"
echo "Installing Voices"
echo "---------------------------"
sudo apt-get install festlex-cmu
sudo apt-cache search festvox
sudo apt-get install festvox-rablpc16k
echo "---------------------------"
echo "Installing Lemar Library"
echo "---------------------------"
sudo apt-get install liblapack3 liblapack-dev
sudo apt-get install libblas3 libblas-dev
sudo apt-get install libf2c2 libf2c2-dev
echo "----------------------------"
echo "Installing Mavros dependencies"
echo "----------------------------"
sudo apt-get install ros-$ROS_DISTRO-control-toolbox
cd /tmp
wget http://packages.ros.org/ros-shadow-fixed/ubuntu/pool/main/r/ros-jade-mavlink/ros-jade-mavlink_2016.1.8-0trusty-20160108-0507-+0000_amd64.deb
sudo dpkg -i *mavlink*deb
echo "------------------------------------------------------"
echo "Installing Ueyecamera drivers"
echo "------------------------------------------------------"
cd ~/workspace/ros/quadrotor_stack_catkin/src/quadrotor_stack/installation
sudo ./ueyesdk-setup-4.60-usb-amd64.gz.run 
echo "------------------------------------------------------"
echo "Removing previous installs of Aerostack (If Installed)"
echo "------------------------------------------------------"
sed -i '/DRONE_WORKSPACE/d' ~/.bashrc
sed -i '/DRONE_STACK/d' ~/.bashrc
source ~/.bashrc
echo "------------------------------------------------------"
echo "Creating Workspace for Downloading the Aerostack"
echo "------------------------------------------------------"
cd ~/workspace/ros/quadrotor_stack_catkin
source /opt/ros/$ROS_DISTRO/setup.bash
cd src
catkin_init_workspace
cd ..
catkin_make
echo "-------------------------------------------------------"
echo "Sourcing the Aerostack"
echo "-------------------------------------------------------"
source devel/setup.bash
echo "--------------------------------------------------------------------"
echo "Installing the environment Variables DRONE_WORKSPACE and DRONE_STACK"
echo "--------------------------------------------------------------------"
./src/quadrotor_stack/installation/installers/installWS.sh
cd src/quadrotor_stack
./installation/installers/installStack.sh
source ~/.bashrc
echo "-------------------------------------------------------"
echo "Fetching the required git submodule"
echo "-------------------------------------------------------"
cd ~/workspace/ros/quadrotor_stack_catkin/src/quadrotor_stack
./installation/gitSubmoduleUpdateInit.sh installation/configSubmodules.cfg
echo "-------------------------------------------------------"
echo "Compiling the Aerostack"
echo "-------------------------------------------------------"
cd ~/workspace/ros/quadrotor_stack_catkin/src/quadrotor_stack
source setup.sh
cd ~/workspace/ros/quadrotor_stack_catkin
catkin_make
