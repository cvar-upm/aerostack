This section includes a set of practical tips to take into account in real flights.

### Multi-drone flight

In order to avoid drone collissions during the flight, you have to publish manually a message in the missionState topic after the complete initialization of Aerostack.
```bash
rostopic pub -1 /<DRONE_ID>/missionState std_msgs/Bool "data: true"
``` 
You must publish the previous message for each drone you are using. 

### Correct topics for Aruco-based localization

If the flight requires aruco-based positioning, be sure that you use the topics ```ArucoSlam_EstimatedPose``` and ```ArucoSlam_EstimatedSpeeds``` in your launcher, instead of ```EstimatedPose_droneGMR_wrt_GFF``` and ```EstimatedSpeed_droneGMR_wrt_GFF```.

**NOTE:** If you are experiencing problems with the drone's localization, consider increasing the density of Aruco visual markers. 

### Points for the Trajectory Planner

The trajectory planner uses a set of randomly generated points that can be modified in the file ```configFile.xml```. If you find that trajectory calculation is too slow you can try decreasing this value to reduce the calculation cost. However, keep in mind that decreasing it too much might cause the trajectory planner not to find trajectories in certain situations.

In the file _configFile.xml_ located in the _configs/droneN_ directory, you can specify the number of points used by the Trajectory Planner's algorithm to calculate trajectories. A high number will result in better trajectories, but will impact performance. To increase the probability of a good trajectory without too low performance, you can add a subzone with additional nodes for a difficult area. This can also work if you want to increase the probability of generating trajectories that pass through a certain area, since the Trajectory Planner favours trajectories with a higher number of nodes.
```xml
<config>
    <numNodes>3500</numNodes>
    <neigbourhood>5</neigbourhood>

    <subzone>
        <numNodes>500</numNodes>
        <initPoint>4.0 0.0</initPoint>
        <size>2.0 3.0</size>
    </subzone>
</config>
```
In this example, we add an extra 500 nodes to a 2m by 3m zone in (4, 0) where there is a narrow window that can make trajectory calculation more difficult.

### Collect data about flight

To record the data of the flight you just have to run the following script before starting the mission. 
```bash
#!/bin/bash

OUTFILE=$1
TOPICS="/public_event /rosout /rosout_agg /societyBroadcast /tf"

for i in $*; do
  if [[ "$i" != "$1" ]]; then
    DRONE_ID="drone$i"
    TOPICS="$TOPICS /$DRONE_ID/ArucoSlam_EstimatedPose   /$DRONE_ID/ArucoSlam_EstimatedPose_v2   /$DRONE_ID/ArucoSlam_EstimatedSpeeds   /$DRONE_ID/ArucoSlam_LandarmkList   /$DRONE_ID/EstimatedPose_droneGMR_wrt_GFF   /$DRONE_ID/EstimatedPose_iRobotGMR_wrt_droneGMR   /$DRONE_ID/EstimatedSpeed_droneGMR_wrt_GFF   /$DRONE_ID/SOEstimatedPose   /$DRONE_ID/SOEstimatedSpeeds   /$DRONE_ID/altitude   /$DRONE_ID/approved_action     /$DRONE_ID/ardrone/image_raw/compressed     /$DRONE_ID/ardrone/imu   /$DRONE_ID/ardrone/land   /$DRONE_ID/ardrone/mag   /$DRONE_ID/ardrone/navdata   /$DRONE_ID/ardrone/odometry   /$DRONE_ID/ardrone/reset   /$DRONE_ID/ardrone/takeoff   /$DRONE_ID/arucoObservation   /$DRONE_ID/aruco_eye/aruco_observation     /$DRONE_ID/aruco_eye/aruco_observation_image/image_raw/compressed     /$DRONE_ID/battery     /$DRONE_ID/camera/front/image_raw/compressed     /$DRONE_ID/cmd_vel   /$DRONE_ID/command/dAltitude   /$DRONE_ID/command/dYaw   /$DRONE_ID/command/high_level   /$DRONE_ID/command/pitch_roll   /$DRONE_ID/command_PBVS/Altitude   /$DRONE_ID/completed_action   /$DRONE_ID/completed_mission   /$DRONE_ID/controller_image_features   /$DRONE_ID/controller_image_features_feedback   /$DRONE_ID/current_task   /$DRONE_ID/distanceToObstacles   /$DRONE_ID/droneControllerYawRefCommand   /$DRONE_ID/droneManagerStateDoContinue   /$DRONE_ID/droneManagerStatus   /$DRONE_ID/droneMissionHLCommandAck   /$DRONE_ID/droneMissionPlannerCommand   /$DRONE_ID/droneMissionPoint   /$DRONE_ID/dronePointToLook   /$DRONE_ID/dronePositionRefs   /$DRONE_ID/droneSpeedsRefs   /$DRONE_ID/droneTrajectoryAbsRefCommand   /$DRONE_ID/droneTrajectoryController/controlMode   /$DRONE_ID/droneTrajectoryRefCommand   /$DRONE_ID/droneYawToLook   /$DRONE_ID/eventString   /$DRONE_ID/event   /$DRONE_ID/get_bounding_box   /$DRONE_ID/ground_speed   /$DRONE_ID/imu   /$DRONE_ID/initiated_action   /$DRONE_ID/isInTheSystem   /$DRONE_ID/is_object_on_frame   /$DRONE_ID/magnetometer   /$DRONE_ID/missionState   /$DRONE_ID/obstacles   /$DRONE_ID/pointToLook   /$DRONE_ID/pressure   /$DRONE_ID/process_alive_signal   /$DRONE_ID/process_error   /$DRONE_ID/process_error_unified_notification   /$DRONE_ID/processes_performance   /$DRONE_ID/requested_action   /$DRONE_ID/rotation_angles   /$DRONE_ID/self_detected_process_error   /$DRONE_ID/skills_list   /$DRONE_ID/societyPose   /$DRONE_ID/status   /$DRONE_ID/temperature   /$DRONE_ID/tracking_object   /$DRONE_ID/trajectoryControllerPositionReferencesRebroadcast   /$DRONE_ID/trajectoryControllerSpeedReferencesRebroadcast   /$DRONE_ID/trajectoryControllerTrajectoryReferencesRebroadcast   /$DRONE_ID/wifiIsOk"
  fi
done

rosbag record -O $OUTFILE $TOPICS
```
Run the script like this:
```bash
./rosbag-multidrone.sh outfile.bag <DRONE_ID_1> <DRONE_ID_2> ... <DRONE_ID_N>
```
Where DRONE_ID is the number id of the drone.

### Battery levels
Keep in mind that the lower the battery level is, the lower the power the drones' rotor will generate. In order to avoid that kind of problem, it is very recommended to change the battery when it has 30 percent or less.

### Aerostack reboot
Whenever the drone is disconnected (because of a battery change or a similar reason), it is highly reccommended to restart Aerostack and roscore to prevent unexpected behaviour.

If any of the processes crash, it is necessary to restart Aerostack to ensure everything is loaded correctly.

### OpenTLD GUI for Visual Servoing
When you are using the OpenTLD GUI you have to press the F5 button to refresh the image o the screen, select the area you want the drone to follow and then press and hold (just for few seconds) the ENTER key. Then the drone will start following the selected area. 

### Emergency mode
This state is used by the AR Drone to stop each of the rotors. This can be useful if the drone stops responding or it runs into an obstacle. To enter emergency mode you have two ways:

- Grab the drone with your hands and flip it so it faces downwards. Useful when the drone stops responding and you have no other way to land.

- Use the Command Line Interface and press the SPACE key.

To exit Emergency mode, you can press the SPACE key again. You will not be able to start a mission until you exit Emergency mode.

### Avoid duplicate identifiers
It is important to check that identifiers for poles, walls or landmarks in the map are unique. If you use the same identifier for different objects in the map, the trajectory planner cannot work properly and could crash.

### Efficient communication
To check if the connection to the drone is stable and fast enough, you can run the command ``` rostopic hz /drone0/camera/front/image_raw ```. It should display frequencies of around 30Hz. If this is not the case, you should consider changing the drone's channel to a less occupied one (this can be done with a parameter in the launcher).

### Visual servoing processes
If visual servoing produces unxpected behaviour, double check that the following processes have been started (with ``` rosnode list ```):
* /droneN/droneIBVSController
* /droneN/open\_tld\_translator
* /droneN/ros\_tld\_tracker\_node
* /droneN/ros\_tld\_gui\_node
* /droneN/trackerEye

### Distance between markers
The range for which the ARDrone's camera can detect Aruco markers is about 3 meters, so poles and landmarks should be placed in a way that the drone always detects at least 1 Aruco marker and can correctly estimate its position.