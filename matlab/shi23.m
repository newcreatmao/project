t=-8:0.01:8;
x1=rectpuls(t)
x=0
for i=-6:2:6;
    x=x+rectpuls(t+i,1)
end

subplot(2,1,1)
plot(t,x1)
title('x1(t)')
xlabel('t')
axis([-2,2,-0.2,1.2])
grid on
subplot(2,1,2)
plot(t,x)
title('x(t) ')
xlabel('t')
axis([-7,7,-1,2])
grid on