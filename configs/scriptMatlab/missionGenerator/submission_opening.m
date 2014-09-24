function [ mission_text ] = submission_opening( description_str, id_num, bool_loop, time_loop)
%SUBMISSION_OPENING Summary of this function goes here
%   Detailed explanation goes here

mission_text = ...
    	['\t<submission description="', description_str, '">\n', ... 
		'\t\t<config>\n', ... 
			'\t\t\t<id>',num2str(id_num),'</id>\n']; 
            
        if (bool_loop)
            mission_text = [ mission_text, ...
                '\t\t\t<loop>1</loop>\n', ... 
			    '\t\t\t<time>',num2str(time_loop),'</time>\n'];
        else
            mission_text = [ mission_text, ...
                '\t\t\t<loop>0</loop>\n'];
        end
		mission_text = [ mission_text,'\t\t</config>\n'];

end

