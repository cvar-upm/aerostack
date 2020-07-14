If your robotic system follows object images (with visual servoing), take into account the following considerations.

### OpenTLD GUI for Visual Servoing
When you are using the OpenTLD GUI you have to press the F5 button to refresh the image on the screen, select the area you want the drone to follow and then press and hold (just for few seconds) the ENTER key. Then the drone will start following the selected area. 

### Visual servoing processes
If visual servoing produces unxpected behavior, double check that the following processes have been started (with ``` rosnode list ```):
* /droneN/droneIBVSController
* /droneN/open\_tld\_translator
* /droneN/ros\_tld\_tracker\_node
* /droneN/ros\_tld\_gui\_node
* /droneN/trackerEye