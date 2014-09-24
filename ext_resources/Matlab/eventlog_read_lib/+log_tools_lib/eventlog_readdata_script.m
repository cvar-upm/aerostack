%% eventlog_readdata:
%       This script reads the event_log.txt located on the path specified
%       by the 'file_path' variable (this variable must be set correctly
%       before calling this script). 
%       The eventlog_read library must be added to the Matlab path. The 
%       library currently includes the following files:
%             eventlog_read/:
%             eventlog_plotdata_example.m
%             eventlog_readdata.m
%             example_data
%             log_tools_lib
%             old_log_tools_lib
% 
%             eventlog_read/example_data:
%             events_log_ex1.txt
%             events_log.txt
% 
%             eventlog_read/log_tools_lib:
%             log_reading_comptags.m
% 
%             eventlog_read/old_log_tools_lib:
%             log2signals.m
%             pos_from_vel.m
%             rotk.m
%             txt2cellm.m
% 
%       The format is similar to MAVworks event_log model, and the format 
%       is specifically which is the following:
%           Time [tag;subtag;subsubtag;[...]] signal1:value signal2:value
%               signal3:value [...]
%           Where,
%               Time, is a float/double number specifying time
%               tag, subtag, [...], are strings that usually specify:
%                   tag, one of the main robots subsystems (ekf,
%                       controller, etc)
%                   subtag, something specific on the subsystem (it may be
%                       interesting to separate configuration values, such 
%                       as controller gains, from time-singals).
%               signal, is a string specifying a (descriptive) name to the
%                   logged data signal.
%               value, currently it can be either a number or a string.
%                   This fact allows the storage of numeric time data 
%                   signals as well as to store working modes or events
%                   that are better described using strings.
% 
%       With it the script will produce data structures like:
%           tag1.time
%           tag1.signal1
%           tag1.signal2
%           [...]
%           tagn.subtag.subsubtag.[...].time
%           tagn.subtag.subsubtag.[...].signal1
%           tagn.subtag.subsubtag.[...].signal2
%       
% 
%       The script is convenient because it provides a single
%       eventlog_reading code for multiple controllers/experimental setups.
%
%
% Usage example:
%  file_path = '/home/jespestana/Documents/MATLAB/eventlog_read/example_data/events_log.txt';
%  eventlog_readdata


% %% Add proxy log_tools to path
% clear all, close all, clc;
% addpath(genpath('./log_tools_lib'));
% file_path = 'events_log.txt';

% Interesting example of how I am reading the txt file in the url: 
%   http://www.mathworks.com/help/matlab/import_export/import-large-text-files.html
tic
disp(['Loading file "' file_path '"...']);
file_id = fopen(file_path,'r');
seps = [' ' ':'];
data = textscan(file_id,'%s','delimiter','\n'); data = data{1};
nseps = max(size(seps));
if (nseps > 1),
    for i=2:nseps,
        data = cellfun(@(x) strrep(x, seps(i), seps(1)), data, 'UniformOutput', false);
    end
end
data = cellfun(@(x) regexp(x, seps(1), 'split'), data, 'UniformOutput', false);
data = data';
clear nseps seps;
disp('*** Elapsed time: reading from file and loading to workspace')
toc % measure elapsed time for this operation.
fclose(file_id); 
clear file_id;

% Make list of tags, subtags, subsubtags, [...]
[tags aux_index ] = unique(cellfun(@(x) x{2}, data, 'UniformOutput', false));

% check if time_init and time_end variables exist, otherwise define them
try
    time_init;
catch
    time_init = -Inf;
end
try
    time_end;
catch
    time_end = +Inf;
end


% Load data into the data structure
tic
for i=1:length(tags)
    if ( strcmp(tags{i},'') )
        continue;
    end
    domain_name_orig = tags{i};
    disp(['Recovering ', domain_name_orig, ' signals:'])
    domain_name = domain_name_orig;
    domain_name = strrep(domain_name, '[', '');
    domain_name = strrep(domain_name, ']', '');
    domain_name_script = domain_name;
    domain_name = strrep(domain_name, ';', '.');
    time_name = [domain_name, '.', 'time'];
    
    domain_cell = cellfun(@log_reading_comptags, data, repmat({domain_name_orig},1,length(data)), 'UniformOutput', false);
    domain_cell = domain_cell(~cellfun('isempty',domain_cell));
    eval([time_name, ' = cell2mat(cellfun(@(x) str2double(x{1}), domain_cell, ''UniformOutput'', false));']);
    time_init_end_funtionality_is_ok = true;
    eventlogread_aux_idx = eval(['find( (time_init <',time_name,') & (',time_name,'<time_end));']);
    if isempty(eventlogread_aux_idx)
        time_init_end_funtionality_is_ok = false;
        eval(['eventlogread_aux_idx = 1:length(',time_name,');']);
    else
        eval([time_name,' = ',time_name,'(eventlogread_aux_idx);']);
%         eval([time_name,' = ',time_name,' - ',time_name,'(1);']);
        time_init_name = [domain_name, '.', 'time_init'];
        time_end_name = [domain_name, '.', 'time_end'];
        eval([time_init_name,' = ',num2str(time_init),';']);
        eval([time_end_name,' = ',num2str(time_end),';']);
    end
    for j=3:2:length(data{aux_index(i)})
        var_name  = [domain_name, '.', data{aux_index(i)}{j}];
        var_name = strrep(var_name, ';', '.');
        disp(['... ' , var_name])
        eval(['eventlogread_sample_value = domain_cell{1}{',num2str(j),'+1};']);
        if not(isnan(str2double(eventlogread_sample_value)))
            eval([var_name, ' = cell2mat(cellfun(@(x) str2double(x{',num2str(j),'+1}), domain_cell, ''UniformOutput'', false));']);
        else
            eval([var_name, ' = cellfun(@(x) x{',num2str(j),'+1}, domain_cell, ''UniformOutput'', false);']);
        end
        if time_init_end_funtionality_is_ok
            eval([var_name,' = ',var_name,'(eventlogread_aux_idx);']);
        end
    end
end
disp('*** Elapsed time: reading the data into the data structures.')
toc

clear i j domain_name domain_name_script time_name var_name aux_index tags ans domain_cell domain_name_orig eventlogread_aux_idx time_init_name time_end_name time_init_end_funtionality_is_ok eventlogread_sample_value data