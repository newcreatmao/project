t = 0 : 0.1 : 20
y = exp((-0.1 + (pi / 4) * i) .* t)
subplot(2,2,1)
stem(t, real(y), 'filled')
title ('exp1_2_real')
xlabel('t')

subplot(2,2,2)
stem(t, imag(y), 'filled')
title ('exp1_2_imag')
xlabel('t')

subplot(2,2,3)
stem(t, abs(y), 'filled')
title ('exp1_2_abs')
xlabel('t')

subplot(2,2,4)
stem(t, angle(y), 'filled')
title ('exp1_2_angle')
xlabel('t')

grid on