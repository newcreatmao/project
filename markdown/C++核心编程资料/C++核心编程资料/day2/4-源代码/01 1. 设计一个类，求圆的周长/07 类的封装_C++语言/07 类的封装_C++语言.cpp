#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//struct Person
//{
//	char m_Name[64];
//	int m_Age;
//	void PersonEat()
//	{
//		cout << m_Name << "在吃人饭" << endl;
//	}
//};
//



class  Person
{
public:
	char m_Name[64];

	void PersonEat()
	{
		cout << m_Name << "在吃人饭" << endl;
	}

private:
	int m_Age;
};


struct Dog
{
	char m_Name[64];
	int m_Age;
	void DogEat()
	{
		cout << m_Name << "在吃狗粮" << endl;
	}
};


//C++封装： 将属性和行为作为一个整体，来表现生活中的事和物
//C++下的struct  和 class 区别 ：  struct默认权限  public 公共权限     class默认权限  private 私有权限
//将这些成员  加以权限进行控制
// 权限：  public 公共权限  protected 保护权限  private  私有权限
// public       类内可以访问  类外也可以访问
// protected    类内可以访问  类外不可以访问（子类可以访问）
// private      类内可以访问  类外不可以访问 (子类也不可以访问）
void test01()
{
	Person p1;
	strcpy(p1.m_Name, "老王");

	Dog d1;
	strcpy(d1.m_Name, "旺财");

	d1.DogEat();

	//p1.DogEat(); 人就不可以调用狗类中的成员函数

}





int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}