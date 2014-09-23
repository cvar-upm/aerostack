#!/bin/bash
echo "Configuring stack submodules .."


#Reading configuration of which submodules include
. configSubmodules.cfg



#Loop for git submodule init
if [[ ${droneMsgsROS}  && $droneMsgsROS = true ]]
	then
		
		git submodule init stack/droneStackBasis/droneMsgsROS/ > /dev/null
		echo " -stack/droneStackBasis/droneMsgsROS added" 
fi




if [[ ${okto_driver}  && $okto_driver = true ]]
	then
		git submodule init extStackCVG/okto_driver > /dev/null
		echo " -extStackCVG/okto_driver added"

fi




#git submodule update
git submodule update
