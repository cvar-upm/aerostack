function [res] = log_reading_comptags( x, tag)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

if ( strcmp(x{2},tag) )
%     x
    res = x;
else
    res = {};
end

end

