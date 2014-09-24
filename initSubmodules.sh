#!/bin/bash
echo "Configuring stack submodules .."


#Reading configuration of which submodules include
. configSubmodules.cfg



#Adquire bitbucket info
echo "Acquiring bitbucket user info"
echo -n " -Bitbucket username: "
read bitbucketUsername

echo -n " -Bitbucket password: "
read -s bitbucketPassword
echo ""



#Loop for git submodule init
echo "Adding submodules"

#droneMsgsROS
if [[ ${droneMsgsROS}  && $droneMsgsROS = true ]]
	then
		
		git submodule init stack/droneStackBasis/droneMsgsROS > /dev/null
		./expectScript.sh "stack/droneStackBasis/droneMsgsROS" $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: stack/droneStackBasis/droneMsgsROS" 
fi



#okto_driver
if [[ ${okto_driver}  && $okto_driver = true ]]
	then
		git submodule init extStackCVG/okto_driver > /dev/null
		./expectScript.sh "extStackCVG/okto_driver" $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: extStackCVG/okto_driver"

fi


#driver_camera_ueye
if [[ ${driver_camera_ueye}  && $driver_camera_ueye = true ]]
	then
		git submodule init stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye > /dev/null
		./expectScript.sh "stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye" $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye"

fi


#driver_camera_ueye_ROSModule
if [[ ${driver_camera_ueye_ROSModule}  && $driver_camera_ueye_ROSModule = true ]]
	then
		git submodule init stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye_ROSModule > /dev/null
		./expectScript.sh "stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye_ROSModule" $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye_ROSModule"

fi

#px-ros-pkg
if [[ ${px_ros_kg}  && $px_ros_pkg = true ]]
	then
		git submodule init stack/droneDrivers/driversSensors/driver_px4flow/px-ros-pkg > /dev/null
		git submodule update stack/droneDrivers/driversSensors/driver_px4flow/px-ros-pkg > /dev/null
		echo " -Added package in: stack/droneDrivers/driversSensors/driver_px4flow/px-ros-pkg"

fi

#driver_camera_ueye
if [[ ${driver_camera_ueye}  && $driver_camera_ueye = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_px4flow/driver_px4flow_interface_ROSModule
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"

fi

