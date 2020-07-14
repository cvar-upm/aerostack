This catalog shows the available processes provided by Aerostack organized according to robot capabilities. The catalog also shows the launcher and the system corresponding to each process. In order to have a desired capability for a particular robot, the developer must select the launchers of processes described in this page.

### Capability: Operation with an aerial platform

**Option: Operation with Parrot AR Drone 2.0**

| Process |  System | Launcher  |
| :-------| :------- | :-------- |
| Drivers platform | Hardware interface | driverParrotARDroneROSModule.launch |

This option also requires the launcher: 

`${AEROSTACK_STACK}/launchers/ardrone_launch/ardrone_indoors.launch`

> NOTE: Other aerial platforms not described here can also be used with Aerostack (e.g., Asctec Pelican, Bebop, etc.).

**Option: Operation with a RViz-based simulator**

| Process |  System | Launcher  |
| :-------| :------- | :-------- |
| Simulator | Simulation system	| SimulatorRvizROSModule.launch	|


### Capability: Aruco visual markers recognition

| Process |  System | Launcher  |
| :-------| :------- | :-------- |
| Aruco eye | Feature extraction | droneArucoEyeROSModule.launch |

### Capability: Self-localization

**Option: Self-localization by Aruco visual markers**

Required capability: **Aruco visual markers recognition**

| Process | System | Launcher  |
| :-------| :------- | :-------- |
| Visual markers localizer | Situation awareness	|droneVisualMarkersLocalizerROSModule.launch	|
| Obstacle detector visual marks	|Situation awareness	|droneObstacleProcessor2dVisualMarksROSModule.launch	|
| Obstacle distance calculator | Situation awareness	|droneObstacleDistanceCalculationROSModule.launch	|
| Self localizer | Situation awareness	|droneEKFStateEstimatorROSModule.launch	|

### Capability: Setpoint-based flight control

Required capability: **Self-localization**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Basic actions controller |	Motor system	|	droneMidLevelAutopilotROSModule.launch	|
|	Trajectory controller	|	Motor system	|	droneTrajectoryControllerROSModule.launch	|

### Capability: Vision-based flight control

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
| Tracker eye | Feature extraction | droneTrackerEyeROSModule.launch	|
| Visual servoing control | Motor system | DroneIBVSControllerROSModule.launch	|
| OpenTLD translator | Motor system  | droneOpenTLDTranslatorROSModule.launch	|

Required launchers: 

`${AEROSTACK_STACK}/launchers/ardrone_launch/launch_files/opentld_for_IBVSController.launch`

`${AEROSTACK_STACK}/launchers/ardrone_launch/launch_files/opentld_gui_for_IBVSController.launch`

NOTE: To activate this Feature for the AR Drone it is necessary to copy the files from the config folder:

`ardrone_camera_bottom.yaml`

`ardrone_camera_front.yaml` 

to the folder in the home directory:

`.ros/camera_info/` 

### Capability: Path planning

Required capability: **Setpoint-based flight control**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Trajectory planner	|	Planning system	|	droneTrajectoryPlanner2dROSModule.launch	|
|	Yaw commander	|	Planning system	|	droneYawCommanderROSModule.launch	|

### Capability: Action execution

Required capabilities: **Path planning**, **Setpoint-based flight control**, **Vision-based flight control**

**Option: Execution of simple actions**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Manager of actions	|	Executive system	|	droneManagerOfActionsROSModule.launch	|

**Option: Execution of advanced actions**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Behavior manager	|	Executive system	|	behavior_manager_process.launch	|
|	Manager of actions	|	Executive system	|	droneManagerOfActionsROSModule.launch	|
|	Action monitor	|	Supervision system|	action_monitor_process.launch	|

### Capability: Mission plan interpretation

**Option: Mission schedule processor**

Required capability: **Action execution (Option: Execution of simple actions)**

| Process |System |   Launcher  |
| :-------| :------- | :-------- |
|	Mission planner	|	Planning system	|	droneMissionSheduleProcessorROSModule.launch	|

**Option: Task-based mission plan interpreter**

Required features: **Action execution (Option: Execution of advanced actions)**

|  Process | System | Launcher  |
| :-------| :------- | :-------- |
|	Mission planner	| Planning system	|	task_based_mission_planner_process.launch	|
|	Action specialist	|	Planning system	|	action_specialist_process.launch	|

### Capability: User interface of ground control station

**Option: Alphanumeric user interface**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Graphical User Interface	| Ground control system	|		droneInterface_jp_ROSModule.launch	|

**Option: Graphical User Interface**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Graphical User Interface	|Ground control system	|		human_machine_interface_process.launch	|

**Option: Speech-based communication**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|	Speech module	|Ground control station | 	droneSpeechROSModule.launch	|
|		Sound module	| Ground control station 	|	droneSoundROSModule.launch	|

Required launcher: 

`${AEROSTACK_STACK}/launchers/sound_play.launch`

**Option: Communication with leap motion**

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|		Leap motion	|Ground control station 	|	droneLeapMotionDroneControlUserInterfaceROSModule.launch	|

### Capability: Swarm Coordination

| Process | System |  Launcher  |
| :-------| :------- | :-------- |
|		Communication manager	| Communication system	|	droneCommunicationManagerROSModule.launch	|

### Capability: Process monitoring

This capability must be always active.

|  Process | System | Launcher  |
| :-------| :------- | :-------- |
|	Process monitor	|	Supervision system  |	process_monitor_process.launch	|