
| Process | System |  Launcher  | Comments |
| :-------| :----- | :--------- |:-------- |
| Basic actions controller | Motor system | droneMidLevelAutopilotROSModule.launch | Take-off, land, hover|
| Trajectory controller	| Motor system | droneTrajectoryControllerROSModule.launch | Setpoint-based flight control|
| Tracker eye | Feature extraction | droneTrackerEyeROSModule.launch |Vision-based flight control. NOTE (1)|
| Visual servoing control | Motor system | DroneIBVSControllerROSModule.launch	|Vision-based flight control. |
| OpenTLD translator | Motor system  | droneOpenTLDTranslatorROSModule.launch	|Vision-based flight control. NOTE (2)|

NOTE(1): To activate this Feature for the AR Drone it is necessary to copy the files from the config folder: `ardrone_camera_bottom.yaml` and `ardrone_camera_front.yaml` to the folder in the home directory:`.ros/camera_info/` 

NOTE (2): Required launchers: 
  `${AEROSTACK_STACK}/launchers/ardrone_launch/launch_files/opentld_for_IBVSController.launch`
  `${AEROSTACK_STACK}/launchers/ardrone_launch/launch_files/opentld_gui_for_IBVSController.launch`