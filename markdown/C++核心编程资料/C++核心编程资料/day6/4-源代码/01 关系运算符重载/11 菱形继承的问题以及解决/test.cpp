#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//动物类
class Animal
{
public:
	int m_Age; //年龄
};

//virtual加上后 继承方式 数据虚继承
// Animal类 变为 虚基类
//羊类
class Sheep : virtual public Animal
{

};

//驼 
class Tuo : virtual public Animal
{

};

//羊驼
class SheepTuo : public Sheep, public Tuo
{

};

void test01()
{
	SheepTuo st;
	st.Sheep::m_Age = 10;
	st.Tuo::m_Age = 20;

	cout << "age = " << st.Sheep::m_Age << endl;
	cout << "age = " << st.Tuo::m_Age << endl;
	cout << "age = " << st.m_Age << endl;
	//m_Age只需要一份即可，菱形继承导致数据有一份浪费

}

//虚继承内部工作原理
void test02()
{
	SheepTuo st;
	st.m_Age = 100;


	//通过sheep找到偏移量值
	cout << "通过sheep找到的偏移量为:" << *(int *)((int*)*(int *)&st + 1) << endl;

	//通过Tuo找到偏移量值
	cout << "通过Tuo找到的偏移量为：" << *(int *)((int*)*((int *)&st + 1) + 1) << endl;
	
	//通过偏移量 求出m_Age的值
	cout << "age =  " << ((Animal *)((char *)&st + (*(int *)((int*)*(int *)&st + 1))))->m_Age << endl;

}

int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}