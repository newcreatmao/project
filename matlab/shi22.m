x=-5:0.1:5;
y=sign(x);
y(y==0)=0.5

plot(x,y)
axis([-5,5,-1.5,1.5])
xlabel('t')
ylabel('u(t)')
title('单位阶跃函数')