%% take-off and sleep
clear all
close all
clc

base_path = '/home/jespestana/workspace/ros/quadrotor/stack/configs/Mission_10/';

% points_information(point_number, [param])
% param: name |    x   |    y   |    z   |
points_information = ...
    {{   'D1' ,   2.50 ,   0.00 ,   1.33 };
     {   'D2' ,   2.50 ,  12.50 ,   1.33 };
     {   'D3' ,  10.00 ,  12.50 ,   1.33 };
     {   'D4' ,  16.50 ,  12.50 ,   1.33 };
     {   'D5' ,   2.50 ,   5.00 ,   1.33 };
     {   'D6' ,   7.50 ,   6.00 ,   1.33 };
     {   'D1F',   1.50 ,  12.00 ,   1.33 };
     {   'D2F',   4.50 ,  12.00 ,   1.33 };
     {   'D3F',   7.50 ,  12.00 ,   1.33 };
     {   'D4F',   1.50 ,  18.00 ,   1.33 };
	 {   'D5F',   4.50 ,  18.00 ,   1.33 };
	 {   'D6F',   7.50 ,  18.00 ,   1.33 };
     {   'T1' ,   4.50 ,  12.00 ,   1.33 };
     {'JUST_LOOK',  '' ,   ''   ,   1.33 };
%      {   'T2' ,   3.00 ,   9.00 ,   1.33 };
%      {   'T3' ,   3.00 ,   9.00 ,   1.33 };
                                         };
point_names = cellfun(@(x) x{1}, points_information, 'UniformOutput', false);

% drone_take_off_site(drone_number, [param])
% param: x   |    y   |    z   |  yaw   | pitch  |  roll  |
drone_take_off_site = ...
    [  0.00  ,  0.00  ,  1.00  ,  0.00  ,  0.00  ,  0.00  ;
       0.00  ,  0.00  ,  1.00  ,  0.00  ,  0.00  ,  0.00  ;
       0.00  ,  0.00  ,  1.00  ,  0.00  ,  0.00  ,  0.00  ;
       0.00  ,  6.00  ,  1.00  ,  0.00  ,  0.00  ,  0.00  ;
       0.00  ,  6.00  ,  1.00  ,  0.00  ,  0.00  ,  0.00  ;
       7.50  ,  6.00  ,  1.00  ,  0.00  ,  0.00  ,  0.00  ];
   
% columns_information(column_number, [param])
% param: name |    x   |    y   | 1st_aruco_id | 1st_aruco_yaw | radius   |
columns_information = ...
    {{   'C1' ,  11.00 ,   5.0  ,            9 ,     -90.0     ,   0.15   };
     {   'C2' ,  11.00 ,   5.0  ,           13 ,     -90.0     ,   0.15   };
     {   'C3' ,  11.00 ,   5.0  ,           17 ,     -90.0     ,   0.15   };
     {   'C4' ,  11.00 ,   5.0  ,           21 ,     -90.0     ,   0.15   };
     {   'C5' ,  11.00 ,   5.0  ,           25 ,     -90.0     ,   0.15   };
     {   'C6' ,  11.00 ,   5.0  ,           29 ,     -90.0     ,   0.15   };
     {   'C7' ,  11.00 ,   5.0  ,           41 ,     -90.0     ,   0.20   };
     {   'C8' ,  11.00 ,   5.0  ,           45 ,     -90.0     ,   0.20   };
     {   'C9' ,  11.00 ,   5.0  ,           49 ,     -90.0     ,   0.20   };
     {  'C10' ,  11.00 ,   5.0  ,           53 ,     -90.0     ,   0.20   };
%      {  'C11' ,   1.60 ,   9.0  ,           57 ,     -90.0     ,   0.20   };
%      {  'C12' ,   1.60 ,   9.0  ,           61 ,     -90.0     ,   0.20   };
                                                                          };
column_names = cellfun(@(x) x{1}, columns_information, 'UniformOutput', false);

missionGeneratorScript