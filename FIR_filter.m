fs=10000;
f=(0:0.01:5000);
omega=2*pi*f/fs;
H=(1/10)./(1-(0.9*exp(-omega*j*1)));
plot(f,abs(H))

saveas(gcf, "filer\plot.png")