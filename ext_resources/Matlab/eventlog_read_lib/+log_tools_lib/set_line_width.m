function [] = set_line_width( h, config)
%SET_LINE_WIDTH Summary of this function goes here
%   Detailed explanation goes here

figure(h)
h_aux = get(gca,'Children');
param_LineWidth = get(h_aux,'LineWidth');
if ( not(iscell(param_LineWidth)) )
    param_LineWidth = config.LineWidth{1};
    set(h_aux(1),'LineWidth', param_LineWidth);
else
    N = length(param_LineWidth);
    for i=1:N
        param_LineWidth{i} = config.LineWidth{1+mod(i-1,length(config.LineWidth))};
        set(h_aux(N+1-i),'LineWidth', param_LineWidth{i});
    end
end


end

