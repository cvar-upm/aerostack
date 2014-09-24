mission_text = cell(0);

% % mission_opening( mission_name, prec_x, prec_y, prec_z, prec_yaw)
mission_text{end+1} = mission_opening( 'Mission 1', 0.2, 0.2, 0.2, 10.0);

% % take_off_hover_yaw( id_num, sleep_time, z_init, yaw_init)
% mission_text{end+1} = take_off_hover_yaw( 1, 3.0, 1.00, 90);
% % take_off_hover_look_to( id_num, sleep_time, z_init, point_to_look_num_column, point_to_look_x, point_to_look_y)
% % take_off_hover_look_to_simp( id_num, sleep_time, z_init, point_to_look_column_name, columns_information, column_names)
mission_text{end+1} = take_off_hover_look_to_simp( 1, 3.0, 1.00, 'C1', columns_information, column_names);

% % submission_opening( description_str, id_num, bool_loop, time_loop)
% submission_ending()
% % go_to_point_yaw( id_num, point_to_go_point_name, target_x, target_y, target_z, target_yaw)
% % go_to_point_look_to( id_num, point_to_go_point_name, target_x, target_y, target_z, point_to_look_column_name, point_to_look_x, point_to_look_y)
% % go_to_point_yaw_simp( id_num, point_to_go_point_name, target_yaw, points_information, point_names )
% % go_to_point_look_to_simp( id_num, point_to_go_point_name, point_to_look_column_name, points_information, point_names, columns_information, column_names)
% mission_text{end+1} = go_to_point_yaw( 1, '1a', 1.0, 2.0, 1.33, 90.0);
% mission_text{end+1} = go_to_point_yaw( 1, '1a', '', '', 3, 120.0);
% mission_text{end+1} = go_to_point_look_to( 1, 'D4',  1.50,  6.0, 1.33, 'C7', 3.0, 3.0);
% mission_text{end+1} = go_to_point_look_to( 2, 'T1',  4.50, 10.0, 1.33, 'C3', 3.6, 9.0);
% mission_text{end+1} = go_to_point_look_to( 3, 'D1F', 1.50, 12.0, 1.33, 'C2', 2.6, 9.0);
N = 1;
k = 2;
mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(1, 'D1' , 'C1', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;

t_pre_aterrizaje =  2.0;
t_aterrizado     =  7.0;
for i=1:N
    
mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(2, 'D2' , 'C2', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;
% mission_text{end+1} = land_submission( k, t_pre_aterrizaje);
% k = k+1;
% mission_text{end+1} = sleep_time( k, t_aterrizado);
% k = k+1;
% mission_text{end+1} = take_off_hover_look_to_simp( k, 3.0, 1.00, 'C1', columns_information, column_names);
% k = k+1;

mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(1, 'D3' , 'C1', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;
mission_text{end+1} = land_submission( k, t_pre_aterrizaje);
k = k+1;
mission_text{end+1} = sleep_time( k, t_aterrizado);
k = k+1;
mission_text{end+1} = take_off_hover_look_to_simp( k, 3.0, 1.00, 'C1', columns_information, column_names);
k = k+1;

mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(1, 'D4' , 'C1', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;
mission_text{end+1} = land_submission( k, t_pre_aterrizaje);
k = k+1;
mission_text{end+1} = sleep_time( k, t_aterrizado);
k = k+1;
mission_text{end+1} = take_off_hover_look_to_simp( k, 3.0, 1.00, 'C1', columns_information, column_names);
k = k+1;

mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(1, 'D3' , 'C1', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;
% mission_text{end+1} = land_submission( k, t_pre_aterrizaje);
% k = k+1;
% mission_text{end+1} = sleep_time( k, t_aterrizado);
% k = k+1;
% mission_text{end+1} = take_off_hover_look_to_simp( k, 3.0, 1.00, 'C1', columns_information, column_names);
% k = k+1;
end;

mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(2, 'D2' , 'C2', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;
mission_text{end+1} = land_submission( k, t_pre_aterrizaje);
k = k+1;
mission_text{end+1} = sleep_time( k, t_aterrizado);
k = k+1;
mission_text{end+1} = take_off_hover_look_to_simp( k, 3.0, 1.00, 'C1', columns_information, column_names);
k = k+1;

mission_text{end+1} = submission_opening('02 - navigation', k,  0, '');
mission_text{end+1} = go_to_point_look_to_simp(2, 'D5' , 'C2', points_information, point_names, columns_information, column_names);
mission_text{end+1} = submission_ending();
k = k+1;

% land_submission( id_num, sleep_time)
mission_text{end+1} = land_submission( k, 5.0);
k = k+1;

% mission_ending()
mission_text{end+1} = mission_ending();

mission_str = '';
for i=1:length(mission_text)    
    mission_str = strcat(mission_str,mission_text{i});
end

mission_str = sprintf(mission_str);
% disp(mission_str);