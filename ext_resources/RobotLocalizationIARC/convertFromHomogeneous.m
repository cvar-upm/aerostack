function [ point ] = convertFromHomogeneous( pointHomogeneous )
    point=pointHomogeneous(1:numel(pointHomogeneous)-1)/pointHomogeneous(numel(pointHomogeneous));
end
