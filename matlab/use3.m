clc
N = 7; %  采样点数为7
xn = [0,1,2,3,2,1,0]; % 序列波形
xn = [xn,xn]; % 两个周期序列
n = 0:2*N-1; % 定义n(长度为xn)
k = 0:2*N-1; % 定义k(长度为xn)
xk = xn*exp(-1i*2*pi/N).^(n'*k); % 离散傅里叶级数变换
x = (xk*exp(1i*2*pi/N).^(n'*k))/N; % 离散傅里叶数逆变换
subplot(2,2,1) % 建立视图(1)
stem(n, xn); % 绘制离散序列数据
title('x(n)-原序列'); % 图形标题
grid on % 网格
% IDFS图
subplot(2,2,2) % 建立视图(2)
stem(n, abs(x)); % 离散序列
% 标题
title('IDFS|x(k)|-逆变换')
grid on % 网格
% 幅度谱
subplot(2,2,3) % 建立视图(3)
stem(k,abs(xk)); % 幅度
% 标题
title('|x(k)|-幅度谱');
grid on
% 相位谱
subplot(2,2,4)
stem(k, angle(xk)) % 相位谱
% 标题
title('angle|x(k)|-相位谱')
grid on