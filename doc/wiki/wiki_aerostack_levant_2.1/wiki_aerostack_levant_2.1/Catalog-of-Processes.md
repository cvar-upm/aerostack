This page shows the catalog of available processes in Aerostack. Processes are organized according to the general architecture:

[[Files/Architecture.png]]

For each process, the catalog shows the launcher to be used and the system to which it belongs. 

| PROCESSES |
| :-----------|
| [[Physical layer processes]] |
| [[Feature extraction processes]] |
| [[Self localization and mapping processes]] |
| [[Motion control processes]] |
| [[Belief management processes]] |
| [[Execution processes]] |
| [[Motion planning processes]] |
| [[Communication processes]] |

To ensure the correct supervised execution of the processes it is also necessary to run the next launcher:

|  Process | System | Launcher  |
| :-------| :------- | :-------- |
| Process monitor | Supervision system  | process_monitor_process.launch |