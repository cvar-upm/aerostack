function [ config ] = default_configuration()
%DEFAULT_CONFIGURATION Summary of this function goes here
%   Detailed explanation goes here

config.adjust_plot_limits_to_data = true;
config.x_axis_lims = [0  9]; % if false
config.y_axis_lims = [0 18];
use_latex = true;

config.LineStyle = {'-','--','-.',':','--','-.',':'};
config.LineWidth  = {2}; 
config.AxisGridWidth  = 1.5; 
config.GridLineStyle  = '--'; % '-' '--' ':' '-.'
config.Color  = { 'r', 'g', 'b', 'm', 'c', 'y', 'k'}; 


end

