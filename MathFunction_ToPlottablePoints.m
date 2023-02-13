%MathFunction_ToPlottablePoints.m
%Written by Matt Nichols (nichols.809) for the OSU Electronics Club
%February 12, 2023

%% Take a math function and plot it, then rescale output to 0-255 for x and y

t = 0:0.1:10;
x = 16*sin(t).^3
y = 13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t)



x1 = interp1([min(x), max(x)], [0,255], x);
y1 = interp1([min(y), max(y)], [0,255], y);


plot(x1,y1)

%% Generate the arrays for the arduino code

num_points = size(x1, 2);
disp("Num points = ");
disp(num_points);

x1 = round(x1);
disp("The x-value points are: ")
x1_array = regexprep( mat2str(x1), {'\[', '\]', '\s+'}, {'', '', ','});
disp(x1_array);

disp(" ")

y1 = round(y1);
disp("The y-value points are: ")
y1_array = regexprep( mat2str(y1), {'\[', '\]', '\s+'}, {'', '', ','});
disp(y1_array);

disp(" ")
disp("Copy these values and paste them in the Arduino code between the { } brackets for each x and y array");

