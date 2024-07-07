t = -1 : .01 : 4;
y = exp(-2 * t) .* cos(3 * pi .* t .* (heaviside(t) - heaviside(t - 3)));
plot(t, y)
title ('exp1_1')
xlabel('t'), ylabel('y')
grid on