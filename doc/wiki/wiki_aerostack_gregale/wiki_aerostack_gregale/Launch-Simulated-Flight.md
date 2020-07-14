Before real flights, a mission can be simulated with the Rviz simulator. 

First, start a roscore in the host system:

    $ roscore

Next, to launch the simulation go to the launchers/Noche_de_los_investigadores folder and run: 

    $ ./quadrotor_laNocheInvestigadores_simulator.sh {droneId} localhost

The {droneId} argument is the Id for the drone config files that were created and the localhost parameter is used to specify you are running the roscore on your host computer. This will open up several terminals with the modules running. To visualize the mission in Rviz, in another terminal run the following command:

    $ ./rvizInterface_Test.sh {droneId} localhost

This will bring up the Rviz simulator but will not start the simulation. Finally, launch the mission by typing the following command in a sourced terminal.

    $ rosservice call /drone{Id}/droneMissionScheduleProcessor/start 

Sample screenshot of drone simulator in RVIZ with example mission:
 
[[images/MapComplete.png]] 

