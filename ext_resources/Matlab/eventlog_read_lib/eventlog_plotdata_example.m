% %% read data from logfile and put into the data structure
% help eventlog_readdata
close all, clear all, clc;

cd('/home/jespestana/workspace/ros/quadrotor/stack/ext_resources/Matlab/eventlog_read_lib');

% % event log file to be read
% file_path = './example_data/events_log.txt';
% % time range to be graphed
% time_init = 97.30;
% time_end  = 125.41;
% % read logfile and store in drone0
% drone0 = eventlog_readdata( file_path, time_init, time_end);

%%  date_y2014m02d01:
% -------------------

% % vuelo 1
% drone1 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo1/drone1/time_15_11_30.933203/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo1/drone2/time_15_11_36.645247/events_log.txt');
% drone3 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo1/drone3/time_15_11_30.933203/events_log.txt');
% drone4 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo1/drone4/time_15_11_30.933203/events_log.txt');
% drone5 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo1/drone5/time_15_12_40.176262/events_log.txt');
% drone6 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo1/drone6/time_15_11_32.195779/events_log.txt');

% % vuelo 2
% drone1 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo2/drone1/time_15_21_46.117869/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo2/drone2/time_15_21_45.030536/events_log.txt');
% drone3 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo2/drone3/time_15_21_43.382463/events_log.txt');
% drone4 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo2/drone4/time_15_21_47.486369/events_log.txt');
% drone5 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo2/drone5/time_15_21_44.887338/events_log.txt');
% drone6 = log_tools_lib.eventlog_readdata('~/flight_logs/date_y2014m02d01/Vuelo2/drone6/time_15_21_44.266123/events_log.txt');

% myfig_filename_init = 'figures/2014Feb01/vuelo1/quad_swarm_';
% mkdir(                'figures')
% mkdir(                'figures/2014Feb01/')
% mkdir(                'figures/2014Feb01/vuelo1')

%% date_y2014m02d01:
% ------------------

% % mapa11c
% *********

% % vuelo 1
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_1/drone1/time_12_15_43.961921/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_1/drone3/time_12_15_43.326503/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_1/drone4/time_12_15_53.896208/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_1/drone5/time_12_15_48.227612/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_1/drone6/time_12_15_45.499906/events_log.txt');
save date_y2014m02d06_mapa11c_vuelo1.mat
clear all

% % vuelo 2
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_2/drone1/time_13_19_59.848830/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_2/drone3/time_13_21_23.335154/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_2/drone4/time_13_20_14.976735/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_2/drone5/time_13_19_57.289561/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_2/drone6/time_13_20_01.452998/events_log.txt');
save date_y2014m02d06_mapa11c_vuelo2.mat
clear all

% % vuelo 3
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_3/drone1/time_13_30_47.904507/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_3/drone3/time_13_33_38.694598/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_3/drone4/time_13_30_54.067016/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_3/drone5/time_13_30_48.720333/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_3/drone6/time_13_30_48.735324/events_log.txt');
save date_y2014m02d06_mapa11c_vuelo3.mat
clear all

% % vuelo 4
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_4/drone1/time_13_42_29.737910/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_4/drone3/time_13_42_30.380311/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_4/drone4/time_13_42_47.333606/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_4/drone5/time_13_42_50.010913/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_4/drone6/time_13_42_55.351804/events_log.txt');
save date_y2014m02d06_mapa11c_vuelo4.mat
clear all

% % vuelo 5
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_5/drone1/time_13_51_00.088956/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_5/drone3/time_13_50_58.729475/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_5/drone4/time_13_51_06.179699/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_5/drone5/time_13_51_00.568694/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa11c/vuelo_5/drone6/time_13_50_59.464975/events_log.txt');
save date_y2014m02d06_mapa11c_vuelo5.mat
clear all

% % mapa10b_a
% ***********

% % vuelo 1
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b_A/vuelo_1/drone1/time_15_55_32.474269/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b_A/vuelo_1/drone3/time_15_55_33.209850/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b_A/vuelo_1/drone4/time_15_55_35.088081/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b_A/vuelo_1/drone5/time_15_55_29.257842/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b_A/vuelo_1/drone6/time_15_55_32.288961/events_log.txt');
save date_y2014m02d06_mapa10ba_vuelo1.mat
clear all

% % mapa10b_a
% ***********

% % vuelo 1
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_1/drone1/time_16_21_27.336194/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_1/drone3/time_16_21_28.069313/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_1/drone4/time_16_21_33.981767/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_1/drone5/time_16_21_24.557584/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_1/drone6/time_16_21_27.304068/events_log.txt');
save date_y2014m02d06_mapa10b_vuelo1.mat
clear all

% % vuelo 2
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_2/drone1/time_16_33_48.843049/events_log.txt');
% drone2 = log_tools_lib.eventlog_readdata('');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_2/drone3/time_16_33_49.174678/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_2/drone4/time_16_33_57.335107/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_2/drone5/time_16_33_40.726824/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/date_y2014m02d06/vuelos_mapa10b/vuelo_2/drone6/time_16_33_43.964061/events_log.txt');
save date_y2014m02d06_mapa10b_vuelo2.mat
clear all

myfig_filename_init = 'figures/2014Feb01/vuelo1/quad_swarm_';
mkdir(                'figures')
mkdir(                'figures/2014Feb01/')
mkdir(                'figures/2014Feb01/vuelo1')

%% Simulaciones del IMAV2013

% % simulacion 1
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion1/drone1/time_19_31_06.390408/events_log.txt');
drone2 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion1/drone2/time_19_30_53.184956/events_log.txt');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion1/drone3/time_19_30_54.212792/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion1/drone4/time_19_30_54.511441/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion1/drone5/time_19_30_48.100905/events_log.txt');
% drone6 = log_tools_lib.eventlog_readdata('');
save date_y2014m02d14_mapaIMAV2013_sim1.mat
clear all

% % % simulacion 2
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion2/drone1/time_20_57_00.625638/events_log.txt');
drone2 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion2/drone2/time_20_56_47.913661/events_log.txt');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion2/drone3/time_20_56_49.122301/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion2/drone4/time_20_56_46.809040/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion2/drone5/time_20_56_36.080876/events_log.txt');
% drone6 = log_tools_lib.eventlog_readdata('');
save date_y2014m02d14_mapaIMAV2013_sim2.mat
clear all

% % simulacion 3
drone1 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion3/drone1/time_21_09_19.264322/events_log.txt');
drone2 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion3/drone2/time_21_09_17.092953/events_log.txt');
drone3 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion3/drone3/time_21_09_18.023535/events_log.txt');
drone4 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion3/drone4/time_21_09_20.984708/events_log.txt');
drone5 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion3/drone5/time_21_09_04.019183/events_log.txt');
drone6 = log_tools_lib.eventlog_readdata('/home/jespestana/flight_logs/simulaciones_date_y2014m02d14/mapaIMAV13/simulacion3/drone6/time_21_09_18.690163/events_log.txt');
save date_y2014m02d14_mapaIMAV2013_sim3.mat
clear all

myfig_filename_init = 'figures/2014Feb14/vuelo1/quad_swarm_';
mkdir(                'figures')
mkdir(                'figures/2014Feb14/')
mkdir(                'figures/2014Feb14/vuelo1')



%% Graph drone trajectories
clc
close all

% load date_y2014m02d01_vuelo1.mat;
% load date_y2014m02d01_vuelo2.mat;

% load date_y2014m02d06_mapa11c_vuelo1.mat
% load date_y2014m02d06_mapa11c_vuelo2.mat
% load date_y2014m02d06_mapa11c_vuelo3.mat
% load date_y2014m02d06_mapa11c_vuelo4.mat
% load date_y2014m02d06_mapa11c_vuelo5.mat
% load date_y2014m02d06_mapa10ba_vuelo1.mat
% load date_y2014m02d06_mapa10b_vuelo1.mat
% load date_y2014m02d06_mapa10b_vuelo2.mat
load date_y2014m02d14_mapaIMAV2013_sim1.mat
% load date_y2014m02d14_mapaIMAV2013_sim2.mat
% load date_y2014m02d14_mapaIMAV2013_sim3.mat

%%
close all
mkdir('figures')

h1 = log_tools_lib.figure( 8.5, 14.875);
config = log_tools_lib.default_configuration();
config.adjust_plot_limits_to_data = false;
% log_tools_lib.cvg_quad_stack.plot_drone_trajectory( h1, config, 7000.0, Inf, drone0);
% log_tools_lib.cvg_quad_stack.plot_drone_trajectory( h1, config, 6110.0, Inf, drone1, drone2, drone3, drone4, drone5, drone6);
% log_tools_lib.cvg_quad_stack.plot_drone_trajectory( h1, config, 500000, Inf, drone1, drone3, drone4, drone5, drone6);
log_tools_lib.cvg_quad_stack.plot_drone_trajectory( h1, config, 500000, Inf, drone1, drone2, drone3, drone4, drone5);
% log_tools_lib.cvg_quad_stack.plot_drone_trajectory( h1, config, 6110.0, Inf, drone2, drone3, drone4, drone5, drone6); // vuelo1
% axis equal
xmin = -1.0;
xmax =  9.0;
ymin = -3.5;
ymax = 14.0;
axis([xmin xmax ymin ymax])
% h_legend = legend('drone1', 'drone2', 'drone3', 'drone4', 'drone5', 'drone6', 'Location', 'SouthEast');
h_legend = legend('drone1', 'drone2', 'drone3', 'drone4', 'drone5', 'Location', 'SouthEast');
set(h_legend,'FontSize', 10);
% set(h_legend, 'box', 'off') 

% lh = legend('1', '2', '3', '4', '5', 'Location', 'SouthEast');
% set(lh,'units','pixels');
% lp=get(lh,'outerposition');
% set(lh,'FontSize',12);
% set(lh,'outerposition',[lp(1:2), 50, 100]);
log_tools_lib.save_figure(h1,'figures/date_y2014m02d14_mapaIMAV2013_sim3')

%% Graphs - controller commands vs telemetry
close all
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

% Pitch 
myfig_filename = [myfig_filename_init,'PitchDelayCheck'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'drone.command.PR.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'drone.command.PR.pitchCmd','ctrlr.state.Pco'};%,'ctrlr.state.Pco*180.0/pi/2.52'};%,'ctrlr.state.Pco*180.0/pi'};
% myfig_legend     = {'telemetry','controller command'};
% myfig_legendLocation = 'NorthWest';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'pitch [deg]';
myfig_legend     = '{''telemetry'',''controller command''}';
myfig_legendLocation = 'NorthWest';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''pitch, $\theta$ [1/1]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'

myfig_jespestana

%%

% Roll
myfig_filename = [myfig_filename_init,'Roll'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ardrone.state.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'ardrone.state.roll','ctrlr.state.Rco*24.0'};%,'ctrlr.state.Rco*180.0/pi/2.37'};%,'ctrlr.state.Rco*180.0/pi'};
% myfig_legend     = {'telemetry','controller command'};
% myfig_legendLocation = 'NorthWest';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'roll [deg]';
myfig_legend     = '{''telemetry'',''controller command''}';
myfig_legendLocation = 'NorthWest';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''roll, $\phi$ [deg]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'

myfig_jespestana

% Yaw
myfig_filename = [myfig_filename_init,'Yaw'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ardrone.state.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'ardrone.state.yaw','ctrlr.state.DYco*100'};%,'ctrlr.state.Rco*180.0/pi'};
% myfig_legend     = {'yaw, telemetry (0 deg is North facing)','controller command'};
% myfig_legendLocation = 'West';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'Yaw [deg] Yaw speed cmd [deg/s]';
myfig_legend     = '{''yaw, telemetry (0 deg, North)'',''yaw, controller command''}';
myfig_legendLocation = 'West';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''Yaw, $\psi$ [deg] $\frac{d\psi}{dt}_r$ [deg/s]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'

myfig_jespestana

% Altitude - Z
myfig_filename = [myfig_filename_init,'Altitude'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ardrone.state.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'-ardrone.state.z','ctrlr.state.Dzco'};%,'ctrlr.state.Rco*180.0/pi'};
% myfig_legend     = {'Altitude, telemetry','Altitude controller command'};
% myfig_legendLocation = 'East';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'Alt. [m], Alt. speed cmd [m/s]';
myfig_legend     = '{''Altitude, telemetry'',''Alt. controller command''}';
myfig_legendLocation = 'East';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''Alt. [m], Alt. speed [m/s]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'

myfig_jespestana

%% IBVS references  and measurements against time

% IBVS - fx
myfig_filename = [myfig_filename_init,'fx'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.time','ctrlr.state.time','ctrlr.state.time'};
myfig_var2plot_y = {'ctrlr.state.fxs','ctrlr.state.fxci','ctrlr.state.tof'};
% myfig_legend     = {'f_x, tracker','f_x, reference','(bool) target on frame?'};
% myfig_legendLocation = 'NorthWest';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'f_x [0/1], (bool) [0=False;1=True]';
myfig_legend     = '{''$f_x$, tracker'',''$f_x$, reference'',''(bool) target on frame?''}';
myfig_legendLocation = 'SouthWest';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''$f_x [0/1]$, (bool) [1=True]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'
% aux_min_x = Inf; 
aux_min_y = 0;
% aux_max_x = -Inf; 
aux_max_y = 1.1;

myfig_jespestana

% IBVS - fy
myfig_filename = [myfig_filename_init,'fy'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'ctrlr.state.fys','ctrlr.state.fyci'};%,'ctrlr.state.tof'};
% myfig_legend     = {'f_y, tracker','f_y, reference'};
% myfig_legendLocation = 'NorthWest';
% myfig_xlabel        = 'time [s]';
% myfig_ylabel        = 'f_y [0/1]';
myfig_legend     = '{''$f_y$, tracker'',''$f_y$, reference''}';
myfig_legendLocation = 'NorthWest';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''$f_y [0/1]$'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'
% aux_min_x = Inf; 
aux_min_y = 0;
% aux_max_x = -Inf; 
aux_max_y = 1.0;

myfig_jespestana

% IBVS - fD
myfig_filename = [myfig_filename_init,'fD'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.time','ctrlr.state.time','ctrlr.state.time'};%,'ctrlr.state.time'};
myfig_var2plot_y = {'ctrlr.state.fDs','ctrlr.state.fDci','ctrlr.state.Dxs'};%,'ctrlr.state.tof'};
myfig_legend     = '{''$f_\Delta$, tracker'',''$f_\Delta$, reference (= 11.7)'',''est. dist. to target [m]''}';
% myfig_legendLocation = 'SouthOutside';
myfig_legendLocation = 'West';
myfig_additionallegend = ',''Interpreter'', ''latex''';
myfig_xlabel        = '''time [s]'', ''Interpreter'', ''latex''';
myfig_ylabel        = '''$f_\Delta~[>0]$, distance [m]'', ''Interpreter'', ''latex''';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'

myfig_jespestana

%% Dx, Dy, Dz

% IBVS - fx
myfig_filename = [myfig_filename_init,'Dx'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.time'};
myfig_var2plot_y = {'ctrlr.state.Dxs'};
myfig_legend     = {'estimate'};
myfig_legendLocation = 'NorthEast';
myfig_xlabel        = 'time [s]';
myfig_ylabel        = 'Dx [m]';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'
myfig_jespestana

% IBVS - Dy
myfig_filename = [myfig_filename_init,'Dy'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.time'};
myfig_var2plot_y = {'ctrlr.state.Dys'};
myfig_legend     = {'estimate'};
myfig_legendLocation = 'NorthEast';
myfig_xlabel        = 'time [s]';
myfig_ylabel        = 'Dy [m]';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'
myfig_jespestana

% IBVS - Dz
myfig_filename = [myfig_filename_init,'Dz'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.time'};
myfig_var2plot_y = {'ctrlr.state.Dzs'};
myfig_legend     = {'estimate'};
myfig_legendLocation = 'NorthEast';
myfig_xlabel        = 'time [s]';
myfig_ylabel        = 'Dz [m]';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'myfig_jespestana
myfig_jespestana

% IBVS - DxDyDz

myfig_filename = [myfig_filename_init,'XYZ'];
myfig_config   = 'single_column'; % 'single_column' o 'double_column'
myfig_var2plot_x = {'ctrlr.state.Dxs'};
myfig_var2plot_y = {'ctrlr.state.Dys'};
myfig_var2plot_z = {'ctrlr.state.Dzs'};
myfig_legend     = {'IBVS'};
myfig_legendLocation = 'SouthEast';
myfig_xlabel        = 'Dx [m]';
myfig_ylabel        = 'Dy [m]';
myfig_zlabel        = 'Dz [m]';
myfig_LineWidth  = 2; 
myfig_AxisGridWidth  = 1.5; 
myfig_GridLineStyle  = '--'; % '-' '--' ':' '-.'


% Create figure window
switch myfig_config
    case 'single_column'
        fig('units','centimeters','width',12.6,'height',6.0,'font','Helvetica','fontsize',12)
        %     case 'double_column'
    case 'half_column'
        fig('units','centimeters','width',8,'height',6,'font','Helvetica','fontsize',12)
    otherwise
        fig('units','centimeters','width',6,'height',4,'font','Helvetica','fontsize',12)
end

% Plot lines
aux_min_x = Inf; aux_min_y = Inf; aux_min_z = Inf;
aux_max_x = -Inf; aux_max_y = -Inf; aux_max_z = -Inf;
for i=1:length(myfig_var2plot_x)
    eval(['plot3(', myfig_var2plot_x{i},',',myfig_var2plot_y{i},',',myfig_var2plot_z{i},',''LineWidth'',', num2str(myfig_LineWidth),');'])
    hold all;
    eval(['aux_min_x = min([aux_min_x min(',myfig_var2plot_x{i},')]);']);
    eval(['aux_max_x = max([aux_max_x max(',myfig_var2plot_x{i},')]);']);
    eval(['aux_min_y = min([aux_min_y min(',myfig_var2plot_y{i},')]);']);
    eval(['aux_max_y = max([aux_max_y max(',myfig_var2plot_y{i},')]);']);
    eval(['aux_min_z = min([aux_min_z min(',myfig_var2plot_z{i},')]);']);
    eval(['aux_max_z = max([aux_max_z max(',myfig_var2plot_z{i},')]);']);
end
eval(['ind = 1:length(',myfig_var2plot_x{1},');']);
ind = mod(ind,70);
ind = (ind == 0);
% quiver3( EKF_X(ind), EKF_Y(ind), EKF_Z(ind), cos(EKF_Yaw(ind)), sin(EKF_Yaw(ind)), sin(EKF_Yaw(ind)*0.0),1,'LineWidth', myfig_LineWidth)
% % quiver3( EKF_X, EKF_Y, EKF_Z, cos(EKF_Yaw), sin(EKF_Yaw), sin(EKF_Yaw*0.0),5)
xlim([aux_min_x aux_max_x]);
ylim([aux_min_y aux_max_y]);
zlim([aux_min_z aux_max_z]);
zlim([0 +2.0]);
box on
clear aux_min_x aux_max_x aux_min_y aux_max_y aux_min_z aux_max_z;
axis equal

set(gca,'LineWidth',myfig_AxisGridWidth)
set(gca,'GridLineStyle',myfig_GridLineStyle)
grid on;
% ylabel(myfig_ylabel)
text(-1.5,0.5,0,'Y [m]')
xlabel(myfig_xlabel)
zlabel(myfig_zlabel)
legend(myfig_legend,'Location',myfig_legendLocation)
% title('Vym')
eval(['export_fig ',myfig_filename,' -transparent -pdf -eps']);
eval(['saveas(gcf,''',myfig_filename,'.fig'');']);
% export_fig 'prueba' -transparent -pdf -eps
% saveas(gcf,'prueba.fig')