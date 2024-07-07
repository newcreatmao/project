% 定义时间范围
t=0:0.01:10;

% 计算第一个信号
x1=(1-exp(-10.*0.1.*t)).*heaviside(t);

% 计算第二个信号
x2=(1-exp(-10.*0.1*t)).*heaviside(t-2);

% 绘制信号波形
figure;
subplot(2,1,1);
plot(t,x1);
xlabel('t');
ylabel('x1(t)');
title('信号x1(t)');

subplot(2,1,2);
plot(t,x2);
xlabel('t');
ylabel('x2(t)');
title('信号x2(t)');