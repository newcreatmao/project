#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class Building;
class goodGay
{
public:
	goodGay();
	void visit(); //visit可以访问 Building中私有属性
	void visit2();//visit2不可以访问 Building中私有属性
private:
	Building * building;
};

class Building
{
	//告诉编译器  goodGay类中的visit成员函数 可以访问本类中的私有内容
	friend void goodGay::visit();
public:
	Building();

public:
	//客厅
	string m_SittingRoom;
private:
	//卧室
	string m_BedRoom;
};

//类外做函数实现
goodGay::goodGay()
{
	this->building = new Building;

}

void goodGay::visit()
{
	cout << "好基友类 正在访问：" << this->building->m_SittingRoom << endl;
	cout << "好基友类 正在访问：" << this->building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "坏基友类 正在访问：" << this->building->m_SittingRoom << endl;
	//cout << "坏基友类 正在访问：" << this->building->m_BedRoom << endl;
}


Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}


void test01()
{
	goodGay gg;
	gg.visit();
	//gg.visit2();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}