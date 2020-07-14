Follow these steps to specify the tasks of a mission:

### 1. Edit the Mission Specification File

The task-based mission of the robot is specified in a XML file called `mission_specification_file.xml` (this is the default name, as it is established in the .launch file located within the `launch` directory in the repository `task_based_mission_planner_process`). This file must be located in `$AEROSTACK_STACK/configs/` within a folder selected by the operator called `drone{Id}` (`{Id}` = 00, 01, 02, ...).

Write your own mission specification file according to [[TML language]]. 

### 2. Check Syntax Errors

To check if the file has syntax errors, launch the mission planner executing the following command:
        
    $ roslaunch task_based_mission_planner_process task_based_mission_planner_process.launch

If the xml file does not have any errors, the following message is presented:

    File loaded without errors! Waiting to start ...
