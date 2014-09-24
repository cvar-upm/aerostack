%Planified trajectory!!!

close all
clear all
clc




%Init figure
figure(1);
hold on


title('Actual trajectory')
        
xlabel('x')
ylabel('y')
zlabel('z')

axis equal
grid on

%Limits
% xlim([-5 12])
% ylim([-5 26])
% zlim([0 4])


%Obstaculos
% plotCircle(3.2,11.2,0.2,'k');
% plotCircle(8.8,11.2,0.2,'k');
% plotCircle(8.8,16.8,0.2,'k');
% plotCircle(3.2,16.8,0.2,'k');
% 
% plotCircle(7.8,12.8,0.4,'k');
% plotCircle(5.2,12.0,0.3,'k');
% plotCircle(6,14.4,0.45,'k');
% plotCircle(7,16,0.1,'k');
% 
% plotRectangle(4.5,7.95,5,0.1);
% plotRectangle(9.25,7.95,1.5,0.1);
% plotRectangle(1,7.95,2,0.1);
% plotRectangle(11.0,7.95,2,0.1);
        

while(1)
    
    %Delete plots
    if(exist('hTraject','var'))
        delete(hTraject)
    end
    if(exist('hDrone','var'))
        delete(hDrone)
    end
    

    
    %Delete vars
%     clear all
    clear trajectory 

    
    
    %Import
    % importfile('../nodesList.dat')
    %importfile('../nodesRelation.dat')
    %importfile('../solutionNodes.dat');
    %importfile('../simplifSolNodes.dat');
    
    
    importfile('../trajectory.dat');





    %Trajectory
    if(size(trajectory,1)>0)
        hTrayect=plot3(trajectory(1:size(trajectory,1),1),trajectory(1:size(trajectory,1),2),trajectory(1:size(trajectory,1),3),'r','lineWidth',1);
        
        

        %Read drone
        drone=[trajectory(size(trajectory,1),1);trajectory(size(trajectory,1),2);trajectory(size(trajectory,1),3)];
        droneAngles=[trajectory(size(trajectory,1),4);trajectory(size(trajectory,1),5);trajectory(size(trajectory,1),6)];


        
        %Plot drone!!
%         plot3(drone(1),drone(2),drone(3),'ob','lineWidth',2)
        
        hDrone=quiver3(drone(1),drone(2),drone(3),cos(droneAngles(1)),sin(droneAngles(1)),0,'lineWidth',2);

        drawnow
    end

%Sleep a while
pause(1.0/20)




end