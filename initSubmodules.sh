#!/bin/bash
echo "Configuring stack submodules .."


#Reading configuration of which submodules include
. configSubmodules.cfg



#Loop for git submodule init
if [[ ${droneMsgsROS}  && $droneMsgsROS = true ]]
	then
		git submodule init stack/droneStackBasis/droneMsgsROS/
		echo " -stack/droneStackBasis/droneMsgsROS added"
fi




if [[ ${okto_driver}  && $okto_driver = true ]]
	then
		git submodule add -b catkin https://bitbucket.org/Vision4UAV/okto_driver.git ./extStackCVG/okto_driver
		echo " -extStackCVG/okto_driver added"

fi




#git submodule update
git submodule update
