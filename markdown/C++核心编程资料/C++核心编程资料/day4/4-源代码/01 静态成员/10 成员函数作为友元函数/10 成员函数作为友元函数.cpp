#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class Building;
class goodGay
{
public:
	goodGay();
	void visit(); //visit���Է��� Building��˽������
	void visit2();//visit2�����Է��� Building��˽������
private:
	Building * building;
};

class Building
{
	//���߱�����  goodGay���е�visit��Ա���� ���Է��ʱ����е�˽������
	friend void goodGay::visit();
public:
	Building();

public:
	//����
	string m_SittingRoom;
private:
	//����
	string m_BedRoom;
};

//����������ʵ��
goodGay::goodGay()
{
	this->building = new Building;

}

void goodGay::visit()
{
	cout << "�û����� ���ڷ��ʣ�" << this->building->m_SittingRoom << endl;
	cout << "�û����� ���ڷ��ʣ�" << this->building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "�������� ���ڷ��ʣ�" << this->building->m_SittingRoom << endl;
	//cout << "�������� ���ڷ��ʣ�" << this->building->m_BedRoom << endl;
}


Building::Building()
{
	this->m_SittingRoom = "����";
	this->m_BedRoom = "����";
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