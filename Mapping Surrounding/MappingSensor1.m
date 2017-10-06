%%%%%
% Created by Evert Eduard Poots
% Data: 05-10-2017
%%%%%
close all;
clear all;
clc;

R = 10:10:100; % Distance measured by the ultrasonic sensor.
theta = 0:10:90; % Angle measured by the gyroscope of the drone.

x1 = R.*cosd(theta); % X coördinate.
y1 = R.*sind(theta); % Y Coördinate.

% [x,y] = meshgrid(x1,y1); % Creates a matrix of the x and y coördiantes.

% Create plot in figure.
figure(1);
scatter(x1(:), y1(:), 'x','linewidth',2)
grid on;
xlabel("X distance in centimeter");
ylabel("Y distance in centimeter");
title("2D map of the front sensor");

% Prints the coördinates (R, theta).
for k = 1:numel(x1)
    text(x1(k),y1(k),['  (' num2str(R(k)) ',' num2str(theta(k)) ')'])
end