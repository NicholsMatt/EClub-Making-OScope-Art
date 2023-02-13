%MathFunction_ToPlottablePoints.m
%Written by Matt Nichols (nichols.809) for the OSU Electronics Club
%February 12, 2023

%% Take a math function and plot it, then rescale output to 0-255 for x and y

t = 0:0.1:6;
x = 16*sin(t).^3
y = 13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t)

x1 = interp1([min(x), max(x)], [0,255], x);
y1 = interp1([min(y), max(y)], [0,255], y);

plot(x1,y1, 'o')

%% Convert to clockwise order
    %Comment out this section of code if you don't feel like downloading the Mapping Toolbox.
    %HOWEVER: this might mean that your shape looks funky, since the points need to be drawn in a continuous loop
   
[x2, y2] = poly2cw(x1, y1);

%% Run this if you didn't use the above poly2cw function

x2 = x1;
y2 = y1;

%% Generate the arrays for the arduino code

num_points = size(x2, 2);
disp("Num points = ");
disp(num_points);

x2 = round(x2);
disp("The x-value points are: ")
x2_array = regexprep( mat2str(x2), {'\[', '\]', '\s+'}, {'', '', ','});
disp(x2_array);

disp(" ")

y2 = round(y2);
% y2 = y2';
disp("The y-value points are: ")
y2_array = regexprep( mat2str(y2), {'\[', '\]', '\s+'}, {'', '', ','});
disp(y2_array);

disp(" ")
disp("Copy these values and paste them in the Arduino code between the { } brackets for each x and y array");

