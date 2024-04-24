#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#define MYADD(x,y) ((x)+(y))
//缺陷1、保证运算完整性  需要加小括号修饰
void test01()
{
	int a = 10;
	int b = 20;
	int ret = MYADD(a, b) * 20; //预期600  展开后  ((10) + (20)) * 20
	cout << "a + b = " << ret << endl;;
}

//缺陷2、即使加入括号修饰，有些情况依然出出现和预期不符的结果
#define  MYCOMPARE(a,b)  (((a) < (b)) ? (a) : (b))

inline int myCompare(int a, int b)
{

	return a < b ? a : b;
}

void test02()
{
	int a = 10;
	int b = 20;

	//int ret = MYCOMPARE(++a, b); // 预期结果 11   (((++a) < (b)) ? (++a) : (b))   
	int ret = myCompare(++a, b);
	cout << "ret = " << ret << endl;

}

//缺陷3  宏函数 不重视作用域



//内联函数 inline 
// 函数的声明和实现必须同时加入inline关键，否则不会按照内联方式处理
inline void func();
inline void func(){  };

//成员函数前面 隐藏的加入了 inline关键字

int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}