| Process | System |  Launcher  | Comment |
| :-------| :----- | :--------- |:------- |
| Shell User Interface | Ground control system | droneInterface_jp_ROSModule.launch |Shell user interface|
| Graphical User Interface |Ground control system	| graphical_user_interface gui.launch	|Graphical User Interface|
| HUD |Ground control system	| first_view.launch	|Graphical User Interface|
| Speech module	|Ground control station | droneSpeechROSModule.launch	|Speech-based communication|
| Sound module| Ground control station | droneSoundROSModule.launch	|Speech-based communication. NOTE (1)|
|Leap motion|Ground control station | droneLeapMotionDrone ControlUserInterface ROSModule.launch|Communication with leap motion|
| Communication manager	| Communication system	| droneCommunication Manager ROSModule.launch |Swarm Coordination|

NOTE (1): Required launcher: `${AEROSTACK_STACK}/launchers/sound_play.launch`
