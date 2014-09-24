function [] = set_axis_limits( h, config)
%SET_AXIS_LIMIS Summary of this function goes here
%   Detailed explanation goes here

aux_min_x = Inf;
aux_max_x = -Inf;
aux_min_y = Inf;
aux_max_y = -Inf;

figure(h)
if (config.adjust_plot_limits_to_data)
    h_aux = get(gca,'Children');
    XData = get(h_aux,'XData');
    YData = get(h_aux,'YData');
    if ( not(iscell(XData)) )
        aux_min_x = min([aux_min_x min(XData)]);
        aux_max_x = max([aux_max_x max(XData)]);
        aux_min_y = min([aux_min_y min(YData)]);
        aux_max_y = max([aux_max_y max(YData)]);
    else
        for i=1:length(XData);
            aux_min_x = min([aux_min_x min(XData{i})]);
            aux_max_x = max([aux_max_x max(XData{i})]);
            aux_min_y = min([aux_min_y min(YData{i})]);
            aux_max_y = max([aux_max_y max(YData{i})]);
        end
    end
    xlim([aux_min_x aux_max_x]);
    ylim([aux_min_y aux_max_y]);
else
    try
        xlim(config.x_axis_lims);
        ylim(config.y_axis_lims);
    catch
    end
end

end

