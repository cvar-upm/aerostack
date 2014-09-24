ARDrone camera calibration:
---------------------------

First, you have to print the image pattern and measure the size of the sides of the squares on it. You also have to count the number of inner corners of the checkboard pattern (the cornes in the border which are shared by only 1 squares are not to be counted). I like to use "calib_pattern.pdf" which should be in the same folder as this readme file. It comes from the ptam library (it is the pattern to be used if you want to calibrate your camera to be used with PTAM; which uses a really specific camera model).

Then, I use the camera calibration package that is already in ROS, because the GUI it has is really user friendly. Follow this steps:
	- Option 1: 
		run (sh script) on ${IMAV_2013_Repository}/launch_dir/ardrone_camera_calibration_frontcam_launcher.sh 
		run (sh script) on ${IMAV_2013_Repository}/launch_dir/ardrone_camera_calibration_bottomcam_launcher.sh 
	- Option 2:
		checkout the instructions on http://www.ros.org/wiki/camera_calibration
		Note: I always input the size of the squares of the pattern in meters
	- Second step: I usually use between 70-90 images to calibrate the camera. Then click "save" so that the calibration images are stored in the /tmp directory. If you click "commit" the application will close, before doing that you can point the camera to the pattern again to judge the quality of the calibration. Then click commit so that the ROS camera calibration file is saved on ~/.ros/camera_info . Recover both things and store them. Note that it is advisable to change the name of your ardrone, so that you can easily identify it afterwards.

Then, if you want, you can use the same imageset to calibrate the camera on OpenCV. I like to do this because I know that the parameter that the calibration returns is the average reprojection error of the patterns on the image after calibration. Do the following:

	Utilized software repositories:
	  - Mono-camera calibration -> OpenCV examples: 
	      - /usr/share/doc/opencv-doc/examples/cpp/calibration.cpp
	      - /usr/share/doc/opencv-doc/examples/cpp/imagelist_creator.cpp

	1. Calibration of monocular camera:
	repository: git clone https://jespestana@bitbucket.org/jespestana/asu_2013-volcanic_plume-mono_camera_calib.git
		- Go to:	~/Documents/workspace/mono_calib/bin
		- Run:		./image_list_creator image_list_ardrone2_jpp_set01.xml ../image_sets/ardrone2_jpp/set_01/*
		- Run:		./image_list_creator image_list_ardrone2_jpp_set02.xml ../image_sets/ardrone2_jpp/set_02/*
		- Run:		./calibration  -w 11 -h 7 -s 0.0182563 -o ardrone2_jpp_set01.yml image_list_ardrone2_jpp_set01.xml
	RMS error reported by calibrateCamera: 1.14419
	Calibration succeeded. avg reprojection error = 1.14
		- Run:		./calibration  -w 11 -h 7 -s 0.0182563 -o ardrone2_jpp_set02.yml image_list_ardrone2_jpp_set02.xml 
	RMS error reported by calibrateCamera: 0.69723
	Calibration succeeded. avg reprojection error = 0.70
	"ardrone2_jpp_set02.yml" contains the best set of parameters for this case.


