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


#okto_driver
if [[ ${driver_camera_ueye}  && $driver_camera_ueye = true ]]
	then
		git submodule init stack/droneSrivers/driversSensors/driver_camera_ueye > /dev/null
		./expectScript.sh "stack/droneSrivers/driversSensors/driver_camera_ueye" $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: stack/droneSrivers/driversSensors/driver_camera_ueye"

fi



