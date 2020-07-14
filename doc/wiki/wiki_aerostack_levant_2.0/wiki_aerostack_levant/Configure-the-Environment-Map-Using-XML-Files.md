The environment map of the robot can be specified in a series of configuration files which follow XML syntax. These files are located at `$AEROSTACK_STACK/configs/` within a folder selected by the operator called `drone{Id}` (`{Id}` = 00, 01, 02, ...). The `Id` parameter is the identification of the drone used for the mission, which is specified in the launch file used. To change the configuration of the environment map follow these steps.

### 1.Defining the Size of the Map 

The size of the map is defined in `configFile.xml`. For example:

```xml
<map>
  <config>
    <dimensions>4.0 6.0</dimensions>
    <initPoint>0.0 0.0</initPoint>
  </config>
</map>
```

The `<dimensions>` parameter specifies the size (x, y) in meters of the perimeter of the flight zone. The `<initPoint>` specifies where the origin to the perimeter of the map will be. This parameter can be set in any value and has to be taken into account when placing the obstacles in the map. In this example the map size is 4m x 6m and the init point is set to (0,0).

[[Files/MapDimensions.png]]

### 2.Defining the Take-off Point

The take-off point should be specified in two files: 

- the file `ekf_state_estimator_config.xml` 
- the localization initial point in the file `param_localization_obs.xml`

For this example the start point in the x and y coordinates is (1m, 1m). Therefore, both files have this point set to (1, 1) but some changes must be made for each of these files. 

**2.1 EKF Take-off Point**

The take-off point defined in `ekf_state_estimator_config.xml specifies the take-off point used by the (Extended Kalman Filter) EKF to start the estimation. This estimation is started with the drone in landed position so the height (z) is set to 0. 

``` xml
<take_off_site>
  <position>
    <x>1.0</x>
    <y>1.0</y>
    <z>0.0</z>
  </position>
  <attitude>
    <yaw>  90.00</yaw>
    <pitch> 0.00</pitch>
    <roll>  0.00</roll>
  </attitude>
</take_off_site>
```

Units:

- Units for tag `<position>`: meters

- Units for tag `<attitude>`: degrees (wYcPuR)

**2.2 Aruco Visual Marker Take-off Point**

The take-off point specified by the `param_localization_obs.xml` is used to determine where the Aruco visual marker localization start point is set in the map. This start point for the localization is done after takeoff and therefore is set to z = 0.7m.

``` xml
<!-- Localization  -->
  <!-- Init pose  -->
  <x_0> 1.0</x_0>
  <y_0> 1.0</y_0>
  <z_0> 0.7</z_0>
  <yaw_0>  90.0</yaw_0>
  <pitch_0> 0.0</pitch_0>
  <roll_0>  0.0</roll_0>
```

Position is specified in meters and angles are given in degrees.

As you can see, both of these configuration files have initial values for Roll, Pitch and Yaw. Roll and Pitch will have a value of zero, since localization is started with these values. Nevertheless, the Yaw value is given according to the mission requirements of the user. If the user wishes to have the drone take-off facing the +x axis then this yaw value will be 0. In this example the dronewill take-off facing the +y axis so the rotation in yaw is +90deg.
 
### 3. Creating Obstacles and Virtual Walls

Walls and obstacles are defined in the `obstacle_config.xml` file. This file allows the creation of obstacles that can be real (to be detected by Aruco visual markers) or can be virtual. 

Virtual walls cover the area of the map in order to restrain the movement of the drone to the desired map space. They can be created based on the size of the map. For example for a map of 4x6, the virtual borders can be defined as shown in the figure below. 

``` xml
<!-- borders (Virtual Obstacles): 10000-19999 -->
<rectangle description="bottom side">
  <id>10000</id>
  <centerPoint>2.0 0.0</centerPoint>
  <size>4.0 0.3</size>
  <yawAngle>0.0</yawAngle>
  <virtual description="define a virtual object">1</virtual>
  </rectangle>

<rectangle description="right side">
  <id>10001</id>
  <centerPoint>4.0 3.0</centerPoint>
  <size>0.3 6.0</size>
  <yawAngle>0.0</yawAngle>
  <virtual description="define a virtual object">1</virtual>
  </rectangle>

<rectangle description="up side">
  <id>10002</id>
  <centerPoint>2.0 6.0</centerPoint>
  <size>4.0 0.3</size>
  <yawAngle>0.0</yawAngle>
  <virtual description="define a virtual object">1</virtual>
  </rectangle>

<rectangle description="left side">
  <id>10003</id>
  <centerPoint>0.0 3.0</centerPoint>
  <size>0.3 6.0</size>
  <yawAngle>0.0</yawAngle>
  <virtual description="define a virtual object">1</virtual>
  </rectangle>
```

Besides specifying the boundaries of the map to be flown, the `obstacle_config.xml` file relates Aruco visual markers to obstacles in the map. 

``` xml
<pole description="A">
  <id>50002</id>
    <radius>0.15 0.15</radius>
    <aruco>
      <id aruco_id = "17"/>
      <id aruco_id = "18"/>
      <id aruco_id = "19"/>
      <id aruco_id = "20/>
    </aruco>
</pole>
```

As can be seen from the figure above, four Aruco markers (id: 17, 18, 19, 20) are used to define an obstacle, in this case a pole of 0.15 radius. With this file the user can specify which Aruco markers make up an obstacle and the geometry it can have.  

### 4. Placing Aruco Visual Markers in the Map

The location of the visual markers used in the world is defined in the 'param_localization_obs.xml' file. In this file the user can specify the Aruco Slam details. Here the visual marker Ids that can be mapped by visual slam can be specified with `<VisualMarkersRange>`. 

Also in this file the user can specify the fixed visual markers in the map. 

**4.1 Visual Markers for Obstacles**

This example uses three poles as known obstacles to navigate through and avoid. The location of each pole is given by the (x, y, z) coordinates of the center of the Aruco placed on the pole. Since the size of the poles used in this mission are 40cm in diameter, the location for the center of each Aruco is shown in the following example: 

```xml
<!-- Pole 1 -->
<Aruco id="9"  x="3.0"  y="1.80" z="1.3" roll="0" pitch="0" yaw="-90"/>
<Aruco id="10" x="2.80" y="2.0"  z="1.3" roll="0" pitch="0" yaw="180"/>
<Aruco id="11" x="3.0"  y="2.20" z="1.3" roll="0" pitch="0" yaw="90"/>
<Aruco id="12" x="3.20" y="2.0"  z="1.3" roll="0" pitch="0" yaw="0"/>

<!-- Pole 2 -->
<Aruco id="13" x="1.0"  y="1.80" z="1.3" roll="0" pitch="0" yaw="-90"/>
<Aruco id="14" x="0.80" y="2.0"  z="1.3" roll="0" pitch="0" yaw="180"/>
<Aruco id="15" x="1.0"  y="2.20" z="1.3" roll="0" pitch="0" yaw="90"/>
<Aruco id="16" x="1.20" y="2.0"  z="1.3" roll="0" pitch="0" yaw="0"/>

<!-- Pole 3 -->
<Aruco id="25" x="2.0"  y="4.80" z="1.3" roll="0" pitch="0" yaw="-90"/>
<Aruco id="26" x="1.80" y="5.0"  z="1.3" roll="0" pitch="0" yaw="180"/>
<Aruco id="27" x="2.0"  y="5.20" z="1.3" roll="0" pitch="0" yaw="90"/>
<Aruco id="28" x="2.20" y="5.0"  z="1.3" roll="0" pitch="0" yaw="0"/>
```

Where the desired location of the obstacles is (3.0,2.0), (1.0,2.0) and (2.0, 5.0).

[[Files/MapObstacles.png]]

**4.1 Visual Markers for Landmarks (for Self-Localization)**

Besides the known pole location, landmarks are used for self-localization and are generally placed at the end of the map  (e.g., where the mission of visual servoing will be performed). Each landmark carries two Aruco visual markers. If the landmark is placed on the y axis facing to the right, 0.11 needs to be subtracted from the y axis of the first aruco and 0.11 needs to be added to the y axis of the second aruco as shown in the figure below. 

```xml
<!-- Landmark 1 -->
<Aruco id="61" x="0.0" y="3.89" z="1.3" roll="0" pitch="0" yaw="-45"/>
<Aruco id="62" x="0.0" y="4.11" z="1.3" roll="0" pitch="0" yaw="45"/>
```


If the landmark is placed on the x axis, facing the take-off point 0.11 needs to be subtracted from the x axis of the first aruco and 0.11 needs to be added to the x axis of the second aruco as shown in the figure below

```xml
<!-- Landmark 4 -->
<Aruco id="69" x="2.89" y="6.0" z="1.3" roll="0" pitch="0" yaw="225"/>
<Aruco id="70" x="3.11" y="6.0" z="1.3" roll="0" pitch="0" yaw="-45"/>
```

In this example, six landmarks are used:

```xml
<!-- Landmark 1 -->
<Aruco id="61" x="0.0" y="3.89" z="1.3" roll="0" pitch="0" yaw="-45"/>
<Aruco id="62" x="0.0" y="4.11" z="1.3" roll="0" pitch="0" yaw="45"/>

<!-- Landmark 2 -->
<Aruco id="63" x="0.0" y="4.89" z="1.3" roll="0" pitch="0" yaw="-45"/>
<Aruco id="64" x="0.0" y="5.11" z="1.3" roll="0" pitch="0" yaw="45"/>

<!– Landmark 3 -->
<Aruco id="65" x="0.89" y="6.00" z="1.3" roll="0" pitch="0" yaw="225"/>
<Aruco id="66" x="1.11" y="6.00" z="1.3" roll="0" pitch="0" yaw="-45"/>

<!– Landmark 4 -->
<Aruco id="69" x="2.89" y="6.00" z="1.3" roll="0" pitch="0" yaw="225"/>
<Aruco id="70" x="3.11" y="6.00" z="1.3" roll="0" pitch="0" yaw="-45"/>

<!– Landmark 5 -->
<Aruco id="71" x="4.0" y="5.11" z="1.3" roll="0" pitch="0" yaw="225"/>
<Aruco id="72" x="4.0" y="4.89" z="1.3" roll="0" pitch="0" yaw="-45"/>

<!– Landmark 6 -->
<Aruco id="73" x="4.0" y="4.11" z="1.3" roll="0" pitch="0" yaw="135"/>
<Aruco id="74" x="4.0" y="3.89" z="1.3" roll="0" pitch="0" yaw="225"/>
```

### 5. Verify the Changes

After the environment is configured correctly, you can verify the changes using the RViz interface.
For this purpose, run the following command:

       $ ./rvizInterface_Test.sh drone{Id} localhost

It should presents a 3D image similar to this:

[[Files/MapComplete.png]]