% 定义有限长序列
x = [1, 0.5, 0, 0.5, 1, 1, 0.5, 0];

% 求该序列的DFT和IDFT的图形
N = length(x); % 序列长度
X = fft(x); % DFT
reconstructed_x = ifft(X); % IDFT

% 绘制DFT和IDFT的图形
figure;
subplot(2, 1, 1);
stem(0:N-1, abs(X));
xlabel('频率');
ylabel('幅度');
title('DFT幅度谱');

subplot(2, 1, 2);
stem(0:N-1, angle(X));
xlabel('频率');
ylabel('相位');
title('DFT相位谱');

figure;
subplot(2, 1, 1);
stem(0:N-1, real(reconstructed_x));
hold on;
stem(0:N-1, x, 'r--');
hold off;
xlabel('n');
ylabel('信号值');
title('IDFT结果与原序列比较');
legend('IDFT结果', '原序列');

% 用FFT算法求该序列的DFT和IDFT的图形
X_fft = fft(x, N); % FFT算法求DFT
reconstructed_x_fft = ifft(X_fft); % FFT算法求IDFT

% 绘制FFT算法求得的DFT和IDFT的图形
figure;
subplot(2, 1, 1);
stem(0:N-1, abs(X_fft));
xlabel('频率');
ylabel('幅度');
title('FFT幅度谱');

subplot(2, 1, 2);
stem(0:N-1, angle(X_fft));
xlabel('频率');
ylabel('相位');
title('FFT相位谱');

figure;
subplot(2, 1, 1);
stem(0:N-1, real(reconstructed_x_fft));
hold on;
stem(0:N-1, x, 'r--');
hold off;
xlabel('n');
ylabel('信号值');
title('FFT逆变换结果与原序列比较');
legend('FFT逆变换结果', '原序列');

% 假定采用频率Fs=20Hz，计算序列长度N分别为8、32和64的幅度谱和相位谱
Fs = 20; % 采样频率

% N=8的幅度谱和相位谱
N = 8;
t = (0:N-1) / Fs; % 时间序列
x_N8 = [1, 0.5, 0, 0.5, 1, 1, 0.5, 0];
X_N8 = fft(x_N8, N); % FFT计算DFT
amplitude_N8 = abs(X_N8);
phase_N8 = angle(X_N8);

figure;
subplot(2, 1, 1);
stem(0:N-1, amplitude_N8);
xlabel('频率');
ylabel('幅度');
title('N=8时的幅度谱');

subplot(2, 1, 2);
stem(0:N-1, phase_N8);
xlabel('频率');
ylabel('相位');
title('N=8时的相位谱');

% N=32的幅度谱和相位谱
N = 32;
t = (0:N-1) / Fs; % 时间序列
x_N32 = [1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0];
X_N32 = fft(x_N32, N); % FFT计算DFT
amplitude_N32 = abs(X_N32);
phase_N32 = angle(X_N32);

figure;
subplot(2, 1, 1);
stem(0:N-1, amplitude_N32);
xlabel('频率');
ylabel('幅度');
title('N=32时的幅度谱');

subplot(2, 1, 2);
stem(0:N-1, phase_N32);
xlabel('频率');
ylabel('相位');
title('N=32时的相位谱');

% N=64的幅度谱和相位谱
N = 64;
t = (0:N-1) / Fs; % 时间序列
x_N64 = [1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0, 1, 0.5, 0, 0.5, 1, 1, 0.5, 0];
X_N64 = fft(x_N64, N); % FFT计算DFT
amplitude_N64 = abs(X_N64);
phase_N64 = angle(X_N64);

figure;
subplot(2, 1, 1);
stem(0:N-1, amplitude_N64);
xlabel('频率');
ylabel('幅度');
title('N=64时的幅度谱');

subplot(2, 1, 2);
stem(0:N-1, phase_N64);
xlabel('频率');
ylabel('相位');
title('N=64时的相位谱');