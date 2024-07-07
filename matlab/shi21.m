t = -3 : 0.01 : 5
function res = xt(time)
    res = exp(-0.5 * time) .* heaviside(time)
end

subplot(1, 2, 1)
plot(t, xt(t))
title ('exp2_1_real')
xlabel('t')

subplot(1, 2, 2)
plot(t, xt(1.5 * t + 3))
title ('exp2_1_real')
xlabel('t')