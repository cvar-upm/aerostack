disp('*** missionGeneratorScript ***')

for drone_number=1:size(drone_take_off_site,1)
    mkdir([base_path,'drone',num2str(drone_number),'/']);
    copyfile([base_path,'drone_base/*'],[base_path,'drone',num2str(drone_number),'/']);
    
    params_read  = fopen([base_path,'drone_base/params_localization_obs.xml'],'r');
    params_write = fopen([base_path,'drone',num2str(drone_number),'/params_localization_obs.xml'],'w+');
    
    params_config_file_name = [base_path,'drone_base/params_localization_obs.xml'];
    line_params_arucos_location_begin = searchLineNumWhereStringIsInFile( params_config_file_name, '<Arucos>');
    line_params_arucos_location_end   = searchLineNumWhereStringIsInFile( params_config_file_name, '</Arucos>');
    line_params_obstacles_list_begin  = searchLineNumWhereStringIsInFile( params_config_file_name, '<obstaclesInMap>');
    line_params_obstacles_list_end    = searchLineNumWhereStringIsInFile( params_config_file_name, '</obstaclesInMap>');
    
    while ~feof(params_read)
        line = fgets(params_read);
        
        aux_x_0 = regexpi(line,'<x_0>');
        aux_y_0 = regexpi(line,'<y_0>');
        aux_z_0 = regexpi(line,'<z_0>');
        aux_yaw = regexpi(line,'<yaw_0>');
        aux_pitch=regexpi(line,'<pitch_0>');
        aux_roll =regexpi(line,'<roll_0>');
        aux_Arucos = regexpi(line,'<Arucos>');
        aux_obstaclesInMap = regexpi(line,'<obstaclesInMap>');
        if ( isempty(aux_x_0) && isempty(aux_y_0) && isempty(aux_z_0) && ...
             isempty(aux_yaw) && isempty(aux_yaw) && isempty(aux_roll) && ...
             isempty(aux_Arucos) && isempty(aux_obstaclesInMap) )
            fprintf(params_write, '%s', line);
        else
            if (~isempty(aux_x_0))
                fprintf(params_write, '\t%s\n', ['<x_0>',num2str(drone_take_off_site(drone_number,1)),'</x_0>']);
            end
            if (~isempty(aux_y_0))
                fprintf(params_write, '\t%s\n', ['<y_0>',num2str(drone_take_off_site(drone_number,2)),'</y_0>']);
            end
            if (~isempty(aux_z_0))
                fprintf(params_write, '\t%s\n', ['<z_0>',num2str(drone_take_off_site(drone_number,3)),'</z_0>']);
            end
            if (~isempty(aux_yaw))
                fprintf(params_write, '\t%s\n', ['<yaw_0>',  num2str(drone_take_off_site(drone_number,4)),'</yaw_0>']);
            end
            if (~isempty(aux_pitch))
                fprintf(params_write, '\t%s\n', ['<pitch_0>',num2str(drone_take_off_site(drone_number,5)),'</pitch_0>']);
            end
            if (~isempty(aux_roll))
                fprintf(params_write, '\t%s\n', ['<roll_0>', num2str(drone_take_off_site(drone_number,6)),'</roll_0>']);
            end
            if ( ~isempty(aux_Arucos) )
                fprintf(params_write, '\t<Arucos>\n');
                fprintf(params_write, '\t<!-- Angles are given in degrees!! -->\n\n');
                for i=1:length(columns_information)
                    fprintf(params_write, '\t\t\t<!-- %s -->\n', column_names{i});
                    center_x       = columns_information{i}{2};
                    center_y       = columns_information{i}{3};
                    first_aruco_id = columns_information{i}{4};
                    first_aruco_yaw= columns_information{i}{5};
                    radius         = columns_information{i}{6};
                    str_out = columnInformationGenerator( center_x, center_y, first_aruco_id, first_aruco_yaw, radius);
                    str_out = sprintf(str_out);
                    fprintf(params_write, '%s\n', str_out);
                end
                fprintf(params_write, '\t</Arucos>\n');
                for i=1:(line_params_arucos_location_end{1} - line_params_arucos_location_begin{1})
                    line = fgets(params_read);
                end
            end
            if ( ~isempty(aux_obstaclesInMap) )
                fprintf(params_write, '\t<obstaclesInMap>\n');
                fprintf(params_write, '\t\t<!-- POLES -->\n\n');
                id = 40000;
                for i=1:length(columns_information)
                    fprintf(params_write, '\t\t<pole description="%s">\n', column_names{i});
                    fprintf(params_write, '\t\t\t<id>%d</id>\n', id);
                    radius = columns_information{i}{6};
                    first_aruco_id = columns_information{i}{4};
                    fprintf(params_write, '\t\t\t<radius>%f %f</radius>\n', radius, radius);
                    fprintf(params_write, '\t\t\t<aruco>\n');
                    fprintf(params_write, '\t\t\t<id aruco_id = "%d"/>\n', first_aruco_id);
                    fprintf(params_write, '\t\t\t<id aruco_id = "%d"/>\n', first_aruco_id+1);
                    fprintf(params_write, '\t\t\t<id aruco_id = "%d"/>\n', first_aruco_id+2);
                    fprintf(params_write, '\t\t\t<id aruco_id = "%d"/>\n', first_aruco_id+3);
                    fprintf(params_write, '\t\t\t</aruco>\n');
                    fprintf(params_write, '\t\t</pole>\n\n');
                    id = id+1;
                end
                fprintf(params_write, '\t</obstaclesInMap>\n');
                for i=1:(line_params_obstacles_list_end{1}  - line_params_obstacles_list_begin{1})
                    line = fgets(params_read);
                end
            end
        end
        
        
    end
    
    fclose(params_read);
    fclose(params_write);
    
    ekf_read  = fopen([base_path,'drone_base/ekf_state_estimator_config.xml'],'r');
    ekf_write = fopen([base_path,'drone',num2str(drone_number),'/ekf_state_estimator_config.xml'],'w+');
    
    ekf_config_file_name = [base_path,'drone_base/ekf_state_estimator_config.xml'];
    line_ekf_take_off_site_begin = searchLineNumWhereStringIsInFile( ekf_config_file_name, '<take_off_site>');
    line_ekf_take_off_site_end   = searchLineNumWhereStringIsInFile( ekf_config_file_name, '</take_off_site>');
    
    while ~feof(ekf_read)
        line = fgets(ekf_read);
        
        aux_take_off_site = regexpi(line,'<take_off_site>');
        if ( isempty(aux_take_off_site) )
            fprintf(ekf_write, '%s', line);
        else
            take_off_site_str = ...
                ['<take_off_site> <!-- Frame_{drone_GMR_t=0} with respect to Frame_{GFF} -->\n', ... 
                 '\t<position> <!-- units: m -->\n', ... 
                 '\t\t<x>', num2str(drone_take_off_site(drone_number,1)),'</x>\n', ... 
                 '\t\t<y>', num2str(drone_take_off_site(drone_number,2)),'</y>\n', ... 
                 '\t\t<z>', num2str(drone_take_off_site(drone_number,3)),'</z>\n', ... 
                 '\t</position>\n', ... 
                 '\t<attitude> <!-- units: deg, wYvPuR -->\n', ... 
                 '\t\t<yaw>', num2str(  drone_take_off_site(drone_number,4)),'</yaw>\n', ... 
                 '\t\t<pitch>', num2str(drone_take_off_site(drone_number,5)),'</pitch>\n', ... 
                 '\t\t<roll>', num2str( drone_take_off_site(drone_number,6)),'</roll>\n', ... 
                 '\t</attitude>\n', ... 
                 '</take_off_site>\n'];
             fprintf(ekf_write, take_off_site_str);
             for i=1:(line_ekf_take_off_site_end{1} - line_ekf_take_off_site_begin{1})
                 line = fgets(ekf_read);
             end
        end
    end
    
    fclose(ekf_read);
    fclose(ekf_write);
    
    run([base_path,'mission_definitions_matlab/','mission_drone',num2str(drone_number),'.m']);
    mission_write = fopen([base_path,'drone',num2str(drone_number),'/configMission.xml'],'w+');
    fprintf(mission_write, '%s', mission_str);
    fclose(mission_write);
end