If your robotic system uses ArUco markers for self-localization, it is important to take into account the recommendations below when you build the real flight environment.

### Distance between markers

Consider carefully the correct distance between markers. For example, the range for which the ARDrone's camera can detect ArUco markers is about 3 meters, so poles and landmarks should be placed in a way that the drone always detects at least 1 ArUco marker and can correctly estimate its position.

NOTE: If you are experiencing problems with the drone's localization, consider increasing the density of Aruco visual markers.

### Avoid duplicate identifiers

It is important to check that identifiers for poles, walls or landmarks in the map are unique. If you use the same identifier for different objects in the map, the trajectory planner cannot work properly and could crash.

### Correct topics for Aruco-based localization

Be sure that you use the topics ArucoSlam_EstimatedPose and ArucoSlam_EstimatedSpeeds in your launcher, instead of EstimatedPose_droneGMR_wrt_GFF and EstimatedSpeed_droneGMR_wrt_GFF.


