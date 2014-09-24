% %% read data from logfile and put into the data structure
% help eventlog_readdata
close all, clear all, clc;

cd('/home/jespestana/workspace/ros/quadrotor/stack/ext_resources/Matlab/eventlog_read_lib')

% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_20.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_21.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_22.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_23.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_24.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_25.txt');

% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_26.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_27.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_28.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_29.txt');

% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_30.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_31.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_32.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_33.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_35.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_36.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_37.txt');

% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_50.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_51.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_52.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_53.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_54.txt');
% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_55.txt');

% drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_70.txt');
drone0 = log_tools_lib.eventlog_readdata('/home/jespestana/events_log_71.txt');

%%

close all
clc

% hist(diff(drone0.camera.back.time))
% scatter(drone0.camera.left.time)

figure
hist(diff(drone0.camera.front.time),100)
title('front, BUS3, USB 2.0')
figure
scatter(1:length(drone0.camera.front.time),drone0.camera.front.time,'.')
title('front, BUS3, USB 2.0')

figure
hist(diff(drone0.camera.bottom.time),100)
title('bottom, HUB, USB 3.0')
figure
scatter(1:length(drone0.camera.bottom.time),drone0.camera.bottom.time,'.')
title('bottom, HUB, USB 3.0')

figure
hist(diff(drone0.camera.right.time),100)
title('right, HUB, USB 2.0')
figure
scatter(1:length(drone0.camera.right.time),drone0.camera.right.time,'.')
title('right, HUB, USB 2.0')


figure
hist(diff(drone0.camera.left.time),100)
title('left, HUB, USB 2.0')
figure
scatter(1:length(drone0.camera.left.time),drone0.camera.left.time,'.')
title('left, HUB, USB 2.0')

figure
hist(diff(drone0.camera.back.time),100)
title('back, BUS3, USB 2.0')
figure
scatter(1:length(drone0.camera.back.time),drone0.camera.back.time,'.')
title('back, BUS3, USB 2.0')

disp(['back:   HUB2 mean: ', num2str( mean(diff(drone0.camera.back.time))   ,'%7.4f\n'), ' std: ', num2str( std(diff(drone0.camera.back.time)),'%7.4f\n')])
disp(['front:  HUB2 mean: ', num2str( mean(diff(drone0.camera.front.time))  ,'%7.4f\n'), ' std: ', num2str( std(diff(drone0.camera.front.time)),'%7.4f\n')])
disp(['bottom: USB3 mean: ', num2str( mean(diff(drone0.camera.bottom.time)) ,'%7.4f\n'), ' std: ', num2str( std(diff(drone0.camera.bottom.time)),'%7.4f\n')])
disp(['left:   BUS3 mean: ', num2str( mean(diff(drone0.camera.left.time))   ,'%7.4f\n'), ' std: ', num2str( std(diff(drone0.camera.left.time)),'%7.4f\n')])
disp(['right:  BUS3 mean: ', num2str( mean(diff(drone0.camera.right.time))  ,'%7.4f\n'), ' std: ', num2str( std(diff(drone0.camera.right.time)),'%7.4f\n')])

% figure
% hist(diff(drone0.drone.ground_speed.time),100)
% title('opt-flow')
% figure
% scatter(1:length(drone0.drone.ground_speed.time),drone0.drone.ground_speed.time,'.')
% title('opt-flow')
% disp(['right:  BUS3 mean: ', num2str( mean(diff(drone0.drone.ground_speed.time))  ,'%7.4f\n'), ' std: ', num2str( std(diff(drone0.drone.ground_speed.time)),'%7.4f\n')])