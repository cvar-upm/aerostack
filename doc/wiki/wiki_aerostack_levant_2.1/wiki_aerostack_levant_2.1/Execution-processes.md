| Process | System |  Launcher  | Comment |
| :-------| :------- | :-------- |:-------- |
|Manager of actions |Executive system | droneManagerOfActionsROSModule.launch |Execution of simple actions |
| Behavior coordinator | Executive system |behavior_coordinator_process.launch |Execution of behaviors |
| Behavior specialist | Executive system |behavior_specialist_process.launch |Execution of behaviors |
| Resource manager | Executive system |resource_manager_process.launch |Execution of behaviors|
| Mission plan interpreter (schedule processor)| Planning system | droneMissionSheduleProcessorROSModule.launch |Mission schedule processor|
| Mission plan interpreter (TML)| Planning system | task_based_mission_planner_process.launch |Task-based mission plan interpreter|
| Mission plan interpreter (Python)| Planning system | python_based_mission_interpreter_process.launch |Python-based mission plan interpreter|
