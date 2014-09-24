function [ mission_text ] = go_to_point_yaw( id_num, point_to_go_point_name, target_x, target_y, target_z, target_yaw)
%GO_TO_POINT_YAW Summary of this function goes here
%   Detailed explanation goes here

mission_text = ...
    	['\t\t<task description="id:', num2str(id_num),' Move to point ', point_to_go_point_name, ' looking at yaw ', num2str(target_yaw),'">\n', ... 
			'\t\t\t<config>\n', ... 
				'\t\t\t\t<id>',num2str(id_num),'</id>\n', ... 
			'\t\t\t</config>\n', ... 
			'\t\t\t<command>move</command>\n'];
        
        if ( isnumeric(target_x) || isnumeric(target_y) || isnumeric(target_z))
            mission_text = [ mission_text, ...
                '\t\t\t<point> <!-- point ', point_to_go_point_name,' -->\n'];
            if ( isnumeric(target_x) )
                mission_text = [ mission_text, '\t\t\t\t<x>',num2str(target_x),'</x>\n'];
            end
            if ( isnumeric(target_y) )
                mission_text = [ mission_text, '\t\t\t\t<y>',num2str(target_y),'</y>\n'];
            end
            if ( isnumeric(target_z) )
                mission_text = [ mission_text, '\t\t\t\t<z>',num2str(target_z),'</z>\n'];
            end
            mission_text = [ mission_text, ...
                '\t\t\t</point>\n'];
        end
        
        mission_text = [ mission_text, ...
			'\t\t\t<yaw>',num2str(target_yaw),'</yaw>\n', ... 
		'\t\t</task>\n'];

end

