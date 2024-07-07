% 定义信号 f(t) 的傅里叶变换 F(jw)
F = @(w) (2*cos(w)-2*cos(2*w))./w.^2;

% 设置频率范围
w = linspace(-10, 10, 1000);

% 计算傅里叶变换结果
FT = F(w);

% 绘制频谱图
figure;
plot(w, abs(FT));
xlabel('频率');
ylabel('幅度');
title('f(t) 的频谱图');

% 验证时域卷积定理
% 定义门函数
rect = @(t, T) (abs(t) <= T/2);

% 定义三角波信号
tri = @(t, T) (1 - abs(mod(t, T) - T/2) * 4 / T);

% 设置时间范围
t = linspace(-10, 10, 1000);

% 计算门函数的傅里叶变换
FT_rect = @(w, T) T * sinc(w*T/2);

% 计算三角波信号的傅里叶变换
FT_tri = @(w, T) (sinc(w*T/2).^2) .* exp(-1i*w*T/2);

% 计算门函数和三角波信号卷积的傅里叶变换
FT_conv = @(w, T) FT_rect(w, T) .* FT_tri(w, T);

% 设置卷积的时间范围
t_conv = linspace(-20, 20, 2000);

% 计算门函数和三角波信号卷积的结果
conv_result = ifftshift(ifft(fft(rect(t_conv, 2)).*fft(tri(t_conv, 2))));

% 计算卷积结果的傅里叶变换
FT_conv_result = fftshift(fft(conv_result));

% 重新设置频率范围
w_conv = linspace(-10, 10, length(FT_conv_result));

% 绘制卷积结果的频谱图
figure;
plot(w_conv, abs(FT_conv(w_conv, 2)), 'r', w_conv, abs(FT_conv_result), 'b--');
xlabel('频率');
ylabel('幅度');
legend('理论结果', '实际结果');
title('门函数和三角波信号卷积的频谱图');