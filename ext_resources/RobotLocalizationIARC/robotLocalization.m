clear all
close all
clc

view3d=figure('units','normalized','outerposition',[0 0 1 1]);
plot3([0 0.1],[0 0],[0 0],'r',[0 0],[0 0.1],[0 0],'g',[0 0],[0 0],[0 0.1],'b','linewidth',2);
grid on;
hold on;
xlabel('X_{world}');
ylabel('Y_{world}');
zlabel('Z_{world}');

pelicanPosewrtWorld=[1,1,4,pi,0,0];
pelicanPlot = plotCoordSystemXYZ(pelicanPosewrtWorld,0.3,'Pelican');

cameraPosewrtPelican=[0,0,1,pi/4,0,pi/2];
pelicanPosewrtWorldRT=[getRotationMatrix([pelicanPosewrtWorld(4),pelicanPosewrtWorld(5),pelicanPosewrtWorld(6)]) ,pelicanPosewrtWorld(1:3)';[0 0 0 1]];
cameraPosewrtPelicanRT=[getRotationMatrix([cameraPosewrtPelican(4),cameraPosewrtPelican(5),cameraPosewrtPelican(6)]) ,cameraPosewrtPelican(1:3)';[0 0 0 1]];

cameraPosewrtWorldRT =  pelicanPosewrtWorldRT * cameraPosewrtPelicanRT;
[anglesX,anglesY,anglesZ] = decomposeRotation(cameraPosewrtWorldRT(1:3,1:3));
cameraPosewrtWorld=[cameraPosewrtWorldRT(1:3,4)',anglesX,anglesY,anglesZ];
cameraPlot = plotCoordSystemXYZ(cameraPosewrtWorld,0.1,'Camera');
 
sensorWidth=4.512e-3;
sensorHeight=2.880e-3;
imageWidth = 752;
imageHeight = 480;
pixelSize=sensorWidth/imageWidth;
fx=5.1364237519117466e+002;
fy=4.9943334932413785e+002;
cx=imageWidth/2;%3.5627828670816609e+002;
cy=imageHeight/2;%2.5874845721600940e+002;
f=fx*sensorWidth/imageWidth;

sensorCornerswrtCamera(:,1)=[sensorWidth/2;sensorHeight/2;0];
sensorCornerswrtCamera(:,2)=[sensorWidth/2;-sensorHeight/2;0];
sensorCornerswrtCamera(:,3)=[-sensorWidth/2;-sensorHeight/2;0];
sensorCornerswrtCamera(:,4)=[-sensorWidth/2;sensorHeight/2;0];
opticalCenterwrtCamera = [0;0;-f];

for i=1:size(sensorCornerswrtCamera,2)
    sensorCornerswrtWorld(:,i) = convertFromHomogeneous(cameraPosewrtWorldRT * convertToHomogeneous(sensorCornerswrtCamera(:,i)));
end

opticalCenterwrtWorld = convertFromHomogeneous(cameraPosewrtWorldRT * convertToHomogeneous(opticalCenterwrtCamera));
sensorLine1=[sensorCornerswrtWorld(:,1),sensorCornerswrtWorld(:,2)];
sensorLine2=[sensorCornerswrtWorld(:,2),sensorCornerswrtWorld(:,3)];
sensorLine3=[sensorCornerswrtWorld(:,3),sensorCornerswrtWorld(:,4)];
sensorLine4=[sensorCornerswrtWorld(:,4),sensorCornerswrtWorld(:,1)];
plot3(sensorLine1(1,:),sensorLine1(2,:),sensorLine1(3,:),'k');
plot3(sensorLine2(1,:),sensorLine2(2,:),sensorLine2(3,:),'k');
plot3(sensorLine3(1,:),sensorLine3(2,:),sensorLine3(3,:),'k');
plot3(sensorLine4(1,:),sensorLine4(2,:),sensorLine4(3,:),'k');

for i=1:size(sensorCornerswrtWorld,2)
    t=-opticalCenterwrtWorld(3)/(sensorCornerswrtWorld(3,i)-opticalCenterwrtWorld(3));
    intersectionsWithFloorwrtWorld(:,i)=[opticalCenterwrtWorld(1)+t*(sensorCornerswrtWorld(1,i)-opticalCenterwrtWorld(1));opticalCenterwrtWorld(2)+t*(sensorCornerswrtWorld(2,i)-opticalCenterwrtWorld(2));0];
end

frustumLine1=[sensorCornerswrtWorld(:,1),intersectionsWithFloorwrtWorld(:,1)];
frustumLine2=[sensorCornerswrtWorld(:,2),intersectionsWithFloorwrtWorld(:,2)];
frustumLine3=[sensorCornerswrtWorld(:,3),intersectionsWithFloorwrtWorld(:,3)];
frustumLine4=[sensorCornerswrtWorld(:,4),intersectionsWithFloorwrtWorld(:,4)];
frustumOnFloor1=[intersectionsWithFloorwrtWorld(:,1),intersectionsWithFloorwrtWorld(:,2)]
frustumOnFloor2=[intersectionsWithFloorwrtWorld(:,2),intersectionsWithFloorwrtWorld(:,3)]
frustumOnFloor3=[intersectionsWithFloorwrtWorld(:,3),intersectionsWithFloorwrtWorld(:,4)]
frustumOnFloor4=[intersectionsWithFloorwrtWorld(:,4),intersectionsWithFloorwrtWorld(:,1)]
plot3(frustumLine1(1,:),frustumLine1(2,:),frustumLine1(3,:),'k');
plot3(frustumLine2(1,:),frustumLine2(2,:),frustumLine2(3,:),'k');
plot3(frustumLine3(1,:),frustumLine3(2,:),frustumLine3(3,:),'k');
plot3(frustumLine4(1,:),frustumLine4(2,:),frustumLine4(3,:),'k');
plot3(frustumOnFloor1(1,:),frustumOnFloor1(2,:),frustumOnFloor1(3,:),'r');
plot3(frustumOnFloor2(1,:),frustumOnFloor2(2,:),frustumOnFloor2(3,:),'r');
plot3(frustumOnFloor3(1,:),frustumOnFloor3(2,:),frustumOnFloor3(3,:),'r');
plot3(frustumOnFloor4(1,:),frustumOnFloor4(2,:),frustumOnFloor4(3,:),'r');

robotPosewrtWorld=[8,6,0,0,0,0]
robotPosewrtWorldRT=[getRotationMatrix([robotPosewrtWorld(4),robotPosewrtWorld(5),robotPosewrtWorld(6)]),robotPosewrtWorld(1:3)';[0 0 0 1]];

robotPlot = plotCoordSystemXYZ(robotPosewrtWorld,0.3,'Robot');

robotPosewrtCamera=inv(cameraPosewrtWorldRT)*robotPosewrtWorldRT;
cameraIntrinsics=[fx 0 cx; 0 fy cy;0 0 1];

robotProjectionCoordinatesOnImage=convertFromHomogeneous(cameraIntrinsics*robotPosewrtCamera(1:3,4))
robotProjectionCoordinateswrtCamera = pixelSize*([robotProjectionCoordinatesOnImage ; 0 ] - [cx; cy; 0]);
robotProjectionCoordinateswrtWorld = convertFromHomogeneous(cameraPosewrtWorldRT * convertToHomogeneous(robotProjectionCoordinateswrtCamera));

t=-opticalCenterwrtWorld(3)/(robotProjectionCoordinateswrtWorld(3)-opticalCenterwrtWorld(3));
intersectionWithFloorwrtWorld=[opticalCenterwrtWorld(1)+t*(robotProjectionCoordinateswrtWorld(1)-opticalCenterwrtWorld(1));opticalCenterwrtWorld(2)+t*(robotProjectionCoordinateswrtWorld(2)-opticalCenterwrtWorld(2));0]

error = norm(intersectionWithFloorwrtWorld - robotPosewrtWorld(1:3)',2)


