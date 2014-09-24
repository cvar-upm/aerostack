function [] = set_line_style( h, config)
%SET_LINE_STYLE Summary of this function goes here
%   Detailed explanation goes here

figure(h)
h_aux = get(gca,'Children');
param_LineStyle = get(h_aux,'LineStyle');
if ( not(iscell(param_LineStyle)) )
    param_LineStyle = config.LineStyle{1};
    set(h_aux(1),'LineStyle', param_LineStyle);
else
    N = length(param_LineStyle);
    for i=1:N;
        param_LineStyle{i} = config.LineStyle{1+mod(i-1,length(config.LineStyle))};
        set(h_aux(N+1-i),'LineStyle', param_LineStyle{i});
    end
end

end

