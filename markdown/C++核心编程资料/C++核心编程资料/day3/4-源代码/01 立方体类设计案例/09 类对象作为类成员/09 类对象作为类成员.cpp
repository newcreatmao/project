#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
//�ֻ���
class Phone
{
public:

	Phone(string pName)
	{
		cout << "Phone�Ĺ��캯������" << endl;
		m_PhoneName = pName;
	}

	~Phone()
	{
		cout << "Phone��������������" << endl;
	}

	string m_PhoneName; //�ֻ�����
};

//��Ϸ��
class Game
{
public:
	Game(string gName)
	{
		cout << "Game�Ĺ��캯������" << endl;
		m_GameName = gName;
	}
	~Game()
	{
		cout << "Game��������������" << endl;
	}
	string m_GameName;
};

class Person
{

public:
	Person(string name, string pName, string gName) : m_Name(name), m_Phone(pName), m_Game(gName)
	{
		cout << "Person �Ĺ��캯������" << endl;
	}

	~Person()
	{
		cout << "Person��������������" << endl;
	}

	void playGame()
	{
		cout << m_Name << "���� << " << m_Phone.m_PhoneName<< " >> ���ֻ� ������ <<" << m_Game.m_GameName << ">> ��Ϸ" << endl;
	
	}


	string m_Name; //����
	Phone m_Phone; //�ֻ� 
	Game m_Game;   //��Ϸ
};

//�������������Ϊ�����Ա���ȹ�������������ٹ��������ͷŵ�˳���빹�����෴

void test01()
{
	Person p("����", "ƻ��", "������ҫ");
	p.playGame();


	Person p2("����", "����", "������");
	p2.playGame();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}