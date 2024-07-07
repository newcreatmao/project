frequencies = -10:0.01:10; % 频率范围
N = length(frequencies);   % 采样点数

% 傅里叶变换的频谱
F1 = 10./(3 + 1i*frequencies) - 4./(5 + 1i*frequencies);
F2 = exp(-4*frequencies).^2;

% 计算信号1的傅里叶反变换
f1 = ifftshift(ifft(F1, N));

% 计算信号2的傅里叶反变换
f2 = ifftshift(ifft(F2, N));

% 绘制信号1的时域信号图
figure;
subplot(2,1,1);
plot(frequencies, real(f1));
xlabel('时间');
ylabel('幅度');
title('信号1的时域信号图 (实部)');

subplot(2,1,2);
plot(frequencies, imag(f1));
xlabel('时间');
ylabel('幅度');
title('信号1的时域信号图 (虚部)');

% 绘制信号2的时域信号图
figure;
subplot(2,1,1);
plot(frequencies, real(f2));
xlabel('时间');
ylabel('幅度');
title('信号2的时域信号图 (实部)');

subplot(2,1,2);
plot(frequencies, imag(f2));
xlabel('时间');
ylabel('幅度');
title('信号2的时域信号图 (虚部)');