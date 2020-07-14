With this project, you can launch Aerostack with Rotors simulator and execute a mission to perform the inventory of a warehouse. The mission is written in Python and the drone uses a lidar sensor and a QR recognizer. 

> IMPORTANT: This mission has only been tested in Ubuntu 16.04 with ROS Kinetic.

After installing this project, perform the following steps to use this project:

1. Open a terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/warehouse_rotors_simulation

1. This project uses "move_base" and "hector_slam" provided by the ROS library. To install "move_base" and "hector_slam", write the following commands (in this example we are using the ROS distribution ros-melodic, but you can use another distribution instead):

        $ sudo apt-get install ros-melodic-move-base*

        $ sudo apt-get install ros-melodic-hector*
     
        $ sudo apt-get install ros-melodic-amcl*

1. Install Rotors components of this project to be used by Rotors simulator:

        $ ./lidar_instalation.sh

1. Execute the ROS master node:

        $ roscore

1. Execute the script that launches Gazebo for this project:

        $ ./launcher_gazebo.sh

    A Gazebo window is presented with a simulated drone.

    [[Files/ProjectWRSGazebo1.png]]

1. You can zoom and rotate the image of the warehouse using the mouse.

    [[Files/ProjectWRSGazebo2.png]]

    [[Files/ProjectWRSGazebo3.png]]

1. You can see the tasks of the mission plan in the Python file. For example, write the following command to see the content of the file with the mission plan:

         $ more configs/mission/mission.py 

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    The window showing the map is presented:

    [[Files/ProjectWRSOccupancyGrid.png]]

1. Write the following command to show the camera image:

        $ rqt_image_view

    A window showing the camera image:

    [[Files/ProjectWRSCameraView.png]]

1. Write the following command to execute the mission:

        $ rosservice call /drone111/python_based_mission_interpreter_process/start

1. Write the following command to execute the mission:

        $ rosservice call /drone111/python_based_mission_interpreter_process/start

After this, you should see the drone moving in the simulated environment, performing the mission specified in the mission file. You can change the Python file to add, modify or remove tasks of the mission plan, and execute again the mission with these changes.

Here there is a video that shows the correct execution of the test:

[ ![Python Mission](https://img.youtube.com/vi/CkS9YU8LGmU/0.jpg)](https://youtu.be/CkS9YU8LGmU)