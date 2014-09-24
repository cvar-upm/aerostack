function [ mission_text ] = take_off_hover_look_to_simp( id_num, sleep_time, z_init, point_to_look_column_name, columns_information, column_names)
%TAKE_OFF_HOVER_LOOK_TO_SIMP Summary of this function goes here
%   Detailed explanation goes here

index = find(cell2mat(cellfun(@(x) strcmp(x, point_to_look_column_name), column_names, 'UniformOutput', false)));
point_to_look_x = columns_information{index}{2};
point_to_look_y = columns_information{index}{3};

mission_text = take_off_hover_look_to( id_num, sleep_time, z_init, point_to_look_column_name, point_to_look_x, point_to_look_y);

end

