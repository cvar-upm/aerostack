%%%Followed trajectory


close all
clear all
clc


%Init figure
figure(1);





while(1)
    
    clf
    
    axis equal
    hold on;

    grid on

    %Limits
    xlim([0 12])
    ylim([0 26])
    
    
    importfile('../trajectory.dat');












    %Obstaculos
    plotCircle(3.2,11.2,0.2,'k');
    plotCircle(8.8,11.2,0.2,'k');
    plotCircle(8.8,16.8,0.2,'k');
    plotCircle(3.2,16.8,0.2,'k');

    plotCircle(7.8,12.8,0.4,'k');
    plotCircle(5.2,12.0,0.3,'k');
    plotCircle(6,14.4,0.45,'k');
    plotCircle(7,16,0.1,'k');

    plotRectangle(4.5,7.95,5,0.1);
    plotRectangle(9.25,7.95,1.5,0.1);
    plotRectangle(1,7.95,2,0.1);
    plotRectangle(11.0,7.95,2,0.1);






    plot(trajectory(:,1),trajectory(:,2),'r','lineWidth',2)

    drawnow


end