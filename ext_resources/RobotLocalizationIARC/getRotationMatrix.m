function [ R ] = getRotationMatrix(angles)
[alfa,beta,gamma]=deal(angles(1),angles(2),angles(3));
Rx=[1,0,0;0,cos(alfa),-sin(alfa);0,sin(alfa),cos(alfa)];
Ry=[cos(beta),0,sin(beta);0,1,0;-sin(beta),0,cos(beta)];
Rz=[cos(gamma),-sin(gamma),0;sin(gamma),cos(gamma),0;0,0,1];
R=Rz*Ry*Rx;
end

