#!/bin/bash

rosservice call /drone5/droneRobotLocalizationROSModuleNode/start
rosservice call /drone5/mavros/set_mode "base_mode: 0
custom_mode: 'OFFBOARD'"
rosservice call /drone5/mavros/cmd/arming "value: true"
#rosservice call /drone5/droneSubMissionPlanner/start
