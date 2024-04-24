#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
//类模板 
//template下面紧跟着的内容是类，那么这个类称为 类模板
//  类模板中的类型 也可以有默认参数
// 泛型编程  类型参数化

template<class NAMETYPE, class AGETYPE = int >
class Person
{
public:
	Person(NAMETYPE name, AGETYPE age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	NAMETYPE m_Name;
	AGETYPE m_Age;

};

void test01()
{
	//Person p1("Tom", 11); // 对于类模板，使用时候不可以用自动类型推导
	Person<string> p1 ("Tom", 11); //类模板必须用显示指定类型
	cout << "姓名： " << p1.m_Name << " 年龄： " << p1.m_Age << endl;
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}