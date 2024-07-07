t=-2:0.01:2;
sid=25;
f=heaviside(t+1)-heaviside(t-1);
subplot(3,3,1);
plot(t,f)
title('f信号图');
axis([-2,2,-0.1,1.1])% 界限
grid on
%幅度谱
f0=str2sym('heaviside(t+1)-heaviside(t-1)');
Fw=fourier(f0);
subplot(3,3,2);
tmp=abs(Fw);
fplot(abs(Fw));
title('f的幅度谱');
axis([-10,10,-0.1,2.1])% 界限
grid on


%相位谱
phase=atan(imag(Fw)./real(Fw));
subplot(3,3,3);
fplot(phase)
title('f的相位谱');
axis([-10,10,-1,1])% 界限
grid on

%绘制加入学号(/)的频谱图
ft1=str2sym('heaviside(t/10+1)-heaviside(t/10-1)');
Fw1=fourier(ft1);% 傅里叶变换
subplot(3,3,4)% 子图
fplot(abs(Fw1))% 求幅度
title('幅度谱ft1')
axis([-10,10,-0.1,4.1])% 界限
grid on
% 相位谱
phase1=atan(imag(Fw1)./real(Fw1));
subplot(3,3,5)
fplot(phase1)
title('相位谱ft1')
grid on

%绘制加入学号(*)的频谱图
ft2=str2sym('heaviside(t*10+1)-heaviside(t*10-1)');
Fw2=fourier(ft2);% 傅里叶变换
subplot(3,3,7)% 子图
fplot(abs(Fw2))% 求幅度
title('幅度谱ft2')
axis([-10,10,-0.1,1.1])% 界限
grid on
% 相位谱
phase2=atan(imag(Fw2)./real(Fw2));
subplot(3,3,8)
fplot(phase2)
title('相位谱ft2')
grid on