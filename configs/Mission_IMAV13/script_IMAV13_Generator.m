%% take-off and sleep
clear all
close all
clc

base_path = '/home/jespestana/workspace/ros/quadrotor/stack/configs/Mission_IMAV13/';

disp('*** missionGeneratorScript ***')
for drone_number=1:8
    mkdir([base_path,'drone',num2str(drone_number),'/']);
    copyfile([base_path,'drone_base/*'],[base_path,'drone',num2str(drone_number),'/']);
end
