Adding a new physical platform basically means adding a new autopilot system which is not supported by the Aerostack. Sometimes the autopilot comes with a fixed platform like the Ardrone or sometimes it is only the autopilot and the user has to build the platform for the autopilot like Pixhawk. The following example demonstrates how the Pixhawk autopilot was added to the Aerostack. 

## 1. Basic Steps for Setting up Communication Between Aerostack and Pixhawk

When adding a new physical platform the most important thing to have a ROS package of the autopilot being added to the Aerostack. This ROS Package is used for communication between the  Autopilot with the Aerostack. As mentioned before the Aerostack is modular and hence in order to communicate with the Aerostack the Autopilot ROS package needs an Interface in order to convert the data coming from the Autopilot in units required by the Aerostack and also to convert the commands sent by the Aerostack in units required by the Autopilot. If the user is successful in making an interface for the Autopilot, the rest of the code for the controllers remains the same, and then its just a matter of tuning the controllers to fly the Autopilot with the Aerostack. 

In case of Pixhawk, the ROS package used for communication is the Mavros which is a MAVLink extendable communication node for ROS. An Interface called the driverPixhawkROSModule is then made for the Mavros in order for it to communicate with the Aerostack. 

The basic things that the Aerostack requires from any autopilot are the IMU data (rotation angles) and the battery voltage data and for sending commands from the Aerostack, the autopilot should accept roll, pitch, dyaw (change in yaw) and throttle commands.

## 2. Getting the Rotation Angles from the Pixhawk Using Mavros

The Aerostack accepts rotation angles in NED (North, East and Down). It requires the rotations in euler angles and the angles should be in degrees and not in radians. 

Mavros on the other hand uses ENU (East, North and Up) frame of reference. Please refer to the following wiki article for more information https://en.wikipedia.org/wiki/Axes_conventions. Also mavros publishes rotations in quaternion. 

Hence the driverPixhawkROSModule converts the rotations published by mavros into suitable units required by the Aerostack. Below is a piece of code on how it is done

```cpp
	//deg,  mavwork reference frame
	geometry_msgs::Vector3Stamped RotationAnglesMsgs;

	tf::Quaternion q(msg.orientation.x, msg.orientation.y,       
                        msg.orientation.z, msg.orientation.w);
	
       //make a matrix m of quaternion q 
       tf::Matrix3x3 m(q);

	
       //convert quaternion to euler angels
	m.getEulerYPR(yaw, pitch, roll);

	RotationAnglesMsgs.vector.x = (double)(+1)*(roll)*180/M_PI;
	RotationAnglesMsgs.vector.y = (double)(-1)*(pitch)*180/M_PI;
	RotationAnglesMsgs.vector.z = (double)(-1)*(yaw)*180/M_PI;

	//converting the yaw which is in the range from -phi to +phi to 0 to 360 
       degrees
	if( RotationAnglesMsgs.vector.z < 0 )
  	RotationAnglesMsgs.vector.z += 360.0;

	publishRotationAnglesValue(RotationAnglesMsgs);
```

The above code takes the rotations given by mavros in quaternion converts them into roll, pitch and yaw angles. These angles are then converted from ENU frame of reference to NED frame of reference and also converted from radians to degrees. The yaw angle which is in the range of -180 to +180 degrees is then converted in the range of 0 to 360 degrees. These angles are then finally published to the Aerostack. 

## 3. Getting the Battery Voltage from the Pixhawk Using Mavros

Mavros provides the current battery voltage using which the current battery percentage can be calculated. This percentage is then displayed on the user interface used for flying, which can be very important during a mission or normal flight to determine if the mission or flight can be carried out with a given percentage of battery. The code below determines how to convert the battery voltage to the percentage required by the Aerostack.

```cpp
	droneMsgsROS::battery BatteryMsgs;

	// Read Battery from navdata
	BatteryMsgs.header   = msg.header;
	// minimum voltage per cell used by the "digital battery checker" is
       3.55 V
	// msg.voltage is in V
	float battery_voltage = (msg.voltage);

       //Battery used in this case is 4 cell battery 
	BatteryMsgs.batteryPercent = ((battery_voltage - 14.8)/(16.8-14.8))*100;

	publishBatteryValue(BatteryMsgs);
```

The above code is used to convert the battery voltage to battery percentage for a 4 cell battery and hence the lower voltage limit is 14.8V and higher voltage limit is 16.8V. If using a 3 cell battery the lower voltage limit should be 11.0V and higher voltage limit should be 12.6V.

## 4. Sending Commands to the Pixhawk Using Mavros

There are several ways of sending commands to the pixhawk using mavros, by giving a certain position using position setpoints or directly setting the attitude and altitude using attitude setpoints.

This example uses roll, pitch, yaw and throttle commands from the Aerostack and sends to the pixhawk using mavros using setpoint_raw/attitude topic. 

The Aerostack produces commands for any autopilot in terms of roll, pitch, dyaw (change in yaw) and throttle and in NED frame of reference. 

The mavros on the other hand accepts commands in terms of roll, pitch, yaw and throttle but the roll, pitch and yaw have to be in quaternion and in ENU frame of reference. The throttle also has to be in the range from 0 to 1 counts. The driverPixhawkROSModule does all these conversions and finally sends the commands to the pixhawk using mavros. 

The code below shows how commands are sent using mavros to the pixhawk.

```cpp
       //message type for sending commands to mavros
	mavros_msgs::AttitudeTarget attitude_msg;

	//adding the current yaw angle to the dyaw command
	yaw_command = yaw_angle + msg.dyaw;

	//convert the values in radians and from NED frame(Aerostack) to ENU 
       frame (Mavros)
	roll_command  = (+1)*msg.roll*(M_PI/180.0);
	pitch_command = (-1)*msg.pitch*(M_PI/180.0);
	yaw_command   = (-1)*yaw_command*(M_PI/180.0);

	//convert euler angles to quaternion but in eigen form
	quaterniond =  mavros::UAS::quaternion_from_rpy(roll_command, 
                                         pitch_command, yaw_command);

	//convert quaternion in eigen form to geometry_msg form
	tf::quaternionEigenToMsg(quaterniond, orientation);

	attitude_msg.orientation = orientation;

	attitude_msg.thrust = msg.thrust * THRUST_SCALE;

	drone_CtrlInput_publisher.publish(attitude_msg);
```
 
In the above code the dyaw command is first converted into yaw by adding the current yaw angle to it because the mavros needs commands in yaw and not in dyaw. The code then converts rotation angles from degrees to radians and then the angles to quaternions. 

Then code then converts the throttle in the range defined in the Aerostack to the range of 0 to +1 required by the mavros by using the parameter THRUST_SCALE. The value of the THRUST_SCALE depends on the throttle range defined in midlevel controller in the Aerostack.

For example if the throttle is in the range of 0 to 32 Newtons in the Aerostack (midlevel controller), then the THRUST_SCALE has to be 1/32 in order to convert the throttle command in the range of 0 to +1 for mavros.