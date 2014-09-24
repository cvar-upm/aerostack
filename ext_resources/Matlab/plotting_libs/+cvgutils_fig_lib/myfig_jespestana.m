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
try 
    aux_min_x; 
    aux_max_x;
catch
    aux_min_x = Inf; 
    aux_max_x = -Inf;
end
try
    aux_min_y; 
    aux_max_y;
catch
    aux_min_y = Inf;
    aux_max_y = -Inf;
end
for i=1:length(myfig_var2plot_x)
    eval(['plot(', myfig_var2plot_x{i},',',myfig_var2plot_y{i},',''LineWidth'',', num2str(myfig_LineWidth),',''LineStyle'',''',myfig_LineStyle{i},''');'])
    hold all;
    eval(['aux_min_x = min([aux_min_x min(',myfig_var2plot_x{i},')]);']);
    eval(['aux_max_x = max([aux_max_x max(',myfig_var2plot_x{i},')]);']);
    eval(['aux_min_y = min([aux_min_y min(',myfig_var2plot_y{i},')]);']);
    eval(['aux_max_y = max([aux_max_y max(',myfig_var2plot_y{i},')]);']);
end
xlim([aux_min_x aux_max_x]);
ylim([aux_min_y aux_max_y]);
clear aux_min_x aux_max_x aux_min_y aux_max_y;

set(gca,'LineWidth',myfig_AxisGridWidth)
set(gca,'GridLineStyle',myfig_GridLineStyle)
grid on;
try
    eval(['ylabel(',myfig_ylabel,');'])
catch
    ylabel(myfig_ylabel)
end
try
    eval(['xlabel(',myfig_xlabel,');'])
catch
    xlabel(myfig_xlabel)
end
try
    eval(['legend(',myfig_legend,',''Location'',''',myfig_legendLocation,'''',myfig_additionallegend,');'])
catch
    legend(myfig_legend,'Location',myfig_legendLocation)
end
eval(['export_fig ',myfig_filename,' -transparent -pdf -eps']);
% eval(['export_fig ',myfig_filename,' -transparent -eps']);
% eval(['export_fig ',myfig_filename,' -transparent -pdf']);
eval(['saveas(gcf,''',myfig_filename,'.fig'');']);
% export_fig 'prueba' -transparent -pdf -eps
% saveas(gcf,'prueba.fig')

clear myfig_ylabel  myfig_AxisGridWidth  myfig_GridLineStyle  myfig_LineWidth  myfig_config  myfig_filename  myfig_legend  myfig_legendLocation  myfig_var2plot_x  myfig_var2plot_y  myfig_xlabel myfig_additionallegend;
% clear aux_min_x aux_min_y aux_max_x aux_max_y;