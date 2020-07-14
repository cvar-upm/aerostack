With this project, you can launch Aerostack with Rotors simulator and execute a mission to perform the inspection of a bridge. The mission is specified as a behavior tree. 

After installing this project, perform the following steps to use this project:

1. Open a terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/bridge_inspection_rotors_simulator

1. Execute the ROS master node:

        $ roscore

1. Execute the script that launches Gazebo for this project:

        $ ./launcher_gazebo.sh

    A Gazebo window is presented with a simulated drone.

    [[Files/ProjectBIRSGazebo.png]]

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    A window showing the camera view is presented:

    [[Files/ProjectBIRSCamera.png]]

    A window showing the behavior tree is presented:

    [[Files/ProjectBIRSBehaviorTree.png]]

1. Click on the button `Start mission` to initiate the mission execution.

After this, you should see the drone moving in the simulated environment, performing the mission specified in the behavior tree. 

You can change behavior tree by executing the behavior tree editor with the following script:

        $ ./mission_editor_launcher.sh

Here there is a video that shows how to launch the project:

[ ![Launch project](https://img.youtube.com/vi/5Tza9svcE6Q/0.jpg)](https://www.youtube.com/watch?v=5Tza9svcE6Q)

Here there is a video that shows the mission execution:

[ ![Rotors Simulator Mission](https://img.youtube.com/vi/1sX4oj02Muw/0.jpg)](https://www.youtube.com/watch?v=1sX4oj02Muw)


## Credits

The original model of the bridge (format .obj) was created by Vishnu Srinivas (nikname mishukutti) and it is available at [Thingiverse](https://www.thingiverse.com/thing:930826). The model was modified for this Aerostack project and adapted to be used with the Gazebo simulator.
