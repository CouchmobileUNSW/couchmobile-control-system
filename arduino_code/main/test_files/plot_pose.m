clear, clc;

% Call data file
% s2();
t1();

% Get positions
x = DATA(:,1); 
y = DATA(:,2);
angle = DATA(:,3);

% Set data
% s1();
% cx = DATA(:,1);
% cy = DATA(:,2);
t = linspace(0, 5, 10)';
cx = t.*cos(t);
cy = t.*sin(t);

% Plot data
figure(1); clf();
h1 = plot(cx, cy, 'r-');          % path to follow
hold on;
robot = plot(0, 0, 'b-');       % robot history
robotDir = plot(0, 0, 'k*');    % robot direction
hold off; 
grid on;
xlabel('x (m)'); ylabel('y (m)');
axis([-5, 5, -5, 5]);

% Iterate and plot sequence
for i = 1:numel(x)
    % Plot robot
    set(robot, 'xdata', x(1:i), 'ydata', y(1:i));
    
    % Plot robot heading
    L = 0.1;
    x_head = x(i) + L*cos(angle(i));
    y_head = y(i) + L*sin(angle(i));
    set(robotDir, 'xdata', x_head, 'ydata', y_head);
    
    % For plotting
    pause(0.001);
end