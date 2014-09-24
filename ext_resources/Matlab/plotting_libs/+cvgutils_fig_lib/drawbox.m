p1 = [aux_min_x aux_min_y aux_min_z];
p2 = [aux_max_x aux_min_y aux_min_z];
p3 = [aux_max_x aux_max_y aux_min_z];
p4 = [aux_min_x aux_max_y aux_min_z];
p5 = [aux_min_x aux_min_y aux_max_z];
p6 = [aux_max_x aux_min_y aux_max_z];
p7 = [aux_max_x aux_max_y aux_max_z];
p8 = [aux_min_x aux_max_y aux_max_z];

A = vertcat(p1,p2,p3,p4,p1,p5,p6,p7,p8,p5,p6,p2,p3,p7,p8,p4);
plot3(A(:,1),A(:,2),A(:,3),'LineWidth',myfig_LineWidth);
   

  



