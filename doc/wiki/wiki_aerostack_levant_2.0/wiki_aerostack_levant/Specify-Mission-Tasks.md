The operator can specify a mission plan using three alternative options:
- TML language (a special-purpose language of Aerostack for mission plans).
- Behavior tree (with a graphical editor).
- Phyton language (with a library of functions).

### Specify mission tasks in TML language

Follow these steps to specify the tasks of a mission using TML language:

- Edit the mission specification file. The TML mission of the robot is specified in a XML file called `mission_specification_file.xml` (this is the default name, as it is established in the .launch file located within the `launch` directory in the repository `task_based_mission_planner_process`). This file must be located in `$AEROSTACK_STACK/configs/` within a folder selected by the operator called `drone{Id}` (`{Id}` = 00, 01, 02, ...). Write your own mission specification file according to [[TML language]]. 

- Check syntax errors. To check if the file has syntax errors, launch the mission planner executing the following command:

```
> roslaunch task_based_mission_planner_process task_based_mission_planner_process.launch
```

- If the xml file does not have any errors, the following message is presented:

```
File loaded without errors! Waiting to start ...
```

### Specify mission tasks using a behavior tree

Aerostack provides a graphical editor to specify missions using a visual modeling language. To know how to specify a mission with behavior trees, consult the following link:

- [[Behavior tree]]

### Specify mission tasks in Python language

The operator of Aerostack may use Python language to specify a mission plan. To know how to specify a mission in Python language, consult the following link:

- [[Python language]]