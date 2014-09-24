function [ str_out ] = columnInformationGenerator( center_x, center_y, first_aruco_id, first_aruco_yaw, radius)
%COLUMNINFORMATIONGENERATOR Summary of this function goes here
%   Detailed explanation goes here

%Center of the column
centerColumn=[center_x; center_y];
radiusColumn=[radius;  radius];

%Altitude
altitude=1.33;

%roll y pitch
roll=0;
pitch=0;

%VisualMarksNum
if(0)
    VisualMarksNum={17,18,19,20};
else
    initVisualMark=first_aruco_id;
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
        yaw_1 = first_aruco_yaw;
        yaw_2 = yaw_1-90.0; yaw_2 = mod(yaw_2, 360); if (yaw_2>180) yaw_2 = -180+(yaw_2-180); end
        yaw_3 = yaw_2-90.0; yaw_3 = mod(yaw_3, 360); if (yaw_3>180) yaw_3 = -180+(yaw_2-180); end
        yaw_4 = yaw_3-90.0; yaw_4 = mod(yaw_4, 360); if (yaw_4>180) yaw_4 = -180+(yaw_2-180); end
        poseVisualMarks{1}=[centerColumn(1);centerColumn(2)-radiusColumn(2);altitude;roll;pitch;yaw_1];
        poseVisualMarks{2}=[centerColumn(1)-radiusColumn(1);centerColumn(2);altitude;roll;pitch;yaw_2];
        poseVisualMarks{3}=[centerColumn(1);centerColumn(2)+radiusColumn(2);altitude;roll;pitch;yaw_3];
        poseVisualMarks{4}=[centerColumn(1)+radiusColumn(1);centerColumn(2);altitude;roll;pitch;yaw_4];    
end;

str_out='';
for(i=1:4)
    str_out = [str_out,'\t\t\t<Aruco id="',num2str(VisualMarksNum{i}),'"',' x="',num2str(poseVisualMarks{i,1}(1)),'"',' y="',num2str(poseVisualMarks{i,1}(2)),'"',' z="',num2str(poseVisualMarks{i,1}(3)),'"',' roll="',num2str(poseVisualMarks{i,1}(4)),'"',' pitch="',num2str(poseVisualMarks{i,1}(5)),'"',' yaw="',num2str(poseVisualMarks{i,1}(6)),'"','/>\n' ];
end



end

