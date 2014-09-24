function [ X, Y, Z ] = decomposeRotation(R)

X = atan2(R(3,2), R(3,3));
Y = atan2(-R(3,1), sqrt(R(3,2)*R(3,2) + R(3,3)*R(3,3)));
Z = atan2(R(2,1), R(1,1));

%X = atan2(-R(3,1), sqrt(R(1,1)*R(1,1) + R(2,1)*R(2,1)));
%Y = atan2(R(3,2)/cos(X), R(3,3)/cos(X));
%Z = -atan2(R(2,1)/cos(X), R(1,1)/cos(X));
end

