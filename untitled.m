f = 250;

t = [0:0.0000001:pi/300];

y = cos(2*pi*f*t)-(1/3*cos(2*pi*3*f*t))+(1/5*cos(2*pi*5*f*t))-(1/7*cos(2*pi*7*f*t))+(1/9*cos(2*pi*9*f*t));

plot(t,y)