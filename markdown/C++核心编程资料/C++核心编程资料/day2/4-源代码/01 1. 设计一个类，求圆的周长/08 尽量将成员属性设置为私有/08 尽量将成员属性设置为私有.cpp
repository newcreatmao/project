#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Person
{
public:

	//设置姓名
	void setName(string name)
	{
		m_Name = name;
	}
	//获取姓名
	string getName()
	{
		return m_Name;
	}

	//获取年龄
	int getAge()
	{
		return m_Age;
	}

	//设置年龄
	void setAge(int age)
	{
		if (age < 0 || age > 150)
		{
			m_Age = 0;
			cout << "你这个老妖精" << endl;
			return;
		}
		m_Age = age;
	}

	//设置情人
	void setLover(string lover)
	{
		m_Lover = lover;
	}

private:
	string m_Name; //可读可写  姓名
	int  m_Age ;  //可读可写  年龄
	string m_Lover; //只写  情人
};

//将成员属性设置为私有好处：  自己控制属性的读写权限
//将用户传入的数据 进行检测


void test01()
{
	Person p1;
	//p1.m_Name;
	p1.setName("张三");

	//设置情人
	p1.setLover("仓井");

	//设置年龄
	p1.setAge(100);
	

	cout << "姓名： " << p1.getName() << endl;

	cout << "年龄： " << p1.getAge() << endl;

	//cout << "情人： " << p1.m_Lover;  情人访问不到 因为只写状态


}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}