function [ mission_text ] = go_to_point_yaw_simp( id_num, point_to_go_point_name, target_yaw, points_information, point_names )
%GO_TO_POINT_YAW_SIMP Summary of this function goes here
%   Detailed explanation goes here

index = find(cell2mat(cellfun(@(x) strcmp(x, point_to_go_point_name), point_names, 'UniformOutput', false)));
target_x = points_information{index}{2};
target_y = points_information{index}{3};
target_z = points_information{index}{4};

mission_text = go_to_point_yaw( id_num, point_to_go_point_name, target_x, target_y, target_z, target_yaw);

end

