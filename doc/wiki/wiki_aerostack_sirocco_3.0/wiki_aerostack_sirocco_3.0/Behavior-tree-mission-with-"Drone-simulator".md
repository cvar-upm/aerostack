With this project, you can launch Aerostack with Drone-simulator and execute a mission using a behavior tree. The mission performs simple actions (e.g., take off, follow a path, land, etc.) by executing the corresponding behaviors. After installing this project, perform the following steps to use this project:

1. Execute the ROS master node:

        $ roscore

1. Open a terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/basic_behavior_tree_drone_simulator

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    An ArViz window will pop up showing a 3D image with a drone.

    [[Files/ProjectBTDSArVizDroneSimulator.png]]

    The window of the execution viewer is presented. This helps to monitor the behaviors that are executed during the mission execution:

    [[Files/ProjectBTDSExecutionViewer.png]]

    The window of behavior tree viewer is also presented, showing the mission specification:

    [[Files/ProjectBTDSBehaviorTree.png]]

1. Press the `Start mission` button to start executing the mission.

After this, you should see the drone moving in the simulated environment, performing the mission specified in the behavior tree. 

You can change behavior tree by executing the behavior tree editor with the following script:

        $ ./mission_editor_launcher.sh

Here there is a video that shows the execution of the mission:

[ ![Drone Simulator Mission](https://img.youtube.com/vi/qWHkJ2wynEI/0.jpg)](https://youtu.be/qWHkJ2wynEI)