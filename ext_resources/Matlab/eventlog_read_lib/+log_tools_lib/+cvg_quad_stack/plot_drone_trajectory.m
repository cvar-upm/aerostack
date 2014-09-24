function [ output_args ] = plot_drone_trajectory( h1, config, tk, deltaT, varargin )
% This function plots the (2D) trajectory of all drones given in varargin
%   for: tk-deltaT < t < tk.

% Plot trajectories
for i=1:(nargin-4)
    drone_data = varargin{i};
    idx = find( (drone_data.aruco_localizer.pose_GMR.time>tk-deltaT) & ...
                (drone_data.aruco_localizer.pose_GMR.time<tk) );
    plot(drone_data.aruco_localizer.pose_GMR.x(idx),drone_data.aruco_localizer.pose_GMR.y(idx));
    hold on;
    
%     idx = max( find(drone_data.trajectory_planner.droneTrajectory.time < tk) );
%     x_traj = eval(drone_data.trajectory_planner.droneTrajectory.x{idx})
%     y_traj = eval(drone_data.trajectory_planner.droneTrajectory.y{idx})
%     plot( x_traj, y_traj);
end
clear idx;

log_tools_lib.set_line_width( h1, config);
log_tools_lib.set_line_style( h1, config);
log_tools_lib.set_color( h1, config);
log_tools_lib.set_grid( h1, config);

% % Plot obstacles
% syms yaw;
% R_yaw = [+cos(yaw) -sin(yaw)  0;
%          +sin(yaw) +cos(yaw)  0;
%           0         0         1];
for i=1:(nargin-4)
    drone_data = varargin{i};
    idx = max( find(drone_data.obstacles_processor.obstacles.time < tk) );
    
    % poles
    poles_center = eval(drone_data.obstacles_processor.obstacles.poles_center{idx});
    poles_id     = eval(drone_data.obstacles_processor.obstacles.poles_id{idx});
    poles_size   = eval(drone_data.obstacles_processor.obstacles.poles_size{idx});
    poles_yaw    = eval(drone_data.obstacles_processor.obstacles.poles_yaw{idx});
    n = 30;
    for j=1:length(poles_id)
        R = poles_size(j,1);
        [Xc,Yc,Zc] = cylinder( R, n-1);
        xcirc = Xc(1,:); 
        ycirc = Yc(1,:);
        xcirc = xcirc + poles_center(j,1);
        ycirc = ycirc + poles_center(j,2);
        plot(xcirc, ycirc, 'k','LineWidth',2);
    end
    
    % rectangle
    walls_center = eval(drone_data.obstacles_processor.obstacles.walls_center{idx});
    walls_id     = eval(drone_data.obstacles_processor.obstacles.walls_id{idx});
    walls_size   = eval(drone_data.obstacles_processor.obstacles.walls_size{idx});
    walls_yaw    = eval(drone_data.obstacles_processor.obstacles.walls_yaw{idx});
    for j=1:length(walls_id)
        centerX = walls_center(j,1);
        centerY = walls_center(j,2);
        sizeX = walls_size(j,1);
        sizeY = walls_size(j,2);
        try
            rectangle('Position',[centerX - sizeX/2;centerY - sizeY/2;sizeX;sizeY],'LineWidth',2);
        catch
        end
    end
end

xlabel('X [m]','Interpreter','latex');
ylabel('Y [m]','Interpreter','latex')

log_tools_lib.set_axis_limits( h1, config);

end

