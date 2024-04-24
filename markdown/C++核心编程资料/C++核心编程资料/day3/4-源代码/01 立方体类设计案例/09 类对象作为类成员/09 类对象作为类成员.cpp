#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
//手机类
class Phone
{
public:

	Phone(string pName)
	{
		cout << "Phone的构造函数调用" << endl;
		m_PhoneName = pName;
	}

	~Phone()
	{
		cout << "Phone的析构函数调用" << endl;
	}

	string m_PhoneName; //手机名称
};

//游戏类
class Game
{
public:
	Game(string gName)
	{
		cout << "Game的构造函数调用" << endl;
		m_GameName = gName;
	}
	~Game()
	{
		cout << "Game的析构函数调用" << endl;
	}
	string m_GameName;
};

class Person
{

public:
	Person(string name, string pName, string gName) : m_Name(name), m_Phone(pName), m_Game(gName)
	{
		cout << "Person 的构造函数调用" << endl;
	}

	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

	void playGame()
	{
		cout << m_Name << "拿着 << " << m_Phone.m_PhoneName<< " >> 牌手机 ，玩着 <<" << m_Game.m_GameName << ">> 游戏" << endl;
	
	}


	string m_Name; //姓名
	Phone m_Phone; //手机 
	Game m_Game;   //游戏
};

//当其他类对象作为本类成员，先构造其他类对象，再构造自身，释放的顺序与构造是相反

void test01()
{
	Person p("张三", "苹果", "王者荣耀");
	p.playGame();


	Person p2("李四", "三星", "消消乐");
	p2.playGame();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}