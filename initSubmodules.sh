#!/bin/bash
echo "Configuring stack submodules .."


droneMsgs=true




if $droneMsgs
	then
		git submodule init stack/droneStackBasis/droneMsgsROS/
fi
