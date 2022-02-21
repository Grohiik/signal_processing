fs=10000;
f=(0:0.01:5000);
omega=2*pi*f/fs;
H=1/4+1/4*exp(-i*omega)+1/4*exp(-i*omega*2)+1/4*exp(-i*omega*3);
plot(f,abs(H))
