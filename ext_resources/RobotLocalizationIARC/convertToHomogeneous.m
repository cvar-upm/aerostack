function [ pointHomogeneous ] = convertToHomogeneous( point )
if (size(point,1)==1)
    pointHomogeneous=[point,1];
else
    pointHomogeneous=[point;1];
end
end

