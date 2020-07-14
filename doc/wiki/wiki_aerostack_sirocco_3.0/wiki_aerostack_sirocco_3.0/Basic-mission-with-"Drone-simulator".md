With this project, you can launch Aerostack with Drone-simulator and execute a mission that is written in Python. The mission performs simple actions (e.g., take off, follow a path, land, etc.) by executing the corresponding behaviors. After installing this project, perform the following steps to use this project:

1. Execute the ROS master node:

        $ roscore

1. Open a terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/basic_mission_drone_simulator 

1. You can see the tasks of the mission plan in the Python file. For example, write the following command to see the content of the file with the mission plan:

         $ more configs/mission/mission.py 

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    An ArViz window will pop up showing a 3D image with a drone.

    [[Files/ProjectBMDSArVizDroneSimulator.png]]

    The window of the execution viewer is presented. This helps to monitor the behaviors that are executed during the mission execution:

    [[Files/ProjectBMDSExecutionViewer.png]]

1. Write the following command to execute the mission:

        $ rosservice call /drone111/python_based_mission_interpreter_process/start

After this, you should see the drone moving in the simulated environment, performing the mission specified in the mission file. You can change the Python file to add, modify or remove tasks of the mission plan, and execute again the mission with these changes.

Here there is a video that shows the execution of the mission:

[ ![Drone Simulator Mission](https://img.youtube.com/vi/sOgy5IW3aEc/0.jpg)](https://www.youtube.com/watch?v=sOgy5IW3aEc)