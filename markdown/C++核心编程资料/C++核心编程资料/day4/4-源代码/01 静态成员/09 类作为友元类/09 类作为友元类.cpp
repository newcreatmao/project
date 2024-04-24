#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>


class Building;
class goodGay
{
public:
	goodGay();
	void visit();
private:
	Building * building;
};

class Building
{
	//告诉编译器  goodGay类是 本类的好朋友，可以访问到里面私有内容
	friend class goodGay;

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

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

void test01()
{
	
	goodGay gg;
	gg.visit();

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}