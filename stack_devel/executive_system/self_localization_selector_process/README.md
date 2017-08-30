# Brief
This process publishes the pose and the speed of the drone depending on the mode selected.
The are two different modes, the odometry mode and the aruco slam mode.

# Services
- **change_self_localization_mode_to_odometry** ([std_srvs/Empty](http://docs.ros.org/kinetic/api/std_srvs/html/srv/Empty.html))  
Changes the mode of the selector to odometry.

- **change_self_localization_mode_to_visual_markers** ([std_srvs/Empty](http://docs.ros.org/kinetic/api/std_srvs/html/srv/Empty.html))  
Changes the mode of the selector to visual markers.


# Published topics
- **estimated_pose** ([droneMsgsROS/dronePose](https://bitbucket.org/joselusl/dronemsgsros/src/a6a289b1101d8a2de9799afe9c96cb540f524112/msg/dronePose.msg))  
Publishes the pose of the drone based on the mode of the selector.

- **estimated_speed** ([droneMsgsROS/droneSpeeds](https://bitbucket.org/joselusl/dronemsgsros/src/a6a289b1101d8a2de9799afe9c96cb540f524112/msg/droneSpeeds.msg))  
Publishes the speed of the drone based on the mode of the selector.


# Subscribed topics
- **ArucoSlam_EstimatedPose** ([droneMsgsROS/dronePose](https://bitbucket.org/joselusl/dronemsgsros/src/a6a289b1101d8a2de9799afe9c96cb540f524112/msg/dronePose.msg))  
Contains the estimated pose of the drone based on visual markers

- **ArucoSlam_EstimatedSpeed** ([droneMsgsROS/droneSpeeds](https://bitbucket.org/joselusl/dronemsgsros/src/a6a289b1101d8a2de9799afe9c96cb540f524112/msg/droneSpeeds.msg))
Contains the estimated speed of the drone based on visual markers

- **EstimatedPose_droneGMR_wrt_GFF** ([droneMsgsROS/dronePose](https://bitbucket.org/joselusl/dronemsgsros/src/a6a289b1101d8a2de9799afe9c96cb540f524112/msg/dronePose.msg))
Contains the estimated pose of the drone based on odometry.

- **EstimatedSpeed_droneGMR_wrt_GFF** ([droneMsgsROS/droneSpeeds](https://bitbucket.org/joselusl/dronemsgsros/src/a6a289b1101d8a2de9799afe9c96cb540f524112/msg/droneSpeeds.msg))
Contains the estimated speed of the drone based on odometry.

---
# Contributors
**Maintainer:** Alberto Camporredondo (alberto.camporredondo@gmail.com)  
**Author:** Alberto Camporredondo
