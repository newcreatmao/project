#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//
////��Ϸҳ��
//class GamePage
//{
//public:
//
//	void header()
//	{
//		cout << "����ͷ��" << endl;
//	}
//	void footer()
//	{
//		cout << "�����ײ�" << endl;
//	}
//	void leftList()
//	{
//		cout << "����������б�" << endl;
//	}
//	void content()
//	{
//		cout << "LOL��Ϸֱ��" << endl;
//	}
//};
//
////����ҳ��
//class NewsPage
//{
//public:
//	void header()
//	{
//		cout << "����ͷ��" << endl;
//	}
//	void footer()
//	{
//		cout << "�����ײ�" << endl;
//	}
//	void leftList()
//	{
//		cout << "����������б�" << endl;
//	}
//
//	void content()
//	{
//		cout << "�����ٿ�" << endl;
//	}
//};


//���ü̳� ���Լ����ظ��������
// BasePage ���� (����)    GamePage ������ (����)
// �﷨ �� class ���� �� �̳з�ʽ  ����

class BasePage
{
public:
	void header()
	{
		cout << "����ͷ��" << endl;
	}
	void footer()
	{
		cout << "�����ײ�" << endl;
	}
	void leftList()
	{
		cout << "����������б�" << endl;
	}
};

//��Ϸ
class GamePage : public BasePage
{
public:
	void content()
	{
		cout << "LOL��Ϸֱ��" << endl;
	}
};
//����
class NewsPage :public BasePage
{
public:
	void content()
	{
		cout << "�����ٿ�" << endl;
	}

};


void test01()
{
	cout << "��Ϸҳ���������£�" << endl;
	GamePage game;
	game.header();
	game.footer();
	game.leftList();
	game.content();

	cout << "-------------------" << endl;
	cout << "����ҳ���������£�" << endl;
	NewsPage news;
	news.header();
	news.footer();
	news.leftList();
	news.content();



}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}