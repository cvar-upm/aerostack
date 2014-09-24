%% take-off and sleep
clear all
close all
clc

base_path = '/home/jespestana/workspace/ros/quadrotor/stack/configs/Mission_10/';

% drone take off site
% A(drone_number, [param])
% param: x   |    y   |    z   |  yaw   | pitch  |  roll  |
A = [  1.50  ,  0.00  ,  1.00  , 90.00  ,  0.00  ,  0.00  ;
       4.50  ,  0.00  ,  1.00  , 90.00  ,  0.00  ,  0.00  ;
       7.50  ,  0.00  ,  1.00  , 90.00  ,  0.00  ,  0.00  ;
       2.25  ,  6.00  ,  1.00  , 90.00  ,  0.00  ,  0.00  ;
       4.50  ,  6.00  ,  1.00  , 90.00  ,  0.00  ,  0.00  ;
       7.50  ,  6.00  ,  1.00  , 90.00  ,  0.00  ,  0.00  ];

for drone_number=1:size(A,1)
    mkdir([base_path,'drone',num2str(drone_number),'/']);
    copyfile([base_path,'drone_base/*'],[base_path,'drone',num2str(drone_number),'/']);
    
    params_read  = fopen([base_path,'drone_base/params_localization_obs.xml'],'r');
    params_write = fopen([base_path,'drone',num2str(drone_number),'/params_localization_obs.xml'],'w+');
    
    while ~feof(params_read)
        line = fgets(params_read);
        
        aux_x_0 = regexpi(line,'<x_0>');
        aux_y_0 = regexpi(line,'<y_0>');
        aux_z_0 = regexpi(line,'<z_0>');
        aux_yaw = regexpi(line,'<yaw_0>');
        aux_pitch=regexpi(line,'<pitch_0>');
        aux_roll =regexpi(line,'<roll_0>');
        if ( isempty(aux_x_0) && isempty(aux_y_0) && isempty(aux_z_0) && ...
                isempty(aux_yaw) && isempty(aux_yaw) && isempty(aux_roll) )
            fprintf(params_write, '%s', line);
        else
            if (~isempty(aux_x_0))
                fprintf(params_write, '\t%s\n', ['<x_0>',num2str(A(drone_number,1)),'</x_0>']);
            end
            if (~isempty(aux_y_0))
                fprintf(params_write, '\t%s\n', ['<y_0>',num2str(A(drone_number,2)),'</y_0>']);
            end
            if (~isempty(aux_z_0))
                fprintf(params_write, '\t%s\n', ['<z_0>',num2str(A(drone_number,3)),'</z_0>']);
            end
            if (~isempty(aux_yaw))
                fprintf(params_write, '\t%s\n', ['<yaw_0>',  num2str(A(drone_number,4)),'</yaw_0>']);
            end
            if (~isempty(aux_pitch))
                fprintf(params_write, '\t%s\n', ['<pitch_0>',num2str(A(drone_number,5)),'</pitch_0>']);
            end
            if (~isempty(aux_roll))
                fprintf(params_write, '\t%s\n', ['<roll_0>', num2str(A(drone_number,6)),'</roll_0>']);
            end
        end
    end
    
    fclose(params_read);
    fclose(params_write);
    
    ekf_read  = fopen([base_path,'drone_base/ekf_state_estimator_config.xml'],'r');
    ekf_write = fopen([base_path,'drone',num2str(drone_number),'/ekf_state_estimator_config.xml'],'w+');
    
    while ~feof(ekf_read)
        line = fgets(ekf_read);
        
        aux_take_off_site = regexpi(line,'<take_off_site>');
        if ( isempty(aux_take_off_site) )
            fprintf(ekf_write, '%s', line);
        else
            take_off_site_str = ...
                ['<take_off_site> <!-- Frame_{drone_GMR_t=0} with respect to Frame_{GFF} -->\n', ... 
                 '\t<position> <!-- units: m -->\n', ... 
                 '\t\t<x>', num2str(A(drone_number,1)),'</x>\n', ... 
                 '\t\t<y>', num2str(A(drone_number,2)),'</y>\n', ... 
                 '\t\t<z>', num2str(A(drone_number,3)),'</z>\n', ... 
                 '\t</position>\n', ... 
                 '\t<attitude> <!-- units: deg, wYvPuR -->\n', ... 
                 '\t\t<yaw>', num2str(  A(drone_number,4)),'</yaw>\n', ... 
                 '\t\t<pitch>', num2str(A(drone_number,5)),'</pitch>\n', ... 
                 '\t\t<roll>', num2str( A(drone_number,6)),'</roll>\n', ... 
                 '\t</attitude>\n', ... 
                 '</take_off_site>\n'];
             fprintf(ekf_write, take_off_site_str);
             for i=1:11
                 line = fgets(ekf_read);
             end
        end
    end
    
    fclose(ekf_read);
    fclose(ekf_write);
end


% movefile('output_results\results.xml.TEMP', 'output_results\results.xml');
