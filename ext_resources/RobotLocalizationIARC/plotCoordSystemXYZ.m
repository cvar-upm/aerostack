function [ handles ] = plotCoordSystemXYZ( pose , scale, objectName )
%Pose is X,Y,Z,P,R,Y
T=pose(1:3)';
R=getRotationMatrix(pose(4:6));

points(:,1)=[0; 0; 0];
points(:,2)=[scale; 0; 0];
points(:,3)=[0; scale; 0];
points(:,4)=[0; 0; scale];

for i=1:size(points,2)
    transformedPoints(:,i)=convertFromHomogeneous([R,T;[0 0 0 1]]*convertToHomogeneous(points(:,i)));
end

line1=[transformedPoints(:,1),transformedPoints(:,2)];
line2=[transformedPoints(:,1),transformedPoints(:,3)];
line3=[transformedPoints(:,1),transformedPoints(:,4)];

handles(1)=plot3(line1(1,:),line1(2,:),line1(3,:),'r');
handles(2)=plot3(line2(1,:),line2(2,:),line2(3,:),'g');
handles(3)=plot3(line3(1,:),line3(2,:),line3(3,:),'b');

text(transformedPoints(1,2),transformedPoints(2,2),transformedPoints(3,2),['X_{', objectName, '}'])
text(transformedPoints(1,3),transformedPoints(2,3),transformedPoints(3,3),['Y_{', objectName, '}'])
text(transformedPoints(1,4),transformedPoints(2,4),transformedPoints(3,4),['Z_{', objectName, '}'])

end
