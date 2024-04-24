### 基础语法

创建项目

创建文件

编写文件

运行程序



````c++
#include<iostream>
using namespace std;
int main ()
{
    system("pause");
    return 0;
}

````

cout<<""<<endl;

输出

cin>>输入

注释：//单行     /* */多行

main是程序的入口，每个项目有且只能由一个·

变量：数据类型 变量名

int char string(引入string包) double float long

int a=10; 

cout<<"a="<<a<<endl;

#define 宏常量 :#define 常量名 常量值

表示一个常量

const修饰变量表示将其变为常量，不可修改

const int a=10;



#### 指针所占内存空间

32位是4，64位是8，和数据类型无关



空指针：指向内存0的指针，如int*p=NULL;

初始化指针变量，空指针不可访问

不可访问的还有0-255的内存编号（电脑系统占用）、



野指针

指针变量指向违法内存空间

空指针和野指针都不是我们申请的空间，不能访问





### 面向对象

内存分区模型

代码区，全局区，蘸取，堆区

![image-20230715134239426](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230715134239426.png)

代码区和全局区在程序运行前就存在了

栈区和堆区在程序运行后才存在

![image-20230715134556503](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230715134556503.png)

局部和全局不放一起



栈区：由编译器自动分配释放，存放函数的参数值，局部变量，形参等

注：不要返回局部变量的地址，栈区开辟的数据由编译器自动释放（第一次会返回正确的数值，但后面就不会了，因为编译器做了一次保留）

栈区的数据在函数执行完后自动释放，

堆区：

由程序员分配释放，若程序员不释放，则程序结束时由操作系统回收

在C++中主要利用new在堆区开辟内存

int*p=new int（10）；new'返回的是地址，内存开辟，用该类型的指针接收

堆区开辟的数据由程序员手动开辟，手动释放，释放用操作符delete

delete 地址

delete后变量名还可使用

在未delete之前都是可访问的



###### 引用

类型 &别名=原名

即使两个变量访问同一块内存，修改哪个都可以改变该内存的数据

引用必须要初始化，且初始化后不能改变，即必须要有原名

别名一旦指向了一块内存后就不能再用去指向其他内存，引用不能直接更改



可以使用引用让形参修饰实参，即做函数参数

![image-20230715153519246](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230715153519246.png)



引用可作为函数的返回值

不要返回局部变量的返回存在

函数的调用可作为左值

int & six()

six() = 1000;相当于赋值



引用相当于是const指针变量，即将地址固定

引用就是一个封装好的指针常量



常量引用：修饰形参防止误操作

const int & ref=10;将代码修改为int team=10;（临时变量）const int&ref=team;

加上const后变成可读，不能修改









###### 函数

默认参数

若传入则按传入的来，无传入用默认值

注：

1.在某个位置有了默认参数，那从这个位置往后的参数都要给默认值

2.若函数的声明有默认参数，函数的实现就不能有默认参数，默认参数有一个有就行



占位参数

只填数据类型即可，但传参时一定要给数据

占位参数可有默认参数



函数重载（函数名相同）

满足条件：

同一个作用域下

函数名称相同

函数参数类型或个数或位置不同

注意：函数的返回值不能作为函数重载的条件，如int mao（）和void mao（int a）不能一起用

引用作为函数重载的条件

即变量和常量的区别

函数重载与默认参数：注意默认参数的使用

void fun(int a,int b=10)

void fun(int a)

fun(10)//不能用，要尽量避免编译器不能区分的情况





###### 类和对象

class 类名{ 访问权限：属性/行为};



封装：

成员：类的属性（属性，变量）和行为（函数，方法）



访问权限：

public 公共权限，类内外都可以访问

protected 保护权限，类内可以访问，外不行，儿子可以访问父亲中的保护内容

private 私有权限，类内可以访问，外不行，儿子都不能访问



struct默认权限是公共

class默认权限是私有



成员属性设置为私有

可自己控制读写权限：在公共部分设置函数改变或读取成员属性

对于写可以检测数据的有效性



对象的初始化和清理

构造函数和析构函数（构造取反）

![image-20230716113919142](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716113919142.png)

析构函数在对象执行完了，被释放了才会被调用



构造函数

有参，无参，普通，拷贝

![image-20230716125550351](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716125550351.png)

显示方法：

括号法：

（使用默认构造函数时不要加（），会使编译器误认为是一个函数声明）

![image-20230716132010211](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716132010211.png)

显示法：

![image-20230716131940270](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716131940270.png)

隐式转换法：

![image-20230716132321497](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716132321497.png)



拷贝构造函数的调用：

![image-20230716133030355](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716133030355.png)

![image-20230716133109272](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716133109272.png)

![image-20230716133220979](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716133220979.png)



注：返回的不是P1本身，而是根据P1创建的新对象



![image-20230716133947303](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716133947303.png)





![image-20230716134053250](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716134053250.png)



![image-20230716134419079](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716134419079.png)

P2已经释放了该地址下的内存，P1再释放就是非法操作了

浅拷贝会出现堆区的内存重复释放

![image-20230716134810238](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230716134810238.png)

重新申请一块内存

总结：若属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题



初始化列表

构造函数（）：属性1（值1），属性2（值2）...{}



嵌套对象：当其他对象作为本类成员时，构造时候先构造类对象再构造自身，先析构自身，再析构类对象。

大盒子包小盒子



![image-20230717100230171](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717100230171.png)

![image-20230717100819587](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717100819587.png)

静态成员或方法的访问方式，，::表示类作用域下的一个成员或方法



成员变量和函数分开存储

只有非静态成员变量才属于类的对象上

空对象占用的内存空间是1，为了区分空对象占内存的位置，每个空对象都有一个独一无二的内存地址

非空的按照成员变量分配内存，注：静态成员变量的分配不在类上

###### this





![image-20230717102613564](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717102613564.png)

![image-20230717103027766](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717103027766.png)



链接式对象函数，

![image-20230717103434687](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717103434687.png)

![image-20230717103526833](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717103526833.png)

cout等都是这种思想

不用引用则返回的不是本体，是一个新对象，值不确定



![image-20230717105058711](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717105058711.png)

调用对象中的属性时默认使用了this指针，当对象为空指针时程序会崩

可增加if条件增强程序可读性

![image-20230717110721623](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717110721623.png)

this指针的本质是指针常量，指针的指向不可修改

![image-20230717111502545](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230717111502545.png)



````c++
#include<iostream>
using namespace std;
int main()
{
    int i;
    cout<<"i="<<i
}
````

````c++
//头文件框架
#ifndef __HEAD_H_
#define __HEAD_H_//自取名称，用来判断程序是否运行过该代码段
//防卫式声明


#endif   //结束
````

````c++
template<typename T>
//class声明
class complex //class head
{//class body
pubilc://公开的，函数部分
    complex(T r=0, Ti=0)//构造函数，名称与类相同，无返回类型
    :re(r),im(i)//构造函数才有的，初值列，初始化
    {re(r),im(i);}//固值化，可改初始化的值
    complex():re(0),im(0){}//不行，函数重载条件：在同一个作用域下，函数名称相同，函数参数类型或个数或顺序不同即可重载
    //函数的参数可有默认值
    complex&operator+=(const complex&);
    T real()const {return re;}//每个函数在定义完后会根据变量名和类型等生成指定编码给编译器，因此同名函数在编译器中并不是完全相同的
    T imag()const{return im;}//函数若在class body内定义完成，便自动成为inline（内置函数）候选人
private://私有的，数据部分
    T re,im;
    
    friend complex&__doapl (complex*,const complex&);
    
private:
    
}

inline T imag(const complex& x)
{return x.imag();}//在外部定义的inline

//错误，private不能直接取,靠函数调用出
{
    complex c1(2,1);
    cout<<c1.re;
    cout<<c1.im;
}
//正确，public可调用
{
    complex c1(2,1);
    cout <<c1.real();
    cout<<c1.imag();
}

void real(T r){re=r;}//函数重载
````

###### 友元

friend

![image-20230718204858367](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230718204858367.png)

全局函数做友元

![image-20230718205859447](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230718205859447.png)

函数，放进去相当于一个声明

类做友元

![image-20230718210859259](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230718210859259.png)
::表示类的作用域

![image-20230718211930398](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230718211930398.png)

成员函数做友元

![image-20230718213655221](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230718213655221.png)



###### 运算符重载

加号：

![image-20230718214950350](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230718214950350.png)

operator

运算符重载也可以发生函数重载

可进行不同数据间的加减法

内置的数据类型的表达式的运算符是不可以变的



左移

![image-20230719101115118](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719101115118.png)

![image-20230719101722574](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719101722574.png)

递增

![image-20230719103603882](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719103603882.png)

赋值

![image-20230719104747948](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719104747948.png)

关系运算符重载(><>=<===)：：写在类里

![image-20230719111136482](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719111136482.png)

()重载

![image-20230719111545658](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719111545658.png)

匿名函数对象

类型（）匿名对象，用完即释放



###### 继承

语法：class 子类（派生类）：继承方式  父类（基类）

继承方式：

public:

protected:

private:

![image-20230719114115750](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719114115750.png)

可访问到父类的保护类型

![image-20230719115326387](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719115326387.png)

![image-20230719115232666](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719115232666.png)

开发人员命令提示工具

![image-20230719115432035](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719115432035.png)

![image-20230719115738713](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719115738713.png)

盒子法

![image-20230719115934241](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719115934241.png)

![image-20230719120015405](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719120015405.png)



![image-20230719120244427](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719120244427.png)

![image-20230719120335866](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719120335866.png)

广度继承



虚基类指针，底层通过两份指针通过偏移量找到基类相同的变量

![image-20230719141103629](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719141103629.png)

![image-20230719141519390](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719141519390.png)

![image-20230719141617991](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719141617991.png)



###### 多态

![image-20230719141931016](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719141931016.png)

动态多态的条件

![image-20230719144318261](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230719144318261.png)

![image-20230720113413777](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720113413777.png)

通过虚函数表的覆盖机制改变虚函数在不同对象下的展示，实现多态

##### 虚函数

[C++虚函数详解](https://blog.csdn.net/qq_42048450/article/details/117282640?ops_request_misc=%7B%22request%5Fid%22%3A%22169182753816800185812702%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=169182753816800185812702&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-117282640-null-null.142^v92^chatgptT0_1&utm_term=虚函数&spm=1018.2226.3001.4187)

[虚函数详解](https://blog.csdn.net/weixin_45372436/article/details/102057589?ops_request_misc=&request_id=&biz_id=102&utm_term=虚函数&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-102057589.nonecase&spm=1018.2226.3001.4187)

###### 抽象类

![image-20230720121156088](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720121156088.png)

![image-20230720122911286](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720122911286.png)

![image-20230720164826826](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720164826826.png)

解决子类析构函数无法调用的问题



###### 文件

![image-20230720171251540](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720171251540.png)

![image-20230720172251605](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720172251605.png)

![image-20230720172546993](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720172546993.png)

读文件的打开操作应该将of改成if

默认创建在同级目录下

![image-20230720173535949](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720173535949.png)

读文件

![image-20230720173747694](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720173747694.png)

![image-20230720174237532](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720174237532.png)

![image-20230720174504855](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230720174504855.png)

### STL

每个容器都需要调用头文件才能使用

容器，算法，迭代器

![image-20230722171056668](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722171056668.png)

![image-20230722172001342](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722172001342.png)

![image-20230722172356223](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722172356223.png)

![image-20230722172605912](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722172605912.png)



#### vector

![image-20230722204731335](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722204731335.png)

使用方式：

![image-20230722205534834](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722205534834.png)

遍历方式：

![image-20230722205927918](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722205927918.png)

![image-20230722210152053](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722210152053.png)

![image-20230722210406511](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722210406511.png)

![image-20230722210503423](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722210503423.png)

###### 存放自定义的数据类型

![image-20230722211016760](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722211016760.png)

对象当类型，结构体也行

v.push_back(pn)//尾插

![image-20230722211743401](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722211743401.png)

指针

![image-20230722212123151](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722212123151.png)

###### 嵌套

![image-20230722212341319](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722212341319.png)

相当于二维数组

![image-20230722212644520](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722212644520.png)

![image-20230722213055251](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722213055251.png)



单端数组，可动态扩展（但不同于数组的动态分配，他是找更大的空间将原数据copy然后释放原空间，并不是在原空间后面接）

![image-20230722221343684](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722221343684.png)

![image-20230722221451914](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722221451914.png)

![image-20230722221854663](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722221854663.png)

###### 大小判断

![image-20230723112019619](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723112019619.png)

###### 插入和删除

![image-20230723112236444](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723112236444.png)



![image-20230723112316521](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723112316521.png)



![image-20230723112358346](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723112358346.png)



![image-20230723112807106](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723112807106.png)

![image-20230723112838955](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723112838955.png)







#### string

![image-20230722213330655](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722213330655.png)

![image-20230722213645970](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722213645970.png)



![image-20230722214016797](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722214016797.png)

注：operator=可参考运算符重载

![image-20230722214530220](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722214530220.png)

![image-20230722214820323](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722214820323.png)

前面是运算符重载，后面是重载方法



![image-20230722215246581](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722215246581.png)

![image-20230722215305346](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722215305346.png)

先比较长短，再从头向后比较，一旦遇到字母ascll不同就返回

![image-20230722215639025](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722215639025.png)

下标和at方式

可修改

![image-20230722220055033](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722220055033.png)

![image-20230722220116984](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230722220116984.png)



#### deque

![image-20230723113013169](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723113013169.png)

双链表



![image-20230723113457882](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723113457882.png)

支持随机访问

![image-20230723113550111](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723113550111.png)

![image-20230723114311681](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723114311681.png)

![image-20230723114330317](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723114330317.png)

![image-20230723114348713](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723114348713.png)

![image-20230723114407840](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723114407840.png)

![image-20230723114439964](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723114439964.png)





随机数



![image-20230723115947455](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723115947455.png)

![image-20230723120006518](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723120006518.png)

####  栈：stack

![image-20230723120137364](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723120137364.png)

![image-20230723120158117](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723120158117.png)

#### queue队列

![image-20230723125856004](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723125856004.png)

![image-20230723130026829](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723130026829.png)

![image-20230723130248217](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723130248217.png)

#### list容器

![image-20230723130454042](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723130454042.png)

![image-20230723131544163](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723131544163.png)

![image-20230723131604998](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723131604998.png)

![image-20230723131709715](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723131709715.png)

创建

![image-20230723132011216](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723132011216.png)

![image-20230723132212564](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723132212564.png)

![image-20230723132257002](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723132257002.png)

![image-20230723132659741](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723132659741.png)

![image-20230723132808389](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723132808389.png)

![image-20230723132925214](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723132925214.png)

![image-20230723133341391](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723133341391.png)

排序规则

![image-20230723134112209](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723134112209.png)

自定义排序规则

![image-20230723134218165](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723134218165.png)

直接调用排序规则

#### set/mutiset集合

![image-20230723134412165](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723134412165.png)

![image-20230723134714328](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723134714328.png)

![image-20230723134747278](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723134747278.png)

不支持resize（用0补位会破坏规则）

![image-20230723134847007](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723134847007.png)

![image-20230723135321211](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723135321211.png)

返回的是指针（迭代器得到的是指针）

![image-20230723135427778](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723135427778.png)

判断两个数据是否相同的方法

pair

![image-20230723135752391](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723135752391.png)

![image-20230723141011023](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723141011023.png)

仿函数，类

![image-20230723141423120](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723141423120.png)

![image-20230723141442614](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723141442614.png)

自定义数据类型时需要制定规则才能插数据

![image-20230723141927573](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723141927573.png)

#### map/multimap字典

![image-20230723142513297](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723142513297.png)

![image-20230723142737882](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723142737882.png)

![image-20230723143255323](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723143255323.png)

pair异名

按照key以从小到大排序

![image-20230723143459801](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723143459801.png)

![image-20230723143638668](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723143638668.png)

![image-20230723143720749](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723143720749.png)

![image-20230723143840930](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723143840930.png)

![image-20230723144050074](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723144050074.png)

pr即排序规则，map也是需要用仿函数修改排序规则

自定义数据需要自定义排序规则，否则会报错

#### 函数对象仿函数

![image-20230723144503492](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723144503492.png)

![image-20230723145000392](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723145000392.png)

![image-20230723145146491](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723145146491.png)

![image-20230723145702780](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723145702780.png)

![image-20230723145904295](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723145904295.png)

#### 谓词pred

![image-20230723194244978](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723194244978.png)

![image-20230723194738506](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723194738506.png)

![image-20230723194755723](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723194755723.png)

有一个括号为空要加回去

#### 内建函数对象

![image-20230723194954453](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723194954453.png)

![image-20230723195023843](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723195023843.png)

![image-20230723195431777](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723195431777.png)

![image-20230723195457433](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723195457433.png)

![image-20230723195651142](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723195651142.png)

![image-20230723195726620](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723195726620.png)

![image-20230723200041053](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723200041053.png)

### 常用算法

![image-20230723200445343](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723200445343.png)

#### 遍历算法

![image-20230723200508723](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723200508723.png)

![image-20230723200755491](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723200755491.png)

![image-20230723200825241](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723200825241.png)

#### 查找算法

![image-20230723201336094](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723201336094.png)

![image-20230723201438391](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723201438391.png)

![image-20230723201651046](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723201651046.png)

![image-20230723201844067](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723201844067.png)

![image-20230723201906347](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723201906347.png)

find就是find_if中==条件下的情况





![image-20230723202236877](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723202236877.png)





![image-20230723202315843](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723202315843.png)



![image-20230723202431970](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723202431970.png)

![image-20230723202814466](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723202814466.png)

同理，count是count_if==时的情况

#### 排序算法

![image-20230723203012539](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203012539.png)

![image-20230723203037178](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203037178.png)

![image-20230723203101016](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203101016.png)

![image-20230723203330619](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203330619.png)

![image-20230723203435778](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203435778.png)

#### 拷贝和替换算法

![image-20230723203829047](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203829047.png)

![image-20230723203950370](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723203950370.png)

![image-20230723204022531](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204022531.png)



![image-20230723204049167](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204049167.png)

![image-20230723204109407](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204109407.png)

同种类型的容器

#### 算术生成算法

![image-20230723204212020](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204212020.png)

![image-20230723204502383](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204502383.png)

相当于sum

![image-20230723204530374](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204530374.png)

#### 集合算法

![image-20230723204607428](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204607428.png)

![image-20230723204655863](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204655863.png)

![image-20230723204906930](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723204906930.png)

![image-20230723205007045](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723205007045.png)

![image-20230723205027659](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230723205027659.png)

## 正则表达式

[C++正则表达式](https://blog.csdn.net/m0_72572822/article/details/126685382?ops_request_misc=&request_id=&biz_id=102&utm_term=c++正则表达式&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-126685382.142^v92^chatgptT0_1&spm=1018.2226.3001.4187)

## 函数指针

[回调函数](https://blog.csdn.net/qq_41854911/article/details/121058935?ops_request_misc=%7B%22request%5Fid%22%3A%22169219216316800188528467%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=169219216316800188528467&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-121058935-null-null.142^v92^chatgptT0_1&utm_term=回调函数&spm=1018.2226.3001.4187)

## 可变参数

[C语言可变参数](https://blog.csdn.net/m0_52517713/article/details/130715706?ops_request_misc=&request_id=&biz_id=102&utm_term=stdarg.h&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-130715706.nonecase&spm=1018.2226.3001.4187)