Aerostack supports all types of ueye cameras with usb. There are ROS packages in the Aerostack for the ueyecameras which take the data from the camera and then publishes the camera data using the suitable config files provided by the user. Adding a new camera to the Aerostack is relatively easy and can be done in the following steps. 

1. Installing the ueyecamera driver
1. Getting the camera_id
1. Generating a suitable config file 
1. Generating a camera calibration file 
1. Launching the ueyecamera node

## 1. Installing the Ueyecamera Driver

The most important thing in order to add a new camera to the stack is installing the drivers for the ueyecamera. Note that installing the ueyecamera drivers is mandatory when installing the Aerostack because without the ueyecamera drivers the Aerostack will never be build. But just in case if the ueyecamera drivers are not installed here is how it can be done. 

The link to download the ueyecamera can be found here

  https://en.ids-imaging.com/download-ueye-lin64.html

The user has to install the drivers for linux. The installing instructions for installing the ueyecamera drivers is properly mentioned in a text file which comes along with the drivers. 

## 2. Getting the camera_id

After installing the ueyecamera drivers, the user has to check the camera_id of the connected ueyecamera. Which can be done as follows. Open the Gnome terminal and type the command ueyecameramanager and a window will open showing all the connected cameras to the computer.

The figure below shows an example of the ueyecameramanager connected with one camera and with all its properties. The camera_id can then be seen under the cam ID section.

[[images/CameraManager.png]]

## 3. Generating a Suitable Config File

The config file is an important file, using which the user can define all the properties of the camera, for example the parameters like the brightness, frame rate, exposure and many more. In order to set these parameters the camera needs to be opened first. It can be done by right clicking on the available camera in the screen shown in the above figure. 

After opening the camera, all the camera parameters can be set as desired by the user. After setting the desired camera parameters, the user then has to save the config file with the desired parameters. The config file has to be saved inside DRONE_STACK/Configs/drone_id. The number of the drone_id depends on the drone which the user is using. For example if the user is using the camera with Asctec Pelican the config file needs to be saved in drone0, as drone0 is currently being used for the Astec Pelican. 

Also there are some default config files for the ueye cameras which are already there inside DRONE_STACK/Configs/drone_id. small_camera_RGB24_HUB.ini is one such config file which is already being generated with certain camera parameters. It completely depends on the user to choose as to which camera config is the best. 

## 4.  Generating a Camera Calibration File

The camera calibration file contains the necessary camera calibration data like the focal length, projection matrix etc of the camera. The camera calibration file can be generated using the ROS camera calibration package which can be found in the link below:

http://wiki.ros.org/camera_calibration 

After generating the suitable calibration file for the camera it can then be saved inside the same folder DRONE_STACK/Configs/drone_id. Where again drone_id depends on the drone the user is using. An example of the calibration file can be found below.

```
image_width: 640
image_height: 360
camera_name: front
camera_matrix:
  rows: 3
  cols: 3
  data: [466.6953647276067, 0, 306.515467461629, 0, 466.1550228548235, 169.6544700845251, 0, 0, 1]
distortion_model: plumb_bob
distortion_coefficients:
  rows: 1
  cols: 5
  data: [-0.3088667172761168, 0.1060937937543472, -0.001639357143514502, 0.0004536735112699787, 0]
rectification_matrix:
  rows: 3
  cols: 3
  data: [1, 0, 0, 0, 1, 0, 0, 0, 1]
projection_matrix:
  rows: 3
  cols: 4
  data: [391.9715881347656, 0, 301.7997751755956, 0, 0, 442.0516967773438, 167.6912864963015, 0, 0, 0, 1, 0]
```
 
Note that the format of the calibration file should be same as the above file or the ueye package in the Aerostack will fail to start. The camera calibration file has to be saved with the same camera name which is will be used by the user in the launch file to launch the camera. For example, if the name of the camera is front, the name of the calibration file has to be front.yaml. 

## 5. Launching the Ueyecamera Node

The user has to make a suitable launch file in order to launch the ueyecamera with the proper config file and the calibration file as well as with the proper camera name and camera_id. An example of such a launch file can be found below. 

```xml
<!-- launches: ueye_cvg node -->
<launch>
    <arg name="camera_id_num" default="1"/>
    <arg name="config_file" default="small_camera_RGB24.ini"/>
    <arg name="camera_name_str" default="front" />

    <arg name="drone_id_int" default="0" />
     <arg name="my_stack_directory" default="$(env DRONE_STACK)" />

    <group ns="drone$(arg drone_id_int)">
     <node name="cvg_ueye_cam$(arg camera_id_num)_$(arg camera_name_str)" pkg="driver_camera_ueye_ROSModule" type="driver_camera_ueye_ROSNode" output="screen">
      <param name="camera_ident_number" value="$(arg camera_id_num)" type="int"/>
      <param name="configuration_file" value="$(arg my_stack_directory)/configs/drone$(arg drone_id_int)/$(arg config_file)" type="string"/>
      <param name="camera_name"   value="$(arg camera_name_str)" type="string"/>
      <param name="topic_name" value="camera/$(arg camera_name_str)"  type="string"/>
      <param name="droneId" value="$(arg drone_id_int)" type="int"/>
      <param name="stackPath" value="$(arg my_stack_directory)" type="string"/>
      <param name="cam_intr_filename"  value="$(arg my_stack_directory)/configs/drone$(arg drone_id_int)/$(arg camera_name_str).yaml" type="string"/>
     </node>
   </group>
</launch>
```

The above launch file launches the ueyecamera node in the Aerostack with parameters and files as explained below:

- The first argument in the launch file is the camera_id where the user inputs the camID seen from the ueyecameramanager. In this example the camera_id is 1. 

- The second argument defines the name of the config file, which is small_camera_RGB24.ini in this case above. 

- The third argument is the camera name which is front in the above case.  The fourth and the fifth argumets defines the drone_id being used and the environment for the Aerostack. 

After all the arguments the ueyecamera ROS node is launched with the name “cvg_ueye_cam$(arg camera_id_num)_$(arg camera_name_str)”. Hence here in the above case the name of the ueyenode would be cvg_ueye_cam1_front. 

After launching the node, the parameters for the node are set:

- The first parameter is the camera_id. 

- The second parameter is the assigns the camera config file, which takes the value "$(arg my_stack_directory)/configs/drone$(arg drone_id_int)/$(arg config_file)". In the above it is 
- $DRONE_STACK/configs/drone0/small_camera_RGB24.ini 

- The third parameter is the name of the camera, in the above case the camera name is front. 

- The fourth parameter defines the topic name which contains the camera data, which takes the camera/$(arg camera_name_str). In the above case it is camera/front. 

- The fifth and the sixth parameters are the drone_id and the stack_path. 

- The seventh parameter is the assigns the camera calibration file, which takes the value “$(arg my_stack_directory)/configs/drone$(arg drone_id_int)/$(arg camera_name_str).yaml”. In the above case the calibration file is assigned as follows $DRONE_STACK/configs/drone0/front.yaml"                  

The above launch file can be launched using the roslaunch command assigning all the camera arguments. For example:

```
roslaunch driver_camera_ueye_ROSModule driver_camera_ueye_ROSNode 
--wait camera_id_num:=2 
         camera_name_str:="front" 
         config_file:="small_camera_RGB24_HUB.ini"
```
