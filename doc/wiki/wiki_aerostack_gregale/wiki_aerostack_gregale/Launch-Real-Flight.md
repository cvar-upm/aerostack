To launch a real flight using an AR Drone perform the following steps:

- First, connect the AR Drone to the computer using wifi.

- Launch the roscore

```
$ roscore
```
- Go to the folder that contains launchers. It includes different pre-configured .sh files that launch the set of processes for different mission types: 

```
$ cd ${AEROSTACK_STACK}/launchers
```
- In this example we select the file *ardrone_basic.sh*. Write the following to launch the mission:

```
$ ./ardrone_basic.sh
```

Then you can use the human machine interface to start the mission (see [[Human Machine Interface]]). The AR Drone will execute the mission defined in the config files.

