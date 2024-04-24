[toc]

#### use cmd windows

#### creat a txt.py to do more py says



#### 退出解析器

exit();

#### 字面量

字符串（用“”包围起来），整型，浮点型（小数）

整数，浮点数直接写，字符串用“”包围

#### print

print(444)

print(13.14)

print("")

不换行：在结尾加上end=''

\t自动对齐,tab键

\n换行

#### 注释

1. 单行：用#开头即可
2. 多行：“”“开头，”“”结尾即可

#### 变量

a=12

print("",a,"")

a=a-10 or a-=10

#### 数据类型

type(查看的数据)

print(type(444))

a=type(444)

type(a)

###### 类型转化

int(x)把x转换为int型

float()

str()

#### 标识符

英文，中文，数字，下划线

#### 运算符

+，-，*，/，//（取整除），***（指数）

=，+=，-=，*=，/=，//=，***=

%求余

#### 字符串的定义

‘单引号定义法‘

”双引号定义法“（通用）

”“”三引号定义法“”“

转义字符"\\"可解除

如：”\“mao”

#### 字符串的拼接

print("kkk"+"mmm")

mao="lll"

print("kkk"+mao+"mmm")

注意只能字符串能用这个办法

#### 字符串格式化

mane="kkk"

l=13

m=13.2

mao="mmm%s%d%6.2f"%(mane,l,m)

mmmkkk13 13.20

方法2

print(f"mmm{mane}"+"kkk{l}"+"ooo{m}")

#### 表达式格式化

print("%s"%(1+2))

print(f"{2+2}")

print("%s"%type(''))

#### 数据的输入(input)

mao=input()

mao=input("请告诉我你是谁?")

无论什么都是字符串,要转化

mao=int(input())

#### 判断

##### bool类型

true为真->1

false->0

a=true

a=10>5->a=true

==,<=,>=,!=,<,>

##### if语句

多条件时用and，or，elif

if 要判断的条件:

条件成立时要执行的操作

多句情况（看缩进）

if a>=100:

  print

  print

print

前两个在if语句下，后面一个在外面

true执行，false不执行

###### if else

if a>100:

   print

   print

else :

  print

  print

###### if elif else

if 条件一:

  print

elif 条件二:

  print

elif 条件三:

  print

else:

判断互斥且有顺序

#### 随机数

import random

num=random.randint(1,10),1到10的随机数

#### 循环语句

###### while

while 条件:

  print

  print

  print

true继续，false结束

空格缩进决定层次关系

###### for

mane=mao

for x in mao:

  print(x)

得到

m

a

o

依次输出,无法定义循环条件，相当于遍历字符串

for 临时变量in 待处理的序列类型(字符串，列表，元组等):

  满足·条件执行的代码

for循环完全结束后可以加上一个else，当前仅有完全结束即到最后一个元素且无异常时才进入

###### range

range(5)得到一个0到m的数字序列

[0,1,2,3,4]

range(1,5)得到一个n到m的数字序列

[1,2,3,4]

range(1,5,2)得到一个n到m每个数间隔k的数字序列

[1,3]

左开右闭

###### break

退出本层循环

###### continue

中断本次本层循环，直接跳到下一次循环（不管接下来的语句）

### 函数

len(),统计字符串长度

###### 定义函数

def 函数名(传入的参数):

​	函数体

​	return 返回值

可返回任何类型

##### 调用函数

函数名（传入参数）

函数名（参数名字1=，函数名字2=）

可达成乱序输入的效果

##### None空，无意义

等同于false

###### 函数的说明文档

"""

:参数的作用及意义

"""

###### global

将变量定义为全局变量，放在函数体里用，函数体外的都是全局变量，函数体内的变量为局部变量

有同名时要先global引入

###### 函数的多返回值

def kkk()

​    return a,b

x,y=kkk()

不同变量用，隔开，可返回不同类型的变量

##### 函数传参方式

1. 位置传参：传递的参数和定义的参数位置和个数一致

2. 关键字参数： 如mao(mane="mao",age=19),不用按顺序传参，但是关键字参数的名字要一致，可与位置传参混合（位置参数要在前面）

3. 缺省传参：也叫默认参数，如def mao(age=19)如果不传参数进去，则默认age=19

4. 注意：传入的参数若是数据容器，便只初始化一次![image-20230323170222813](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230323170222813.png)

5. ###### 不定长参数：

   也叫可变参数，用于不知到参数个数多少的情况

   位置不定长：

   如 def mao(*age)

   表示传递的所有参数都可以被age接收，得到一个age元组

   关键字不定长：

   如 def mao(**age)

     age是一个字典

   mao（x=1，y=2）

   age[3]

   函数可嵌套

   可通过

   fun1.fun2()进行调用

   可保护fun2()

   内部函数相当于闭包：即可对外部函数的变量进行操作

   fun(i)(j)也可使用

   ###### 匿名函数

   ![image-20230115150334240](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230115150334240.png)

   相当于想计算1+2，但是只知道了1和2但不知道加法，可以传一个加法进来

   lambda匿名函数：

   ![image-20230115152801045](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230115152801045.png)

   ![](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230115153934598.png)

   可在里面调用其他函数

   lambda 参数：函数体

   l=[(lambda x:x**2),

   (lamdba x:x**3)]

   print(l[0] (2)],l[1] (2))

   l=[1,2,3]

   print(list(map(lambda x:x+10,x)))

   map:映射

#### 数据容器

![image-20230114225909168](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230114225909168.png)

###### 列表（list）：相当于数组，可变的有序数据储存器

定义：

mao=[kk,kl,km,kn]

mao=list()//定义空列表

类型不受限制

print(mao)

使用：

mao[0]="kk"

mao[1]="kl"

mao[-1]="kn"

mao[-4]="kk"

双层：mao[0] [1]

可嵌套其他数据类型：但是遍历时会麻烦，取数据时也麻烦

###### 方法：

列表名.方法名

mao.index

1. 查找元素下标->num=列表名.index(元素)

2. 修改指定位置的值->列表[下标]=值

3. 插入元素->列表.insert(下标，元素)

4. 追加元素到尾部->列表.append(元素)

5. 追加一个数据容器到尾部->列表.extend(其它数据容器)

6. 删除指定下标的数据->del 列表[下标]，后面自动往前补齐，无下标则删除的是改列表

7. 删除指定下标的数据并返回该数据->k=列表.pop(下标),出栈

8. 指定元素的删除（删除从头到尾的第一个）->列表.remove(元素)，自动索引补齐

9. 清空列表->列表.clear()

10. 统计某元素的数量->列表.count(元素)

11. resever->反转列表

12. copy->复制列表

13. sorted->排序

14. a.sort->排序

15. a +[1,3,4,5]

16. a*3->得n个重复的a，复制的是引用，而不是值，改变一个值则相应的值也会改变，所谓引用可比如存储结构

17. 统计列表的元素->len(列表)

    循环遍历

    while index<len(列表):

       index+=1

    for x in 列表:

    <img src="C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230113172017894.png" alt="image-20230113172017894" style="zoom: 200%;" />

    ###### 列表推导式

    [x*x for x in range(1,10)]

    [x for x in range(1,101) if 0 not in[x%1!=0 for i in range(1,x)]]得1到100的素数

###### 元组（tuple）：不能改变的列表

定义完成则不可修改

定义：

mao=(kk,km,555)

mao=tuple()

注：定义单个元组时后面要加上一个单独的，

num=mao[1] [1]

方法：

index=mao.index(元素)

count=mao.count(元素)

num=len(元组)

遍历：

index=0

while index<len():

print(f"{}“)

index++

法二：

for x in 元组：

print

注：元组中的其他结构里的数据可以修改

<img src="C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230113171925520.png" alt="image-20230113171925520" style="zoom:33%;" />



a=1,2,3,4,5有逗号就默认元组

得元组

##### 字符串（str）:不可修改

汉字的字节也是1

无字符的数据结构

###### 转义字符

\\\\->\

\ "->''

\ b退格，\n换行



mao='kk''lll'='kklll'(用加号会耗时长)

用join（）方法

mao.join("klasdjal")



比较：直接就“    ”>"dkas"

按位比较，只要有一位大则整体大

mane="mao"

mane[0]=m

mane[-1]=o

方法：

in 包含操作



索引和切片

索引指下标操作（但不能修改）

切片指mao[0：4：1]



字符串格式化

print("{0},{1},{2}",format('jack',9,22003))

对应012指代数据

print("%d%5.2f(会对下一位四舍五入)%s"%(10,10.666.'jeck))

%占位符



strip([chars])

删除字符串里的chars

无chars时删空格

（chars里面有的字符并且在字符串的左右两边）都会被删除

sltrip:删除左边，有右边



index:得到起始下标

mao="kkk and mmm"

index=mao.index("and")

找不到会报错



replace:字符串的替换

newstr=字符串.replace(字符串1，字符串2，count)

得到一个新的字符串,原字符串不变



find（‘str',start,end）

从strat到end找str

找不到会返回-1



reverse()

数据转置



isalnum()

判断一个字符串是否只有数字和字母

isalpha（）

判断是否只有字母

islower（）

小写

isupper（）

大写



low()

变小写

upper()

变大写



endswith("hds")

判断是否以hds结尾



spilt:字符串的分割

字符串.spilt(分隔符字符串，count)

count表示分割几次

字符串本身不变，而是得到一个列表对象

如k=”mmm kkk lll"

mystrlist=k.spilt(" ")//通过“ ”分割

用空格分隔，分割后得到mystrlist=["mmm",''kkk'',"lll"]



partition(’34')

指定前中后分割

返回前面，他。后面



字符串的规整(去前后指定字符串)，有返回值

字符串.strip(字符串)//满足任一字符都可去除

mao="kkl lll lkk"

print(mao.strip("kkl"))//得到lll



统计字符串中某字符串出现的次数

chunt=count.字符串(字符串)



capitailize()

首字母大写



统计字符串长度

num=len(字符串)

<img src="C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230113171746139.png" alt="image-20230113171746139" style="zoom:33%;" />

有乘法操作

###### 正则表达式



### 序列(列表，字符串，元组):

切片：从一个序列中，取出一个子序列

序列[起始下标:结束下标:步长]//结束下标本身的数据不包含，即左闭右开

默认左边是0，右边是len（序列）

步长N：每次跳过N-1个元素取

步长为负数表示反向取（注意，起始下标和结束下标也要反向标记）

不影响序列本身，得到一个新序列，与操作序列类型一致

逻辑有问题则返回一个空序列

a[1:4]=[0],用0代替了123位的数，注意只存入一个0

###### 解包

1. x,y,z=range(3)
2. *range(1,3),7=(1,2,7),range(1,3),7=(range(1,3),7)

大型转化器，map(str,range(4)),将range里的数字都转化成str，得应该序列

###### 集合（set）：自动去重，顺序不定

mao={元素，元素，元素}

mao=set(元素，元素)

不支持下标索引，允许修改

方法：

添加元素：

mao.add(元素)

移除元素：

mao.remove(元素)

取出元素：

返回取出的元素，并从集合中删除

kk=mao.pop(元素)

清空集合：

clear(集合)

取两个集合的差集（1有2没有）：

新集合3=集合1.difference(集合2)

消除两个集合的差集：

集合1.difference_undata(集合2)

集合1改变，集合2不变

两个集合的合并：

new=集合1.union(集合2)

统计集合元素的数量：

number=len(集合)

集合的遍历：

用for

用while比较麻烦

![image-20230114221346338](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230114221346338.png)

##### 字典（dict）：相当于集合加列表

mao={kk:lll,mm:777}

mao=dict(kk:lll,mm:777)

主体不能相同，会导致无法索引

无法用下标索引

从字典中的主体找数据：

ao=mao[主体]

主体可以是任意结构，除字典外

数据无要求，都可以用

从嵌套字典中找某数据：

ao=mao[主 体] [嵌套主体]

常用操作：

（无元素则新增）新增元素：

字典[主体]=数据

更新元素：

字典[主体]=数据

删除元素：

data=字典.pop(主体)

清空字典：

字典.clear()

获取全部主体：

keys=字典.keys()

遍历：

用for

统计字典中元素数量;

num=len(字典)

![image-20230114225724990](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230114225724990.png)

##### 通用操作

1. 遍历

2. len()

3. max()

4. min()

5. 类型转换：list(),str(),tuple(),set(),字典可转其他，其他不能转字典

6. 排序：mao=sorted(容器,[reverse=Ture]),mao是一个列表，字典的排序会丢失数据（reverse是反转排序）

   <img src="C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230114230714337.png" alt="image-20230114230714337" style="zoom:33%;" />

### 文件：打开->读取/写入->关闭

文件编码：文件编码很多，备注一下密码本（编码），一般用UTF-8进行操作

##### 文件的打开：

f=open(名字，打开文件的形式，编码形式)

f是open函数的文件对象

如f=open('python.py','r',encoding="UTF-8")

因为encoding顺序不是第三位，所以要用关键字参数锁定

![image-20230115213745299](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230115213745299.png)

##### 文件的读取（r）：

文件对象.read(num)

num表示要从文件中读取的数据长度(单位是字节)，若没有num则默认是读完

mydatalist=文件对象.readlines()

返回一个列表，每一行是一个元素

读完后要关闭文件

time.sleep(200)停止两百秒

文件对象.close()

readline()表示一行行取

with open:

with open("d:\python.py","r") as 文件对象:

文件对象.readlines()

可以在操作完成后自动关闭文件

![image-20230116182452418](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230116182452418.png)

![image-20230116182543112](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230116182543112.png)

##### 文件的写入（w）：

文件写入：

文件对象.write(内容)//将内容写入缓冲区

内容刷新：

文件对象.flush()//让缓冲区的内容真正写入文件

关闭文件：

文件对象.close()//完成文件操作，内置了文件刷新功能，直接可以让内容写入文件

##### 文件的追加（a）：

可用\n进行换行操作

### python turtle库

###### 导入

1. import turtle

2. import turtle as 别名

3. from turtle import *//应用时不用加上别名/turtle.

   

   ###### 运动控制命令

   ![image-20230116185223969](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230116185223969.png)

   

###### 画笔设置命令

![image-20230116185325612](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230116185325612.png)

shape("turtle")让海龟出现

### 异常，包

#### 异常的捕获

try:

可能发生错误的代码

except:

如果出现异常执行的代码

捕获指定异常：

try:

print(name)

except NameError as e://e是异常变量，可通过打印e来得到为什么错误,NameError是错误类型

print("name变量名称未定义错误")

捕获多个异常

except（NameError，ZeroDivisionError）as e:

捕获所有异常

except Exception as e:或except：

顶级的异常类型

加个else：（可写）

没有异常时执行的代码

finally：

有无异常都要执行的代码

异常的传递与优先;

可在另外的函数里找到该函数的异常，优先第一个异常

##### python的模块

py代码文件（.py结尾）

自定义函数，后面可以自己用

###### 导入：

[from 模块名]  import[模块|类|变量|函数|*] [as别名]

组合形式：

import 模块名:   模块名.功能名()

from 模块名 import 类 变量 方法等：from time import sleep 导入sleep

sleep（）可直接用

from 模块名 import*// *代表引入所有的功能

直接写功能名就行了

import 模块名 as 别名//给模块改名

from 模块名 import 功能名 as 别名//给功能改名

注意：命名的使用按就近原则，后定义的相同名字代表最后一个

ctrl+鼠标左键点击模块名可看模块代码

##### 自定义模块并导入

新建一个py文件，并定义text函数

导入便可以用了

自定义包（py文件夹）parkage：

1.包含py文件

2.包含一个_init_.py文件（有则是py包，无就是普通文件夹）：建立包时会自动建立该文件

3.引入方式：import 包名.模块名

from 包名 import 模块名（不用写包名）

from 包名.模块名 import 功能名

from 包名 import *(前提要在init.py文件中加上_ all _=["模块名"，“模块名”]，能引入all包含模块的所有功能)，用的时候要加上模块名

4.包名.模块名.目标

### 安装第三方包

python pip程序：打开cmd 输入pip install 包名称，网速慢

改进

pip install -i https://pypi.tuna.tsinghua.edu.cn/simple 包名称

或者在pycharm里的解析器选项中点击interpreter  settings

在加号里搜索

option里加上-i 网站

#### 数据可视化

###### json：带有特定格式的字符串，在各个编程语言中都适用

[{"name","admin'',"age'':18},{},{}]

将字典转换为字符串

将列表转换为字符串

import json

将py转换为json

json.dumps(data)

将json转换为py

json.loads(data)

中文在转换时会涉及编码问题

解决方法：在data后面加上ensure_ascii=False表示不用ascii表示中文

##### pyecharts模块

pyecharts.org

gallerypychart.org

###### 画折线图步骤

1. 导功能，from pycharts.charts import line

2. 得到折线对象 line=line()

3. 添加x轴数据   line.add_xaxis(["",""])，数据可以是列表字符串等等

4. 添加y轴数据 line.add_yaxis("name",[,,]),数据可是任意东西,对应x轴数据

5. 生成图表 line.render()：一个html网页文件，要用浏览器打开

6. 设置全局配置

   

   局部配置

### 面向对象

1. 设计表格：设计类（class）:可包含数据和行为（函数）

class  student:

​	name=None#记录学生姓名,成员变量

​    def min(self(表示类对象自身)):#成员方法

在成员方法内部要访问类的成员变量必须使用self，但不用传参给self

​		.......

.......

2. 打印生产表格：创建对象

stu1=student()

stu2=student()

3. 填写表格：对象属性赋值

   stu1.name="周杰伦"

##### 类与对象

|                           现实事物                           |
| :----------------------------------------------------------: |
| 属性                                                                      行为 |

构造方法：_int _()

可以实现：

1.在构建类对象（构建类）的时候，会自动执行

2.在创建类对象（构建类）的时候，将传入参数自动传递给__init     _方法使用

![image-20230215212233858](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230215212233858.png)

类中的name等可省

注意：self不要省略，对成员关键字操作时不能忘了self

#### 类内置方法：

