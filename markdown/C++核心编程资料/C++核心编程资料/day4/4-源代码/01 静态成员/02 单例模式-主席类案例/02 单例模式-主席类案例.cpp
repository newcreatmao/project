#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class ChairMan
{

public:
	//返回主席指针
	static ChairMan * getInstance()
	{
		return singleMan;
	}

private:
	//将构造函数私有化 ，不可以创建多个对象
	ChairMan()
	{ 
		//cout << "ChairMan默认构造函数调用" << endl; 
	};

	//拷贝构造函数也私有化
	ChairMan(const ChairMan & c)
	{
	
	}

	//数据是共享的，而且只许拿到一个主席的对象的指针即可

//public:
private: 
	static ChairMan * singleMan;

};

ChairMan * ChairMan::singleMan = new ChairMan; //唯一的主席类的指针

void test01()
{
	//ChairMan c1;
	//ChairMan c2;
	//ChairMan * c3 = new ChairMan;


	/*ChairMan * c1 = ChairMan::singleMan;
	ChairMan * c2 = ChairMan::singleMan;*/

	//if (c1 == c2)
	//{
	//	cout << "c1 与 c2 相等" << endl;
	//}
	//else
	//{
	//	cout << "c1 与 c2 不相等" << endl;
	//}


	//ChairMan::singleMan = NULL;

	ChairMan * c1 = ChairMan::getInstance();
	ChairMan * c2 = ChairMan::getInstance();

	if (c1 == c2)
	{
		cout << "c1 与 c2 相等" << endl;
	}
	else
	{
		cout << "c1 与 c2 不相等" << endl;
	}

	/*ChairMan * c3 = new ChairMan(*c1);
	if (c1 == c3)
	{
		cout << "c1 与 c3 相等" << endl;
	}
	else
	{
		cout << "c1 与 c3 不相等" << endl;
	}*/



}

int main(){

	test01();
	//cout << "main 函数调用" << endl;

	system("pause");
	return EXIT_SUCCESS;
}