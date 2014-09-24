function [ mission_text ] = go_to_point_look_to_simp( id_num, point_to_go_point_name, point_to_look_column_name, points_information, point_names, columns_information, column_names)
%GO_TO_POINT_LOOK_TO_SIMP Summary of this function goes here
%   Detailed explanation goes here

index = find(cell2mat(cellfun(@(x) strcmp(x, point_to_go_point_name), point_names, 'UniformOutput', false)));
target_x = points_information{index}{2};
target_y = points_information{index}{3};
target_z = points_information{index}{4};
index = find(cell2mat(cellfun(@(x) strcmp(x, point_to_look_column_name), column_names, 'UniformOutput', false)));
point_to_look_x = columns_information{index}{2};
point_to_look_y = columns_information{index}{3};

mission_text = go_to_point_look_to( id_num, point_to_go_point_name, target_x, target_y, target_z, point_to_look_column_name, point_to_look_x, point_to_look_y);

end

