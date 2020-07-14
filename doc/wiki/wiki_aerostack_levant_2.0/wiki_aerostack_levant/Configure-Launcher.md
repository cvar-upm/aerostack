The launcher is a file that specifies the set of processes that will be executed for a particular aerial robot system and and a specific mission to be done.

To configure a launcher, it is necessary to select a particular set of Aerostack processes. Each basic functionality (e.g., recognize ArUco visual markers, self-localization, mission planning, etc.) is provided by a set of processes. To configure the launcher, perform the following steps.

Go to the folder that contains examples of launchers. This folder includes .sh files that launch sets of processes for different architecture configurations:

```
$ cd ${AEROSTACK_STACK}/launchers
```

Select the .sh file that corresponds to an architecture similar to the architecture that you want to to create. Copy the selected file into a new .sh file. Edit the content of the new .sh file to add or remove processes. For example, to add the process task_based_mission_planner, add a new call to roslaunch such as the following:

```
gnome-terminal  \
...
--tab --title "Mission Planner" --command "bash -c \"
roslaunch task_based_mission_planner_process task_based_mission_planner_process.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
...
```

To know the available functionalities and processes provided by Aerostack, see the following catalogue:

- [[Catalog of Processes]] 