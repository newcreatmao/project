stm32：st：意法半导体	m：mcu/mpu	32：32位

st中文社区网：https://www.stmcu.org.cn

官网: https//www.st.com

![image-20230529200831878](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230529200831878.png)

选型：由高到低，由大到小

### 查看数据手册

从官网和社区网通过型号搜索下载即可

基本参数，工作电压，最大电流，io引脚的接入电压范围（coms端口，兼容5v端口），单个io的最大电流

最小系统和io口

![image-20230623114002483](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230623114002483.png)

选择启动文件，

![image-20230623114237066](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230623114237066.png)

创建文件的步骤

![image-20230623114541112](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230623114541112.png)





#### 定时器

![image-20230710151205480](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710151205480.png)

基本定时器

![image-20230710151501277](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710151501277.png)

实际分频系数=预分频器的值（范围为[0,65535]）+1

计数器范围为（【0，65535】），从0开始自增运行到目标值（即自动重装载寄存器，小于65535）时产生中断，且数值从0重新开始

UI表示产生中断信号（更新中断）会触发中断，u表示产生事件（更新事件）不会触发中断，但能触发内部其他电路的工作



通用定时器

![image-20230710152646565](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710152646565.png)

计数器有三种模式：

从0递增到重装值，从重装值递减到0，中央对齐模式即结合以上两种，先增后减



内外时钟源选择：

基本定时器只能选择内部时钟，即系统频率72MHz

通用·可选择内部也可选外部

ETR：配置外部时钟后配置一下外部时钟设置后即可

TRGI：触发输入，可看作外部时钟输入模式，ETR与ITR

定时器的级联，如TIM1的TRGO->TIM2的ITRO，则TIM2可以使用TIM1的时基单元

![image-20230710154402198](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710154402198.png)

![image-20230710154436734](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710154436734.png)

五种方式配置定时器

（触发输出）TRGO可映射定时器的时间，如更新事件



高级定时器

![image-20230710154817488](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710154817488.png)

1. 增加重复次数计时器，可实现每隔几个周期才发生一次更新事件和更新中断，相当于对输出信号又分了一次频
2. DTG：死区生成电路（开关切换瞬间产生一定时长的死区，防止直通现象），引出两个波型为互补的PWM波，用于驱动三项无刷电机
3. 刹车输入功能：保护电机

![image-20230710155954630](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710155954630.png)

配置流程

![image-20230710161906984](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710161906984.png)

在周期未结束时改变分频值，stm32会继续原来的分频结束该周期后在下一周期改变

计数器计数频率：CK_CNT=CK_PSC/(PSC+1)

![image-20230710162552934](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710162552934.png)

时间=1/频率

![image-20230710162801165](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710162801165.png)

未配置缓冲寄存器（让值的变化和更新事件同步发生）

![image-20230710162848298](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710162848298.png)

##### 时钟树

![image-20230710163558134](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230710163558134.png)

HSL提供系统时钟

一般来说外部石英振荡器更精准





### 32与pwm

![image-20230712215404638](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712215404638.png)

0往上走，信号不反转

1往下走，通过非门取反，输出反转信号

![image-20230712215610174](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712215610174.png)

直接认为高电频为有效电频，低电频是无效电频

CNT（计数寄存器）与CCR（捕获/比较寄存器）：小于有效，大于无效，等于为变化后输出

PWM1=~PWM2

PWM1配置流程：

![image-20230712220339227](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712220339227.png)

时钟源选择->时基单元配置->输出比较单元->配置GPIO口

输出PWM暂时不需要中断

蓝色线：CNT，红色线：CCR，黄色线：ARR，绿色线：输出

![image-20230712222220653](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712222220653.png)

psc（预分频器）CNT（计数寄存器）CCR（捕获/比较寄存器）

![image-20230712222518719](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712222518719.png)

死区：避免上下管同时导通

![image-20230712223115259](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712223115259.png)

![image-20230712224916870](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230712224916870.png)



### TIM输入捕获

CNT锁存到ccr

计数值存储到ccr再反馈给cpu

高级和通用电路都一样，无区别，普通定时器没有该功能



![image-20230713152111811](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230713152111811.png)

测频法：高频信号，较准确，测量时间长，测周法：低频信号，测量时间取决于周期长度，测量受影响较大

fm越靠近哪边就选哪个

![image-20230715165618425](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230715165618425.png)

![image-20230715165754192](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230715165754192.png)

![image-20230715165828870](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230715165828870.png)

可同时测量占空比（CCR2/CCR1）和频率



###### TIM编码器

![image-20230716091016790](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716091016790.png)

![image-20230716203555841](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716203555841.png)

输入部分

![image-20230716203707727](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716203707727.png)

从模式

![image-20230716203826207](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716203826207.png)

![image-20230716204415730](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716204415730.png)

均不反向

![image-20230716204903417](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716204903417.png)

###### ADC和DAC

![image-20230720195526549](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720195526549.png)

1MHZ，32的最大频率

###### 串口

![image-20230722160142696](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722160142696.png)

单端需要GND接口共地

差分则通过引脚间的电压差，不需要接口，课极大提高抗干扰特性



![image-20230722161846455](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722161846455.png)

数据低位先行，奇偶·校验

![image-20230722162956213](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722162956213.png)

1/9600=104us对于这个（看波特率的计算）

tx引脚输出定时翻转的高低电平

rx引脚定时读取引脚的高低电平



![image-20230725125522573](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725125522573.png)

![image-20230725125835509](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725125835509.png)

![image-20230725130414540](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725130414540.png)

![image-20230725130754775](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725130754775.png)



![image-20230725131542823](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725131542823.png)

![image-20230725132708008](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725132708008.png)

###### hex与文本模式

![image-20230725151909054](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725151909054.png)

以ascll码为准

输出汉字第一种![image-20230725153449682](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725153449682.png)

第二种

![image-20230725153621511](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725153621511.png)

GBK

#### 串口发送数据包

###### 规定数据包格式

![image-20230725200838047](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725200838047.png)

定包头包尾，中间为数据

！编程思路：防止数据与包头包尾重复

![image-20230725201607078](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725201607078.png)

文本灵活一点不用担心重复

![image-20230725201814187](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725201814187.png)

![image-20230725201825082](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230725201825082.png)

状态机

###### I2C

实现与外挂芯片进行收发操作

SCL：使用同步的时序，降低对硬件的依赖

SDA：变全双工为半双工，一根线兼具收发模式，实现资源优化

