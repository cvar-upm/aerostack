Rotors is a computer program (based on the simulator Gazebo) that simulates the dynamics of a quadrotor. With this project, you can launch Aerostack with Rotors and execute a mission written in Python language. After installing this project, perform the following steps:

1. Execute the ROS master node:

        $ roscore

1. Open a terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/basic_mission_rotors_simulator

1. Execute the script that launches Gazebo for this project:

        $ ./launcher_gazebo.sh

    A Gazebo window is presented with a simulated drone.

    [[Files/ProjectBMRSGazebo.png]]

1. You can see the tasks of the mission plan in the Python file. For example, write the following command to see the content of the file with the mission plan:

         $ more configs/mission/mission.py 

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    The window of the execution viewer is presented. This helps to monitor the behaviors that are executed during the mission execution:

    [[Files/ProjectBMRSExecutionViewer.png]]

1. Write the following command to execute the mission:

        $ rosservice call /drone111/python_based_mission_interpreter_process/start

After this, you should see the drone moving in the simulated environment, performing the mission specified in the mission file. You can change the Python file to add, modify or remove tasks of the mission plan, and execute again the mission with these changes.

Here there is a video that shows the execution of the mission:

[ ![Rotors Simulator Mission](https://img.youtube.com/vi/wLo4T_6d_OI/0.jpg)](https://www.youtube.com/watch?v=wLo4T_6d_OI)