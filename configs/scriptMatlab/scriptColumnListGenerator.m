%Script to put Visual Marks in the map
%In Columns


close all
clear all
clc

file_name = '/home/jespestana/workspace/ros/quadrotor/stack/configs/Mission_11/drone_base/params_localization_obs.xml';
lines_number_cell_1 = searchLineNumWhereStringIsInFile( file_name, '<Arucos>')
lines_number_cell_2 = searchLineNumWhereStringIsInFile( file_name, '</Arucos>')

file_name = '/home/jespestana/workspace/ros/quadrotor/stack/configs/Mission_11/drone_base/ekf_state_estimator_config.xml';
lines_number_cell_1 = searchLineNumWhereStringIsInFile( file_name, '<take_off_site>')
lines_number_cell_2 = searchLineNumWhereStringIsInFile( file_name, '</take_off_site>')



%%


%Center of the column
centerColumn=[4.50; 15.00];
radiusColumn=[0.20;  0.20];

%Altitude
altitude=1.33;

%roll y pitch
roll=0;
pitch=0;

%VisualMarksNum
if(0)
    VisualMarksNum={17,18,19,20};
else
    initVisualMark=61;
    VisualMarksNum=cell(4,1);
    for(i=0:3)
        VisualMarksNum{i+1,1}=initVisualMark+i;
    end
end

%Option:
option=1; %First yaw=-90;

poseVisualMarks=cell(4,1);

switch(option)
    case 1
        poseVisualMarks{1}=[centerColumn(1);centerColumn(2)-radiusColumn(2);altitude;roll;pitch;-90.0];
        poseVisualMarks{2}=[centerColumn(1)-radiusColumn(1);centerColumn(2);altitude;roll;pitch;180.0];
        poseVisualMarks{3}=[centerColumn(1);centerColumn(2)+radiusColumn(2);altitude;roll;pitch;90.0];
        poseVisualMarks{4}=[centerColumn(1)+radiusColumn(1);centerColumn(2);altitude;roll;pitch;0.0];    
end;

stringTot=cell(4,1);

for(i=1:4)
    
    stringTot{i,1}=[  '<Aruco id="',num2str(VisualMarksNum{i}),'"',' x="',num2str(poseVisualMarks{i,1}(1)),'"',' y="',num2str(poseVisualMarks{i,1}(2)),'"',' z="',num2str(poseVisualMarks{i,1}(3)),'"',' roll="',num2str(poseVisualMarks{i,1}(4)),'"',' pitch="',num2str(poseVisualMarks{i,1}(5)),'"',' yaw="',num2str(poseVisualMarks{i,1}(6)),'"','/>' ];
    
    disp(stringTot{i,1})
    %outToXML=strcat(outToXML,stringTot{i,1},sprintf('\n'));
end
