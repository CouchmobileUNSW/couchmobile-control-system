clear, clc

% Create graphic handles
figure(1); clf();
h1 = plot(0, 0, 'b*'); hold on;     % path
robot = plot(0, 0, 'r-');           % robot centre of wheels
robotPath = plot(0, 0, 'r*');       % path of the robot
robotHead = plot(0, 0, 'k*');       % indicates robot heading
hold off;

% Figure configs
grid on;
axis([-1,5,-1,5]);  
xlabel('X (meters)'); ylabel('Y (meters');
legend('path', 'robot');

% Generate path
% t = linspace(0, 5, 10)';
% cx = t.*cos(t);
% cy = t.*sin(t);
% Will's data
s1();
cx = DATA(:,1);
cy = DATA(:,2);
set(h1, 'xdata', cx, 'ydata', cy);

% Find tangent to each point (backwards difference)
cyaw = [0; atan2((cy(2:end) - cy(1:end-1)), (cx(2:end) - cx(1:end-1) ))];
cyaw(end+1) = cyaw(end);

% Configure stanley gains
global k
k = 4;    % control gain (stanley angle)
Kp = 4;   % angle proportional control
dt = 0.1;   % time difference
L = 0.185;  % wheel base of vehicle

% Create robot position [x, y, yaw, v]
v_max = 0.6;    % m/s
w_max = 3;      % rad/s
pose = [0; 0; 0; 0];

% Initial variables
delta = 0;
current_target_idx = 0;

% Pose history
poseHistory = pose;

% Simulate data
i = 1; prevW = 0; curW = 0;
while(1)
    % Stop if close enough
    if(get_pose_error(pose, [cx(end); cy(end)]) < 0.4)
        break;
    end
    
    % Run stanley controller
    [delta,current_target_idx]  = stanley_control(pose, cx, cy, cyaw, current_target_idx);

    if(get_pose_error(pose, [cx(current_target_idx); cy(current_target_idx)]) > 5)
        v;
    end
    
    w = delta*Kp;
    if(w > w_max) w = w_max;
    elseif(w < -w_max) w = -w_max; end
    
    v = (1 - abs(w/(w_max+0.1)))*v_max;
    
    % Print variables
    v, w
    
    % Run process model
    pose = process_model(pose, v, w, dt);
    % Save history
    poseHistory(:, i) = pose;
    i = i + 1;
    
    % Plot heading direction
    poseHeading = pose(1:2) + L * [cos(pose(3)); sin(pose(3))];
    
    % Plot data
    set(robot, 'xdata', poseHistory(1, :), 'ydata', poseHistory(2, :));
    set(robotHead, 'xdata', poseHeading(1), 'ydata', poseHeading(2));
    pause(0.01);
end

fprintf('Program finished!');

% -----------Control-----------
% Find v and yaw to control
function [delta, current_target_idx] = stanley_control(pose, cx, cy, cyaw, last_target_idx)
    global k
    % Calculate target and perpendicular error
    [current_target_idx, error_front_axle] = calc_target_index(pose, cx, cy);
    
    % Ensure we are only moving forwards
    if(last_target_idx >= current_target_idx)
        current_target_idx = last_target_idx;
    end
    
    % theta_e corrects heading error
    theta_e = wrapToPi(cyaw(current_target_idx) - pose(3));
    
    % theta_d corrects cross track error (so it stays on the path)
    theta_d = atan2(k * error_front_axle, pose(4));
    
    % steering control
    delta = theta_e + theta_d;
end

% Find index in the list of points
function [target_idx, error_front_axle] = calc_target_index(pose, cx, cy)
    
    % Calc front axle position
    fx = cx ;%+ L*cos(pose(3));
    fy = cy ;%+ L*sin(pose(3));
    
    % Find the distance to all points
    dx = pose(1) - fx;
    dy = pose(2) - fy;
    d = sqrt(dx.^2 + dy.^2);
    
    % Find min distance index
    [~, target_idx] = min(d);
    
    % Project RMS error onto the front axle vector
    front_axle_vec = [-cos( pose(3) + pi/2 ), -sin( pose(3) + pi/2 )]; 
    
    % Use dot product to find projection
    error_front_axle = dot([ dx(target_idx), dy(target_idx) ], front_axle_vec);
end

% -----------Process model-----------
function X = process_model(X, v, w, T)
    X(1:3) = X(1:3) + T * [v*cos(X(3)); v*sin(X(3)); w];
    X(4) = v;
end

% Get pose error
function e = get_pose_error(pose, X)
    e = sqrt( sum( (pose(1:2)-X).^2) );
end









