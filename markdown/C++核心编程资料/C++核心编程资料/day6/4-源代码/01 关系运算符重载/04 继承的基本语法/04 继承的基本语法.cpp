#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//
////游戏页面
//class GamePage
//{
//public:
//
//	void header()
//	{
//		cout << "公共头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共底部" << endl;
//	}
//	void leftList()
//	{
//		cout << "公共的左侧列表" << endl;
//	}
//	void content()
//	{
//		cout << "LOL游戏直播" << endl;
//	}
//};
//
////新闻页面
//class NewsPage
//{
//public:
//	void header()
//	{
//		cout << "公共头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共底部" << endl;
//	}
//	void leftList()
//	{
//		cout << "公共的左侧列表" << endl;
//	}
//
//	void content()
//	{
//		cout << "两会召开" << endl;
//	}
//};


//利用继承 可以减少重复代码出现
// BasePage 基类 (父类)    GamePage 派生类 (子类)
// 语法 ： class 子类 ： 继承方式  父类

class BasePage
{
public:
	void header()
	{
		cout << "公共头部" << endl;
	}
	void footer()
	{
		cout << "公共底部" << endl;
	}
	void leftList()
	{
		cout << "公共的左侧列表" << endl;
	}
};

//游戏
class GamePage : public BasePage
{
public:
	void content()
	{
		cout << "LOL游戏直播" << endl;
	}
};
//新闻
class NewsPage :public BasePage
{
public:
	void content()
	{
		cout << "两会召开" << endl;
	}

};


void test01()
{
	cout << "游戏页面内容如下：" << endl;
	GamePage game;
	game.header();
	game.footer();
	game.leftList();
	game.content();

	cout << "-------------------" << endl;
	cout << "新闻页面内容如下：" << endl;
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