[toc]

# 简介

[官网](https://opencv.org/releases/#)

[c++ opencv vs配置](https://blog.csdn.net/m0_47472749/article/details/111328183)

![image-20230804135843995](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804135843995.png)

![image-20230804135945083](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804135945083.png)

![image-20230804140146818](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804140146818.png)

数字图像

## 基础

### Mat类

存储矩阵类型的数据

![image-20230804152203434](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804152203434.png)

#### Mat数据类型

[通道的理解](https://blog.csdn.net/gdfsg/article/details/50927257)

![image-20230804152627360](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804152627360.png)

#### Mat的创建

![image-20230804152738907](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804152738907.png)

通道每个位置下放几个数

![image-20230804155223654](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804155223654.png)

![image-20230804152901780](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804152901780.png)

![image-20230804153000713](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804153000713.png)

#### Mat类的赋值

###### ![image-20230804153236681](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804153236681.png)

![image-20230804153619394](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804153619394.png)

![image-20230804153818280](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804153818280.png)

#### Mat类的基础信息

![image-20230804155350555](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804155350555.png)

3 * 3 * 3（相当于通道）->3*9   BGR的排列

![image-20230804155506007](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804155506007.png)

#### Mat类取数据

![image-20230804155705180](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804155705180.png)

at<数据类型>选取范围

多通道取值的一般步骤即先取其中一个通道下的元素（如3通道则取出3个元素放入一个Mat类中），再对该元素进行处理

![image-20230804155958938](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804155958938.png)

![image-20230804160224669](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804160224669.png)

读取的数据会根据不同的转换类型而不同，否则按ascll码输出对应字符

#### Mat类的相关运算（符合矩阵的运算性质）

![image-20230804163518602](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804163518602.png)

需要保证两个Mat类的尺寸大小数据类型都一样即两个矩阵相等

注意：对于Mat和其他数据类型的操作均为全部元素都与该数进行操作，如i=a-1即为a中元素全部-1得到i

![image-20230804163835949](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804163835949.png)

乘积是矩阵，内积是数值，

![image-20230804164203943](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804164203943.png)

## 图像处理

![image-20230804170040943](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804170040943.png)

![image-20230804170126479](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804170126479.png)



```c++
resizeWindows(name,width,height)
destroyAllWindows()
```

nameWindow（）可能不会自动释放空间，需要breakdown相关函数

![image-20230804170907127](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804170907127.png)

![image-20230804171419398](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804171419398.png)

官网直接搜索

#### 视频处理

int waitKey（）读取键盘键值

![image-20230804173236779](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804173236779.png)

![image-20230804173347294](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804173347294.png)

![image-20230804173542357](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804173542357.png)

#### 图像颜色空间

![image-20230804175233552](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804175233552.png)

##### RGB(红绿蓝)

![image-20230804175009892](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804175009892.png)

每个通道的取值范围都是0-255

##### HSV

![image-20230804175431005](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804175431005.png)

##### 灰度

![image-20230804175531882](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804175531882.png)

只能由彩色转化为灰色

![image-20230804175823069](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804175823069.png)



参数可去官网搜索

COLOR_（）2（）

### image watch

插件，调试过程使用

#### 多通道的分离与合并

![image-20230804191630254](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804191630254.png)

![image-20230804191758925](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804191758925.png)

#### 图片像素对比

![image-20230804203944781](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804203944781.png)

![image-20230804204126681](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804204126681.png)

可用于像素筛选

![image-20230804204311241](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804204311241.png)

##### mask掩码矩阵，可按其选择指定区域 

[掩码矩阵](https://blog.csdn.net/chenjiazhou12/article/details/21092847?ops_request_misc=%7B%22request%5Fid%22%3A%22169115544816777224439642%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=169115544816777224439642&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-21092847-null-null.142^v92^chatgptT0_1&utm_term=opencv掩码矩阵&spm=1018.2226.3001.4187)

##### 像素的逻辑运算

![image-20230804210603168](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804210603168.png)

![image-20230804211133081](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804211133081.png)



![image-20230804211358076](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804211358076.png)

#### 图像二值化（二值即max，min）

![image-20230804213600277](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804213600277.png)

![image-20230804214153490](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804214153490.png)

二值化方法：THRESH_OTSV大精算法，THERESH_TRIAXGLE三角形算法

![image-20230804220258592](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804220258592.png)

BINARY大于阈值置为0，小于不变

自适应只支持灰度图的处理

#### LUT查找表

![image-20230804221456697](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804221456697.png)

8U：0-255

## 图像操作

### 缩放

![image-20230804222907549](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230804222907549.png)

问题由来：两个映射到同一个上怎么选，相邻两个映射后中间隔开又应填什么值

插值：根据已有像素推测未知像素

最邻近法：谁近就是谁

线性插值法：最近的几点任意两点构建一次函数，选取未知点的坐标投影

双线性插值法：多条的投影点连线再投影

![image-20230805133008449](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805133008449.png)

不用Size则穿个空即可

### 翻转

![image-20230805133143550](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805133143550.png)

### 拼接

![image-20230805133236858](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805133236858.png)

### 仿射变换

![image-20230805134536679](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805134536679.png)

![image-20230805134847681](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805134847681.png)

![image-20230805135107760](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805135107760.png)

![image-20230805135216089](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805135216089.png)

### 图像的透视变换

![image-20230805154424108](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805154424108.png)

![image-20230805154605733](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805154605733.png)

![image-20230805154708602](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805154708602.png)

![image-20230805154741455](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805154741455.png)

可用于抠图

### 在图像中绘制

#### 直线

![image-20230805155651983](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805155651983.png)

#### 圆形

![image-20230805163342026](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805163342026.png)

thickness为-1时代表填充

#### 椭圆

![image-20230805163701481](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805163701481.png)

#### 矩形

![image-20230805164129691](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805164129691.png)

#### 多边形

![image-20230805164221124](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805164221124.png)

#### 生成文字

![image-20230805164533577](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805164533577.png)

现环境支持中文

### 图像截取（copy）

![image-20230805165621559](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805165621559.png)

![image-20230805170935507](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805170935507.png)

深拷贝重新申请内存

浅拷贝相当于引用

### 高斯图像金字塔

![image-20230805171711746](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805171711746.png)

![image-20230805172850327](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805172850327.png)

尺寸缩小

### 拉普拉斯图像金字塔

![image-20230805173608285](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230805173608285.png)

高斯模糊就是下采样的过程

![image-20230808143038294](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808143038294.png)

### 创建滑动条

![image-20230808144350215](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808144350215.png)



### 鼠标

![image-20230808145943979](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808145943979.png)

![image-20230808150001445](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808150001445.png)

![image-20230808150759890](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808150759890.png)

瞬间

![image-20230808150816107](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808150816107.png)

长时间

### 直方图统计

![image-20230808155540389](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808155540389.png)

### 统计图像中像素点的数量

![image-20230808160641212](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808160641212.png)

#### 制作图表

![](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808160908572.png)

归一化

###### 均衡化

![image-20230815161422290](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815161422290.png)

只有单通道图像才有均衡化

均衡化即将原图像直方图得分布形式平均

###### 匹配

即将图像直方图特定在某个区域表示

![image-20230815162216205](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815162216205.png)

累积概率小于运算时，从别处映射像素值来调高概率

通过计算原累计概率与目标图像的累计概率的差值来确定映射关系，如0->3

![image-20230815163235578](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815163235578.png)

![image-20230815163507978](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815163507978.png)

##### 模板匹配

![image-20230815163852480](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815163852480.png)

在目标图像中匹配模板图像

![image-20230815164155576](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815164155576.png)

![image-20230815164357798](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815164357798.png)

#### 图像卷积

![image-20230815164930056](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815164930056.png)

中心位置矩阵相乘

归一化：求出的值除以模板元素之和

![image-20230815165734561](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815165734561.png)

![image-20230815165839147](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815165839147.png)

基准点即中心点

偏值即在超出范围除添加的像素点

### 图像噪声

![image-20230815170150937](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815170150937.png)

![image-20230815170329494](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815170329494.png)

![image-20230815170711844](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815170711844.png)

#### 滤波

##### 线性滤波

###### 均值

![image-20230815171023680](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815171023680.png)



![image-20230815171306567](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815171306567.png)

常用卷积核为奇数方阵

###### 方框

![image-20230815171441847](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815171441847.png)

允许卷积核不进行归一化

###### 高斯

![image-20230815171610940](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815171610940.png)

正态分布

![image-20230815171647235](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815171647235.png)

#### 非线性滤波

###### 中值滤波

![image-20230815172142893](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815172142893.png)

![image-20230815172235322](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815172235322.png)

#### 滤波可分离

![image-20230815172640519](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815172640519.png)

分为x，y方向的滤波操作

![image-20230815172917935](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815172917935.png)

### 边缘检测

#### 原理

![image-20230815173309745](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815173309745.png)



#### sobel算子边缘检测

![image-20230815173621173](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815173621173.png)

推荐使用16s形式

#### scharr算子边缘检测

![image-20230815173941784](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815173941784.png)



以上两种算法都需要分别进行计算



#### 算子生成

![image-20230815174036674](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815174036674.png)

#### laplacian算子

![image-20230815184210899](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815184210899.png)

直接提取各方向的计算值

![image-20230815184418392](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815184418392.png)



滤波器默认3*3



#### canny算子

![image-20230815184612625](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815184612625.png)

![image-20230815185003761](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815185003761.png)

### 连通域（某个区域内所有的像素是相邻的）

![image-20230815185211442](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815185211442.png)

![image-20230815185852846](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815185852846.png)

![image-20230815190037079](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815190037079.png)

![image-20230815190206776](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230815190206776.png)

### 图像距离变换

![image-20230816114048732](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816114048732.png)

dist_L1																dist_L2															dist_C

![image-20230816114314013](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816114314013.png)

#### 形态学

##### 图像腐蚀

![image-20230816115823952](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816115823952.png)

![image-20230816115945377](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816115945377.png)

![image-20230816120132133](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816120132133.png)

![image-20230816132047771](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816132047771.png)

##### 图像膨胀

![image-20230816133214672](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816133214672.png)

![image-20230816133410608](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816133410608.png)

##### 应用

###### 开运算

![image-20230816133644745](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816133644745.png)

###### 闭运算

![image-20230816133846626](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816133846626.png)

###### 形态学梯度

![image-20230816133903290](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816133903290.png)

###### 顶帽运算

![image-20230816133945158](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816133945158.png)

###### 黑帽运算

![image-20230816134022360](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816134022360.png)

###### 集中击不中变换

![image-20230816134126562](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816134126562.png)

###### 操作

![image-20230816134357634](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816134357634.png)

![image-20230816134423396](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816134423396.png)

#### 图像细化

![image-20230816134643498](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816134643498.png)

![image-20230816135010128](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816135010128.png)

要重新添加库路径（p40）

![image-20230816135452470](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816135452470.png)

实心的会变成点，字母文字等不变

### 轮廓的操作

![image-20230816135932829](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816135932829.png)

##### 轮廓检测

![image-20230816140311884](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816140311884.png)

##### 绘制轮廓

![image-20230816140530246](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816140530246.png)

##### 轮廓信息

###### 面积

![image-20230816140821711](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816140821711.png)

###### 长度

![image-20230816141100497](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816141100497.png)

##### 轮廓多边形拟合

![image-20230816141656462](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816141656462.png)

##### 凸包检测

![image-20230816143032318](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816143032318.png)

![image-20230816143128951](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816143128951.png)

##### 直线检测

![image-20230816143544480](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816143544480.png)

![image-20230816143657535](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816143657535.png)

![image-20230816143742412](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816143742412.png)

![image-20230816143845184](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816143845184.png)

![image-20230816144317286](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816144317286.png)

### 点集操作

#### 点集拟合

###### 直线拟合

![image-20230816150232495](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816150232495.png)

![image-20230816150357758](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816150357758.png)

![image-20230816150437127](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816150437127.png)

### 二维码检测

![image-20230816200514987](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816200514987.png)

位置探测图形要满足11311的规律（1黑，1白，3黑，1白，1黑）

![image-20230816201038333](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816201038333.png)

![image-20230816201238398](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816201238398.png)

### 积分图像

![image-20230816201722195](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816201722195.png)

即数据求和

![image-20230816201959619](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816201959619.png)

### 图像分割

#### 漫水填充

![image-20230816202055061](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202055061.png)

![image-20230816202150435](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202150435.png)

#### 分水岭法

![image-20230816202330046](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202330046.png)

![image-20230816202445568](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202445568.png)

### Harris角点

![image-20230816202715187](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202715187.png)

![image-20230816202809917](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202809917.png)

![image-20230816202944319](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816202944319.png)

![image-20230816203012679](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230816203012679.png)

### Tomas角点

![image-20230821210721653](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230821210721653.png)

![image-20230821210941423](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230821210941423.png)

### 角点位置亚像素位置优化

![image-20230821211302601](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230821211302601.png)

![image-20230821211354574](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230821211354574.png)