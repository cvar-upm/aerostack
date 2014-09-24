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
		MODULE_PATH=stack/droneStackBasics/droneMsgsROS
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi



#okto_driver
if [[ ${okto_driver}  && $okto_driver = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverMikrokopterOkto/okto_driver
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#driver_camera_ueye
if [[ ${driver_camera_ueye}  && $driver_camera_ueye = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#driver_camera_ueye_ROSModule
if [[ ${driver_camera_ueye_ROSModule}  && $driver_camera_ueye_ROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye_ROSModule
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"

fi

#px-ros-pkg
if [[ ${px_ros_kg}  && $px_ros_pkg = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_px4flow/px-ros-pkg
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driver_px4flow_interface_ROSModule
if [[ ${driver_camera_ueye}  && $driver_camera_ueye = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_px4flow/driver_px4flow_interface_ROSModule
		git submodule init $MODULE_PATH > /dev/null
		./expectScript.sh $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

