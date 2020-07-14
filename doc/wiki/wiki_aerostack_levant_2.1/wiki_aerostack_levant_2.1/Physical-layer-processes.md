| Process |  System | Launcher  | Comments |
| :-------| :------- | :------- |:------- |
| Drivers AR Drone | Hardware interface | driverParrotARDroneROSModule.launch | Operation with AR Drone 2.0. NOTE (1) |
| Drone Simulator | Simulation system	| droneSimulatorROSModule.launch | Operation with "Drone Simulator" |

NOTE (1) This option also requires the launcher related to "ARDrone Autonomy": `${AEROSTACK_STACK}/launchers/ardrone_launch/ardrone_indoors.launch`

NOTE (2): Other aerial platforms not described here can also be used with Aerostack (e.g., Asctec Pelican, Bebop, etc.).