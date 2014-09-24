function [] = set_grid( h, config)
%SET_GRID Summary of this function goes here
%   Detailed explanation goes here

figure(h)
set(gca,'LineWidth',config.AxisGridWidth)
set(gca,'GridLineStyle',config.GridLineStyle)
grid on;

end

