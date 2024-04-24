#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//公共继承
class Base1
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son1 : public Base1
{
public:

	void func()
	{
		m_A = 100;  // m_A在Son1中是 public 权限
		m_B = 100;  // m_B在Son1中是 protected 权限
		//m_C = 100; // 父类中的私有属性 子类也访问不到
	}
};
void test01()
{
	Son1 s;
	s.m_A = 100; // m_A 在Son1中是public权限，可以类外访问
}


// ------------------------  保护继承  ------------------------

class Base2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son2 : protected Base2
{
public:

	void func()
	{
		m_A = 100; //m_A在Son2类中的权限为 protected 
		m_B = 100; //m_B在Son2类中的权限为 protected
		//m_C = 100; //父类中的私有属性 子类也访问不到
	}
};

void test02()
{
	Son2 s;
	//s.m_A = 100; //m_A在Son2中的权限 是protected ，类外不可以访问
}

// ------------------------  私有继承  ------------------------
class Base3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son3 :private Base3
{
public:
	void func()
	{
		m_A = 100; //m_A在Son3类中的权限为 private 
		m_B = 100; //m_B在Son3类中的权限为 private 
		//m_C = 100; //父类中的私有属性 子类也访问不到
	}
};
class GrandSon3 :public Son3
{
public:
	void func()
	{
		//m_A = 100; m_A在Son3中已经变为 private权限，因此访问不到
	}
};
void test03()
{
	Son3 s;
	//3个属性都访问不到
	//s.m_A = 100;
	//s.m_B = 100;
	//s.m_C = 100;

}


int main(){



	system("pause");
	return EXIT_SUCCESS;
}