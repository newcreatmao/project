% 清除变量和关闭所有图形窗口
clear;
close;

% 设置时间范围和采样频率
t = -5:0.01:5;% 时间范围
fs = 1/(t(2)-t(1));% 采样频率

% 信号1: f1(t) = sin(2π(t-1))/(π(t-1))
f1 = sin(2*pi*(t-1))./(pi*(t-1));
f1(isnan(f1)) = 1; % 用1替代零除错误处的NaN值

% 计算信号1的傅里叶变换
F1=fftshift(fft(f1));

% 计算频谱和相位谱
frequencies = (-fs/2):(fs/length(t)):(fs/2-fs/length(t));
spectrum = abs(F1);
phase = angle(F1);

% 绘制信号1的频谱图和相位图
figure;
subplot(2,1,1);
plot(frequencies, spectrum);
xlabel('频率');
ylabel('幅度');
title('信号1的幅度谱');

subplot(2,1,2);
plot(frequencies, phase);
xlabel('频率');
ylabel('相位');
title('信号1的相位谱');

% 信号2: f2(t) = [sin(πt)/(πt)]^2
f2 = (sin(pi*t)./(pi*t)).^2;
f2(isnan(f2)) = 0; % 用0替代零除错误处的NaN值

% 计算信号2的傅里叶变换
F2 = fftshift(fft(f2));

% 计算频谱和相位谱
frequencies = (-fs/2):(fs/length(t)):(fs/2-fs/length(t));
spectrum = abs(F2);
phase = angle(F2);

% 绘制信号2的频谱图和相位图
figure;
subplot(2,1,1);
plot(frequencies,spectrum);
xlabel('频率');
ylabel('幅度');
title('信号2的幅度谱');

subplot(2,1,2);
plot(frequencies,phase);
xlabel('频率');
ylabel('相位');
title('信号2的相位谱');