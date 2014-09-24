%close all
%clear all
clc




importfile('../nodesList.dat')
importfile('../nodesRelation.dat')
importfile('../solutionNodes.dat');
importfile('../simplifSolNodes.dat');



%Init figure
figure(1);
axis equal
hold on;

grid on

%Limits
xlim([0 12])
ylim([0 26])




%PRM
if(1)
    plot(nodesList(:,1),nodesList(:,2),'.c');
end


if(0)
    for(i=1:size(nodesRelation,1))
       plot([nodesList(nodesRelation(i,1)+1,1);nodesList(nodesRelation(i,2)+1,1)],[nodesList(nodesRelation(i,1)+1,2);nodesList(nodesRelation(i,2)+1,2)],'c') 

    end
end



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



%QR
%plotCircle(7.5,5.7,1.0,'k');





%Path
%solucionNodes=[5000;3291;1104;4894;668;1538;707;844;18;3745;4855;2965;1289;999;4212;2063;4747;2862;2320;445;3124;2414;455;831;1673;3270;3741;2547;982;3399;2921;777;1178;1519;824;2942;3428;3660;1007;2665;3902;4423;295;4612;482;4844;3119;4865;1365;3528;2602;2680;720;809;4807;465;1926;2055;1541;4774;3968;1493;4250;1866;704;3299;3154;4573;2756;1297;4540;649;3535;4062;2919;2664;106;706;1774;2080;2084;2510;3798;3905;3174;4095;1790;1029;5001];

%%%Nodes solution
if(1)
    nodesSolution=[];
    for(i=1:size(solutionNodes,1)) 
        nodesSolution=[nodesSolution; nodesList(solutionNodes(i,1)+1,1), nodesList(solutionNodes(i,1)+1,2)];
    end

    if(size(nodesSolution,1)>0)
        plot(nodesSolution(:,1),nodesSolution(:,2),'m','lineWidth',1)
    end
end



%%%%Simplified path
nodesSolutionSimp=[];
for(i=1:size(simplifSolNodes,1)) 
    nodesSolutionSimp=[nodesSolutionSimp; nodesList(simplifSolNodes(i,1)+1,1), nodesList(simplifSolNodes(i,1)+1,2)];
end

if(size(nodesSolutionSimp,1)>0)
    plot(nodesSolutionSimp(:,1),nodesSolutionSimp(:,2),'o-r','lineWidth',2)
end