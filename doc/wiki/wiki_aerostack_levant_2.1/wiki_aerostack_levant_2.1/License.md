

**Aerostack** - A Software Framework for Aerial Robotic Systems

Copyright (C) 2016-2018 Technical University of Madrid

BY INSTALLING, COPYING OR OTHER USES OF SOFTWARE YOU ARE DECLARING THAT YOU AGREE WITH THE TERMS AND CONDITIONS OF THIS LICENSE AGREEMENT. IF YOU DO NOT AGREE WITH THE TERMS AND CONDITIONS, DO NOT INSTALL, COPY OR USE THE SOFTWARE

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the [GNU General Public License](http://www.gnu.org/licenses/gpl-3.0-standalone.html) for more details.

<p align="center">[[Files/LogoGPLv3.png]]</p>

## Safety Warning and Disclaimer

IMPORTANT: It is important to note that this software is provided 'as is' without warranty of any kind.  You are using this software at your own risk. The authors and their institutions decline any responsibility for any harm or damage of any kind (e.g., personal injuries and/or property damage) caused by the use of this software or by following this instructions.

Some of the components of this software were developed as part of research work in an academic context in the form of prototypes with LIMITED VALIDATION. If you plan to use this software in a final application, be sure that you perform an additional EXHAUSTIVE VALIDATION procedure. 

Some drones supported by this framework ARE NOT TOYS. Even operation by expert users might cause SERIOUS INJURIES to people around. Therefore, be sure that you fly in a properly screened or isolated flight area.

## Third-Party Libraries

Aerostack uses other third-party open-source libraries:

- Robot Operating System ([ROS](http://ros.org/ "Robot Operating System")), license: `BSD` license, not included in the source of the stack.

- ardrone_autonomy ROS package ([ardrone_autonomy](https://github.com/AutonomyLab/ardrone_autonomy "ardrone_autonomy ROS package")), license: `BSD` license, not included in the source of the stack.

- Open Source Computer Vision library ([OpenCV](http://opencv.org/ "OpenCV")), license: `BSD` license, not included in the source of the stack.

- ArUco: a minimal library for Augmented Reality applications based on OpenCv ([ArUco](http://www.uco.es/investiga/grupos/ava/node/26 "ArUco")), original license: `BSD` license, included as source in the stack in the `lib_aruco` package.

- pugixml library ([pugixml](http://pugixml.org/ "pugixml")), original license: `MIT` license, included as source in the stack in the `lib_pugixml` package.

- newmat11 library, a matrix library in C++ ([newmat11](http://www.robertnz.net/nm11.htm "newmat11, a matrix library in C++")), original license: ([newmat11 license](http://www.robertnz.net/nm11.htm#use "newmat11 library license")), included as source in the stack in the `lib_newmat` package.

- other software libraries used by this stack also uses licenses similar to `BSD` and `MIT` licenses: [ncurses](https://www.gnu.org/software/ncurses/ "GNU ncurses") and [boost](http://www.boost.org "boost c++ libraries").