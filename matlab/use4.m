syms t
Fw=str2sym('1/(1+w^2)');
ft=ifourier(Fw,t);
fplot(ft);% 绘制函数
axis([-10,10,0,0.5])% 绘制上下限
grid on% 绘制网格
title('Fw时域信号图');% 标题