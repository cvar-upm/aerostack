Calibrating controllers become very important step if user has added more payloads to the UAV or a UAV has been added which with the Aerostack was not used before. There are several controllers which are used the Aerostack and they are arranged in several layers. The first layer is the low level controller which is inside the autopilot of the UAV system. This low level controller can be tuned according to the instructions given by the people providing the autopilot system.

Above the low-level controller comes the mid-level controller which is present inside the Aerostack. This controller is used for take off, landing and hovering of the UAV. (Note: In case of the ARdrone, the mid-level controller provided by the ARdrone manufactures is being used and hence the mid-level controller provided by the Aerostack is not used). Above the mid-level controller is the high-level controller, using which the user can give speed commands, position commands as well as trajectories to the UAV. 

## Calibrating the Mid-Level Controller

As mentioned above the mid-level controller is used for take-off, landing and hovering of the UAV, and hence it is one of the critical controllers. If the mid-level controller is not tuned properly, there are high chances of the UAV crashing. Hence it is very important that is mid-level is tuned perfectly. 

The mid-level controller is a combination of three different controllers namely: 

- Altitude controller

- Hover controller 

- Yaw controller

As the names suggest, the altitude controller is the one which is used for controlling the altitude of the UAV. The hover controller takes in input as vertical speeds and is used for making the UAV hover at a particular position. The yaw controller controls the heading of the UAV maintaining the current heading of the UAV. 

The mid-level controller tuning parameters are stored inside $DRONE_STACK/configs/drone. The drone id (drone0, drone1, etc.) depends on the drone which the user is using. For example, the mid-level controller tuning file for Asctec Pelican UAV can be found inside $DRONE_STACK/configs/drone0, as drone0 is being used for Pelican. The name of the file which contains the tuning parameters is midlevel_autopilot.xml. Below is a step by step explanation of the midlevel_autopilot.xml.

```xml
<midlevel_autopilot>
  <ON_GROUND_ALTITUDE>  0.25  </ON_GROUND_ALTITUDE> <!-- m -->

  <TAKE_OFF>
    <TAKEOFF_SPEED>  0.6  </TAKEOFF_SPEED> <!-- m/s -->

    <TAKEOFF_FINAL_ALTITUDE> 1.1 </TAKEOFF_FINAL_ALTITUDE> <!-- m   -->

    <TAKINGOFF_ALT_SPEED_COS_GAMMA> 2.15 </TAKINGOFF_ALT_SPEED_COS_GAMMA>   

    <MAX_TAKINGOFF_TIME_S> 5.0 </MAX_TAKINGOFF_TIME_S> <!-- s   -->
  </TAKE_OFF>

  <LANDING>
    <LANDING_SPEED> 0.40 </LANDING_SPEED> <!-- m/s -->

    <ALTITUDE_FOR_LANDING_WITH_TIME> 0.40   </ALTITUDE_FOR_LANDING_WITH_TIME>  <!-- m   -->

    <LANDING_WITH_TIME_MAX_SECONDS> 	1.00 </LANDING_WITH_TIME_MAX_SECONDS>  <!-- s   -->
      
    <LANDING_WITH_TIME_FIXED_THRUST_KG> 0.32 </LANDING_WITH_TIME_FIXED_THRUST_KG>  <!-- kg  -->
  </LANDING>
```


- ON_GROUND_ALTITUDE is the on ground altitude measured by the distance sensor when the UAV is landed. 

The next parameters influence the take off of the UAV. 

- TAKEOFF_SPEED influences how fast the UAV will take off. Ranging from 0.1 to 1.0. It is generally advised to keep to the takeoff speed parameter to 0.6 for a good take off.
 
- TAKEOFF_FINAL_ALTITUDE influences the final altitude the UAV is maintain after it taking off. In case PX4flow sensor  is being used as the distance sensor the range is between 0.5 to 3.0.

- MAX_TAKINGOFF_TIME_S parameter defines the maximum time the midlevel controller will maintain its status at taking off after which it will change its status to hovering. In other words if the max taking off time is 5 secs, the maximum time the midlevel controller will allow the UAV to reach its final altitude is 5 secs after which the UAV will start hovering evern if it has not reached the final altitude. 

The next set of parameters are for landing 

- LANDING_SPEED parameter defines how fast the UAV will land. Advisable to keep it around 0.4 m/s.

- ALTITUDE_FOR_LANDING_WITH_TIME parameter defines the altitude at which the controller will give the final thrust for llanding the UAV. For example is the the parameter is 0.4 m the controller will give the final thrust after the UAV reaches 0.4 m.

- LANDING_WITH_TIME_MAX_SECONDS parmeter defines the time is seconds the controller will wait before give the final thrust.

- LANDING_WITH_TIME_FIXED_THRUST_KG parameter is the value of final thrust given in kgs for the UAV to touch the ground. It is influenced by the weight of the UAV, lighter UAV’s around 2 kgs can have a this parameter around 0.32kgs and for heavy UAV’s this parameter can be around 1.32 kgs. For more information on how to choose the landing thrust value user can refer to configs/drone0/midleve_autopilot.xml.

The next set of parameters are for setting the limits for the controller as can be seen in the table below

```xml
<MAX_ALTITUDE>      
  <MAX_ALTITUDE>   3.00 </MAX_ALTITUDE> <!-- m   -->

  <MAX_ALTITUDE_DESCENDING_SPEED> 0.20 </MAX_ALTITUDE_DESCENDING_SPEED> <!-- m/s -->
   
  <MAX_ALTITUDE_TO_CONSIDER_UNKNOWN_STATE_AS_LANDED> 0.40 </MAX_ALTITUDE_TO_CONSIDER_UNKNOWN_STATE_AS_LANDED> <!-- m   -->
</MAX_ALTITUDE>


<CONTROLLER_SATURATIONS>
  <ML_AUTOPILOT_MAX_ALLOWED_YAW_SPEED> 30.0</ML_AUTOPILOT_MAX_ALLOWED_YAW_SPEED> <!-- deg/s -->
      
  <ML_AUTOPILOT_MAX_ALLOWED_ALTITUDE_SPEED>0.5 </ML_AUTOPILOT_MAX_ALLOWED_ALTITUDE_SPEED> <!-- m/s   -->
</CONTROLLER_SATURATIONS>
```

- MAX_ALTITUDE parameter as the the name says defines the maximum altitude that can be achieved by the UAV. Note: when using the px4flow sensor for altitude measurement, the height is always limited to 3 meters.

- MAX_ALTITUDE_DESCENDING_SPEED parameter defines the maximum descending speed which a UAV can achieve while landing.

- MAX_ALTITUDE_TO_CONSIDER_UNKNOWN_STATE_AS_LANDED parameter publishes the unknown state landed below a given altitude. The midlevel controller always publishes the states of the UAV where it is landed, taking off, flying etc, if in case the state is unknown the and the altitude is below.

- MAX_ALTITUDE_TO_CONSIDER_UNKNOWN_STATE_AS_LANDED parameter the midlevel controller will publish the state as landed.

- ML_AUTOPILOT_MAX_ALLOWED_YAW_SPEED parameter defines the maximum yaw speed for the UAV, recommended to keep it at 30 deg/s. 

- ML_AUTOPILOT_MAX_ALLOWED_ALTITUDE_SPEED defines the maximum allowed altitude speed, right now the midlevel controller does not work properly with altitude speed more that 0.5 m/s. 

The next set of parameters define the maximum and minimum tilt value, change in yaw value and the thrust value. This values remain constant to a specific autopilot of the UAV, which can obtained from the manufacturer of the UAV. In the below case the values are for the Asctec Pelican UAV obtained from the astec manufacturers. 

```xml
<LL_AUTOPILOT>

  <LL_AUTOPILOT_COMMAND_TILT_MIN_VALUE>-51.175</LL_AUTOPILOT_COMMAND_TILT_MIN_VALUE> <!-- deg  -->

  <LL_AUTOPILOT_COMMAND_TILT_MAX_VALUE>+51.175</LL_AUTOPILOT_COMMAND_TILT_MAX_VALUE> <!-- deg  -->

  <LL_AUTOPILOT_COMMAND_DYAW_MIN_VALUE>-254.760</LL_AUTOPILOT_COMMAND_DYAW_MIN_VALUE> <!-- deg/s -->

  <LL_AUTOPILOT_COMMAND_DYAW_MAX_VALUE>+254.760</LL_AUTOPILOT_COMMAND_DYAW_MAX_VALUE> <!-- deg/s -->

  <LL_AUTOPILOT_COMMAND_THRUST_MIN_VALUE>0.000</LL_AUTOPILOT_COMMAND_THRUST_MIN_VALUE> <!-- N   -->

  <LL_AUTOPILOT_COMMAND_THRUST_MAX_VALUE>+32.000</LL_AUTOPILOT_COMMAND_THRUST_MAX_VALUE> <!-- N  -->
    
</LL_AUTOPILOT>
```

The next set of values define the altitude controller which is the first controller inside the midlevel controller as mentioned above. 

```xml
<altitude_speed_controller>
     
  <FEEDFORWARD_M>  2.11  </FEEDFORWARD_M> <!-- kg  -->

  <THRUSTER_GAIN> 0.3065625 </THRUSTER_GAIN> <!-- 1p1/kg, pelican: 1/(32/9.81)-->
    
  <GAIN_P>        0.10      </GAIN_P> <!-- Pelican: 0.1, 1p1/(m/s)-->
    
  <GAIN_I>        0.08      </GAIN_I> <!-- Pelican:(GAIN_P / 1.25),1p1/(s*m/s)-->

  <GAIN_D>        0.00      </GAIN_D> <!-- Pelican:(GAIN_P * 0.00),1p1*s/(m/s)-->

    
  <ALT_SPEED_MEASURE_SATURATION_FACTOR> 3.0</ALT_SPEED_MEASURE_SATURATION_FACTOR>

  <COMMAND_UPPER_LIMIT>  0.33  </COMMAND_UPPER_LIMIT>  <!-- Pelican:(     	450.0 / 4095.0 ) -->

  <COMMAND_LOWER_LIMIT> -0.11  </COMMAND_LOWER_LIMIT>  <!-- Pelican: ( (-1.0) *  150.0 / 4095.0 ) -->

  <SUBSAMPLING_DIVIDER>  6  	</SUBSAMPLING_DIVIDER> <!-- Pelican: 6 -->
	
</altitude_speed_controller> 
```

- FEEDFORWARD_M parameter is in kilograms the value at which the UAV can manitain its altitude. It can be calculated as follows. The user first must know the value in the terms units of the radio at which the UAV holds altitude, this can be found out manaully flying the UAV. For example in case of pelican it was found that with the current payload it holds altitude at 2560 counts using the radio,  and hence FEEDFORWARD_M is: 2650 * (32/9.81) * (1/4095)   = 2.11 kgs, where 32: LANDING_WITH_TIME_FIXED_THRUST_KG, 4095: The maximum thrust in units of the radio (counts), 9.81: Acceleration due to gravity.

- THRUSTER_GAIN parameter can be calculated as follows: 1/(32/9.81) where 32: LANDING_WITH_TIME_FIXED_THRUST_KG, 9.81: Acceleration due to gravity.
	
- GAIN_P parameter is the most important parameter, should be started with a smaller value like 0.01, until the UAV does not oscillate in the altitude. 

- GAIN_I parameter should be increased from a smaller value like 0.01 until the UAV reaches its setpoint which is 1.1 meters in this case.

- GAIN_D parameter influences how fast the UAV reaches the given the setpoint. Higher values can make it very responsive and can be kept to very less value or zero as in case of pelican. 

- ALT_SPEED_MEASURE_SATURATION_FACTOR parameter deprecated.

- COMMAND_UPPER_LIMIT and COMMAND_LOWER_LIMIT set the maximum and minimum saturations for the altitude controller. 

- SUBSAMPLING_DIVIDER currently not used. 

The next set of parameters define are used for tuning the hover controller. 

```xml
<hover_controller>

  <GAIN_P>     9.00 </GAIN_P>      <!-- [deg / (m/s)]  -->

  <GAIN_I>     1.80 </GAIN_I>      <!-- Ti = 5s, (GAIN_P / 5.0)  -->

  <GAIN_D>     0.50 </GAIN_D>      <!-- -->

  <MAX_OUTPUT> 12.00 </MAX_OUTPUT> <!-- [deg] -->

  <ALTITUDE_FOR_NOMINAL_D> 0.70 </ALTITUDE_FOR_NOMINAL_D> <!-- [m]   -->

</hover_controller>
```

- GAIN_P parameters as for all the PID controllers is most important, higher the gain_p the more the oscillations UAV about a given position. Gain_p parameter should be set a value where the UAV is not too sluggish or responsive at a desired position.

- GAIN_I parameter makes the UAV maintain its desired setpoint position. In this case the gain_I should be gain_p/5.

- GAIN_D parameter parameter influences how fast the UAV can reach the desired attitude, hence higher values tend to make the UAV more responsive.

- MAX_OUTPUT parameter defines the minimum and maximum saturations for the hover controller.

- ALTITUDE_FOR_NOMINAL_D is the altitude value upto which the gain_d is considered by the controller after which the gain_d becomes zero. 

The next set of values are for the yaw controller which is currently a PD controller. 

```xml
<yaw_controller>

  <GAIN_P> 5.00 </GAIN_P> <!-- [deg/s / (deg)]  -->

  <GAIN_I> 0.00 </GAIN_I> <!--  -->

  <GAIN_D> 0.50 </GAIN_D> <!-- (0.1 * GAIN_P) -->

</yaw_controller>
```

- GAIN_P parameter can be tuned the same way as in the above controllers.

- GAIN_D parameter is 0.1*gain_p
