clear all:
close all;
clc;

mission_text = cell(0);

% mission_opening( mission_name, prec_x, prec_y, prec_z, prec_yaw)
mission_text{end+1} = mission_opening( 'Mission 1', 0.2, 0.2, 0.2, 10.0);

% take_off_hover_yaw( id_num, sleep_time, z_init, yaw_init)
mission_text{end+1} = take_off_hover_yaw( 1, 3.0, 1.00, 90);
% % take_off_hover_look_to( id_num, sleep_time, z_init, point_to_look_num_column, point_to_look_x, point_to_look_y)
% mission_text{end+1} = take_off_hover_look_to( 1, 3.0, 1.00, 3, 3.6, 9.0);

% submission_opening( description_str, id_num, bool_loop, time_loop)
% submission_ending()
mission_text{end+1} = submission_opening('02 - navigation', 2,  0, 120.0);
% go_to_point_yaw( id_num, point_to_go_point_name, target_x, target_y, target_z, target_yaw)
mission_text{end+1} = go_to_point_yaw( 1, '1a', 1.0, 2.0, 1.33, 90.0);
% go_to_point_look_to( id_num, point_to_go_point_name, target_x, target_y, target_z, point_to_look_column_name, point_to_look_x, point_to_look_y)
mission_text{end+1} = go_to_point_look_to( 2, '2a', 5.0, 2.0, 1.33, '3', 3.6, 9.0);
mission_text{end+1} = go_to_point_yaw( 1, '1a', '', '', 3, 120.0);
mission_text{end+1} = submission_ending();

% submission_opening( description_str, id_num, bool_loop, time_loop)
% submission_ending()
mission_text{end+1} = submission_opening('03 - navigation', 3,  0, 120.0);
% go_to_point_yaw( id_num, point_to_go_point_name, target_x, target_y, target_z, target_yaw)
mission_text{end+1} = go_to_point_yaw( 1, '1a', 1.0, 2.0, 1.33, 90.0);
% go_to_point_look_to( id_num, point_to_go_point_name, target_x, target_y, target_z, point_to_look_column_name, point_to_look_x, point_to_look_y)
mission_text{end+1} = go_to_point_look_to( 2, '2a', 5.0, 2.0, 1.33, '3', 3.6, 9.0);
mission_text{end+1} = go_to_point_yaw( 1, '1a', '', '', 3, 120.0);
mission_text{end+1} = submission_ending();

% land_submission( id_num, sleep_time)
mission_text{end+1} = land_submission( 4, 3.0);

% mission_ending()
mission_text{end+1} = mission_ending();

str = '';
for i=1:length(mission_text)    
    str = strcat(str,mission_text{i});
end

disp(sprintf(str));