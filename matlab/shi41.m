% 定义主值序列
x = [0, 1, 2, 3, 2, 1, 0];

% 填充两个周期的序列
x_extended = repmat(x, 1, 2);

% 计算傅里叶级数系数
X = fft(x_extended);

% 计算幅度谱和相位谱
amplitude = abs(X);
phase = angle(X);

% 进行傅里叶级数逆变换
reconstructed_x = ifft(X);

% 绘制两个周期的序列波形、幅度谱和相位谱，以及逆变换后的序列
n = 0:length(x_extended)-1;

figure;
subplot(4, 1, 1);
stem(n, x_extended);
xlabel('n');
ylabel('x(n)');
title('两个周期的序列波形');

subplot(4, 1, 2);
stem(n, amplitude);
xlabel('频率');
ylabel('幅度');
title('幅度谱');

subplot(4, 1, 3);
stem(n, phase);
xlabel('频率');
ylabel('相位');
title('相位谱');

subplot(4, 1, 4);
stem(n, real(reconstructed_x));
hold on;
stem(n, x_extended, 'r--');
hold off;
xlabel('n');
ylabel('信号值');
title('逆变换结果与原序列比较');
legend('逆变换结果', '原序列');