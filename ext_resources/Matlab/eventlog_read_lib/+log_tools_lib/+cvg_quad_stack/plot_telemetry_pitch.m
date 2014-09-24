function [h1, h2] = plot_telemetry_pitch( drone_data )
%PLOT_TELEMETRY_PITCH Summary of this function goes here
%   Detailed explanation goes here

myfig_LineStyle = {'-','--','-.',':'};
% Note: to understand the weird gains 2.52 and 2.37; check out MscJesus section: 5.6.2. Identification example: Parrot AR Drone

% Pitch 
myfig_filename = [myfig_filename_init,'Pitch'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'drone.rotation_angles.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'drone.rotation_angles.y','ctrlr.state.Pco*24.0'};%,'ctrlr.state.Pco*180.0/pi/2.52'};%,'ctrlr.state.Pco*180.0/pi'};
% myfig_legend     = {'telemetry','controller command'};
% myfig_legendLocation = 'NorthWest';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'pitch [deg]';
myfig_legend     = '{''telemetry'',''controller command''}';
myfig_legendLocation = 'NorthWest';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''pitch, $\theta$ [deg]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'

myfig_jespestana

end

