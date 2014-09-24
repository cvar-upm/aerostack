function [ h_fig ] = figure( width_cm, height_cm, varargin)
% Opens a figure using fig_lib
% Note: IEEE papers have:
%   1 column: width=17cm
%   2 column: width= 8cm

if (nargin > 2)
    h_fig = fig('units','centimeters','width', width_cm,'height', height_cm, varargin);
else
    h_fig = fig('units','centimeters','width', width_cm,'height', height_cm, 'font','Helvetica','fontsize',12);
end
    
end

