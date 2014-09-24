function [] = save_figure( h, figure_name)
%SAVE_FIGURE Summary of this function goes here
%   Detailed explanation goes here

figure(h);
% eval(['export_fig ',figure_name,' -transparent -pdf -eps']);
eval(['saveas(gcf,''',figure_name,'.fig'');']);

% eval(['export_fig ',myfig_filename,' -transparent -eps']);
eval(['export_fig ',figure_name,' -transparent -pdf']);
% export_fig 'prueba' -transparent -pdf -eps
% saveas(gcf,'prueba.fig')

end

