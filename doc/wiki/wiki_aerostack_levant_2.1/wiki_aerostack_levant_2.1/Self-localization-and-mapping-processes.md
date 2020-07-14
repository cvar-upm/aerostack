| Process | System | Launcher  | Comments |
| :-------| :------- | :-------- |:-------- |
| Self Localization Selector | Situation awareness |self_localization_selector_process.launch | Selector of self localization method |
| Visual markers localizer | Situation awareness |droneVisualMarkersLocalizerROSModule.launch |Self-localization by Aruco visual markers |
| Obstacle detector visual marks |Situation awareness	|droneObstacleProcessor2d VisualMarksROSModule.launch |Self-localization by Aruco visual markers |
| Obstacle distance calculator | Situation awareness	|droneObstacleDistance CalculationROSModule.launch |Self-localization by Aruco visual markers |
| Self localizer | Situation awareness	|droneEKFStateEstimatorROSModule.launch	| Self-localization by Aruco visual markers|