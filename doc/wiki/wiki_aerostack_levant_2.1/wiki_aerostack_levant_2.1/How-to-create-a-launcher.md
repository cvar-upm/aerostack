To create a launcher for a particular robotic system, it is necessary to specify in this file the Aerostack processes that are required for this robotic system. Each basic capability (e.g., recognize ArUco visual markers, self-localization, mission planning, etc.) is achieved by a subset of processes. To know the available capabilities and their processes in Aerostack, see the following catalog:

- [[Catalog of Processes]] 

To configure the launcher, select the .sh file that corresponds to an architecture similar to the architecture that you want to to create. Copy the selected file into a new .sh file. Edit the content of the new .sh file to add or remove processes. For example, to add the process task_based_mission_planner, add a new call to roslaunch such as the following:

```
xfce4-terminal  \
...
--tab --title "Mission Planner" --command "bash -c \"
roslaunch task_based_mission_planner_process task_based_mission_planner_process.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
...
```

## Configuration folders

Launchers are associated to configuration folders. In general, launchers use a default folder. For example, the launcher `ardrone_basic.sh` uses the default folder `${AEROSTACK_STACK}/config/drone1`. However, this number can be changed by providing as a first argument of the launcher the desired number of folder.

By convention, the configuration folders are called `droneX`, where X can be a number 0, 1, 2, ..., etc. Each configuration folder includes the configuration files corresponding to a particular aerial platform. For example, the config folder `${AEROSTACK_STACK}/config/drone1` includes configuration files related to AR Drone 2.0. 

The configuration folder also includes files related to the mission plan. Developers can change these files to specify their particular mission plans. For this purpose, developers can either use one of the prefixed folders for a particular robotic system (and a mission plan) or developers can duplicate one of them to use a new folder (e.g., `${AEROSTACK_STACK}/config/drone75` as a copy of `${AEROSTACK_STACK}/config/drone1`).