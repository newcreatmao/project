#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include <string>

//�ҽ���
class Building
{
	//��һ��ȫ�ֺ��� ��Ϊ�������Ԫ���������Է��ʵ�˽������
	friend void goodGay(Building & building);
public:
	Building()
	{
		this->m_SittingRoom = "����";
		this->m_BedRoom = "����";
	}

public:

	//����
	string m_SittingRoom;

private:
	//����
	string m_BedRoom;
};

//�û���ȫ�ֺ���
void goodGay( Building & building)
{
	cout << "�û������ڷ���" << building.m_SittingRoom << endl;

	cout << "�û������ڷ���" << building.m_BedRoom << endl;
}

void test01()
{
	Building b;
	goodGay(b);
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}