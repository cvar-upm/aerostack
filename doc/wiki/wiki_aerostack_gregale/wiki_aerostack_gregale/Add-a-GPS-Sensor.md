This section describes with an example how to add a new sensor to a UAV platform using the Aerostack. There might be several sensors that can be added to the Aerostack according to its usage, the important thing to keep in mind is that when adding a new sensor to the stack the sensor should publish its data in ROS and there should be an appropriate translator/interface that receives this sensor data. This translator or interface then converts the data in the units and conventions required by the stack and then publishes it to the appropriate module of the stack. In the following sections an example of adding a GPS sensor to the Aerostack is presented. 

This example illustrates adding a particular type of GPS sensor shown in the figure below. GPS is the most commonly used sensor with UAV’s, since it can give a  good position estimation of the UAV with reference to a global frame of reference, the only drawback of GPS is that is cannot be used indoors or in cluttered environments for example in places with a lot of trees or buildings. 

The position estimated by the GPS always has a drift, hence GPS data has to be given to the extended kalman filter in the Aerostack in order to obtain a better pose estimation of the UAV with respect to a given frame of reference. 

The following steps have to performed in order to add a GPS sensor in the Aerostack 

1. A GPS sensor with USB connection sending NMEA sentences (shown in figure below). 

1. A ROS package that listens to this NMEA sentences and then converts them to latitude and longitude values.

1. A ROS package which converts this latitude and longitude values into proper x, y and z coordinates in Universal Transverse Mercator coordinate system (UTM coordinate system).

1. A ROS package to convert these x, y and z values in UTM coordinate system to appropriate coordinate system required by the Aerostack. This package is called the translator or the interface for the GPS sensor.

1. Adding few changes in the extended kalman filter package to subscribe to the x, y, z values published by the GPS interface package. 

A detailed explanation of all this steps is given below step by step. 

## 1. Choosing a GPS Sensor
 
The first and the most important part in choosing a GPS is that it should publish NMEA sentences, because all the packages developed in ROS for GPS modules assume that the GPS module sends NMEA sentences. 

One can also use the GPS data given by a GPS which is attached to the autopilot of UAV. In this case, the user has to hack the autopilot to publish the appropriate GPS data for the following package which will be subscribing to this data. The figure below shows the USB GPS being used in this example which can be bought from a local electronics store at a low cost.

[[images/SensorGPS.png]]

## 2. ROS Module to Get the Data from the GPS Sensor   

There is already a package available in ROS which listens to the NMEA sentences given by the GPS sensor and converts them into appropriate latitude and longitude values. The ROS package can be found under this link:

https://github.com/ros-drivers/nmea_navsat_driver  

A launch file can be made to launch the node of this package which is as follows:

```xml
<!-- Launches: nmea_navsat_driver_node -->
<launch>

  <arg name="drone_id_namespace"  default="drone0" />
  <arg name="drone_id_int"                default="0" />
  <arg name="my_stack_directory"     default="$(env DRONE_STACK)" />
  
  <group ns="$(arg drone_id_namespace)">

        <node name="nmea_navsat_driver_node" pkg="nmea_navsat_driver" type="nmea_serial_driver" output="screen" respawn="true" clear_params="true">

	<param name="port"    value="/dev/ttyUSB0"  type="string" />
	<param name="baud"   value="4800"     	        type="int"   />   
        </node>
 </group>
</launch>
```

This file launches the ‘nmea_serial_driver’ node with the name ‘nmea_navsat_driver_node’ from the package ‘nmea_navsat_driver’. The param port defines the port at which the GPS is connected and the baud which should always be kept at 4800 in case of this GPS.

## 3. ROS Module Which Provides Position in UTM Coordinates

This is also a standard ros package which can be downloaded from github:

https://github.com/ktossell/gps_umd/tree/master/gps_common 

This package converts the latitude and longitude values provided by the ROS Module in the previous section into x, y and z position in UTM coordinates. 

A launch file can be made to launch the node of this package which is as follows:

```xml
<!-- Launches: gps_umd_node -->
<launch>

  <arg name="drone_id_namespace"  default="drone0" />
  <arg name="drone_id_int"                default="0" />
  <arg name="my_stack_directory"     default="$(env DRONE_STACK)" />
  
   <group ns="$(arg drone_id_namespace)">

       <node name="gps_umd" pkg="gps_common" type="utm_odometry_node" output="screen" respawn="true" clear_params="true">
  	
       </node>
  </group>
</launch>
```

This file launches the ‘utm_odometry_node’ with a name ‘gps_umd’ from the package ‘gps_common’. 

## 4. ROS Interface/Translator for the Received GPS Data

This package converts the position data given by the utm_odometry_node into data which is required by the Aerostack. At first, for the Aerostack the X axis should always be pointing towards the north and the Y axis towards the east but in case of utm_odometry_node the X axis points towards the east and Y axis points towards the north. Hence when this package receives data from the utm_odometry_node it first changes the axis as shown in the following code below. This piece of code is a callback function in this package which is called when this package receives the data from the utm_odometry_node.  

```cpp
void GPSOdomROSModule::GPSOdomCallback(const nav_msgs::Odometry &msg)
{
	//Asynchronous module with only one callback!
	if(!run())
    	return;

	GPS_pose.x = msg.pose.pose.position.y;
	GPS_pose.y = msg.pose.pose.position.x;
	GPS_pose.z = msg.pose.pose.position.z;

	ConvertToLocal(&GPS_pose);

	publishGPSValue();
	return;
}
```

Where:

- GPS_pose.x is Pose in x axis which will be published to the Aerostack,
 
- msg.pose.pose.position.y is Pose in y axis which was published by the utm_odometry_node,

- The convention goes similar for other axis. 

The function ConvertToLocal(&GPS_pose) takes the current pose given utm_odometry_node and substracts it from the pose at the initial point (Initial pose is the posewhich was sent by the GPS was got connected).  For example, if the GPS is connected at a particular point the utm_ododmetry_node publishes data in x = 44545 y = 4482, z = 650, but since this being the initial point the data should always be x = 0, y = 0 and z = 0, and hence the function ConvertToLocal(&GPS_pose) converts all the start point data to zero. 

```cpp
bool GPSOdomROSModule::GlobalToLocal(droneMsgsROS::dronePose *current)
{
	static droneMsgsROS::dronePose map_origin;
	static bool first_pose_received = false;

	bool initial_pose = !first_pose_received;

	if(initial_pose)
	{
  	map_origin   = *current;
  	map_origin.x = map_origin.x;          	
  	map_origin.y = map_origin.y;         	
  	map_origin.z = map_origin.z;

  	first_pose_received = true;

  	ROS_INFO("INITIAL data (%.3f, %.3f, %.3f), map origin (%.3f, %.3f, %.3f)",
  	current->x, current->y, current->z,
  	map_origin.x, map_origin.y, map_origin.z);
	}

	current->x -= map_origin.x;
	current->y -= map_origin.y;
	current->z -= map_origin.z;
	
	return initial_pose;
}
```
 
The variable map_origin has the data when the GPS started sending data. The current data is then subtracted from the map_origin data to get distances with respect to the start point. 

## 5. Publishing the GPS Data to Aerostack

The translated data given by a sensor now has to be processed by a suitable module in the Aerostack. In case of the GPS data the x, y and z positions need to be given to  EKF_Module to get a better pose estimate from it. 

But before giving the gps data to the EKF it first needs to be converted to the frame of reference used by the EKF. The frame of reference used by the EKF can be seen inside documention/Coordinate_frames/General_Frames_Field.svg. As can be seen from the figure the EKF takes measurements in Fdrone__Lmrt wrt to FEKF Frame. This fixed EKF frame always aligns itself to the heading of the UAV when the EKF is started and then the heading of the fixed EKF frame remains constant. 

The GPS Frame of reference is always fixed with x pointing towards the north and y pointing towards the east, and hence by using the yaw_degree given by the magnetometer the GPS fixed frame can be aligned to the EKF fixed frame as soon as the EKF is started. Below is a code showing how this reference frame conversion is being done.

```cpp
 	float x_drone,y_drone;

 	GlobalFrame(0,0) = x_gps;
 	GlobalFrame(1,0) = y_gps;
 	GlobalFrame(2,0) = z_gps;

 	RotationMat(0,0) = cos(yaw_drone);
 	RotationMat(1,0) = -sin(yaw_drone);
 	RotationMat(2,0) = 0;

 	RotationMat(0,1) = sin(yaw_drone);
 	RotationMat(1,1) = cos(yaw_drone);
 	RotationMat(2,1) = 0;

 	RotationMat(0,2) = 0;
 	RotationMat(1,2) = 0;
 	RotationMat(2,2) = 1;

 	BodyFrame = RotationMat*GlobalFrame;

 	x_drone = BodyFrame(0,0);
 	y_drone = BodyFrame(1,0);
```

The yaw_drone parameter is taken only once when the EKF is started or it is reset, and during rest of time it remains constant with the first value when EKF was started. The x_drone and y_drone are positions converted with respect to EKF frame of reference and are then provided to the EKF and if everything else is correct the user should obtain a pose from the EKF which is fused with the GPS data. Note that in the example above only x and y data from the GPS are given to the EKF the z data is not used as it has a lot of noise. 