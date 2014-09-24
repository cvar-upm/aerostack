function [] = set_color( h, config)
%SET_COLOR Summary of this function goes here
%   Detailed explanation goes here

figure(h)
h_aux = get(gca,'Children');
param_Color = get(h_aux,'Color');
if ( not(iscell(param_Color)) )
    param_Color = config.Color{1};
    set(h_aux(1),'Color', param_Color);
else
    N = length(param_Color);
    for i=1:N;
        param_Color{i} = config.Color{1+mod(i-1,length(config.Color))};
        set(h_aux(N+1-i),'Color', param_Color{i});
    end
end

end

