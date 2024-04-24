#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Printer
{
public:
	static Printer * getInstance()
	{
		return printer;
	}

	//打印操作
	void printText(string text)
	{
		cout << "打印的内容： " << text << endl;
		m_Count++;
	}
	int m_Count; //打印机使用次数

private:
	Printer()
	{
		m_Count = 0;
	}

	Printer(const Printer & p)
	{
	
	}

	static Printer *  printer;

	

};

Printer *  Printer::printer = new Printer;


void test01()
{
	Printer * p1 = Printer::getInstance();
	p1->printText("入职申请");
	p1->printText("离职报告");
	p1->printText("旅游申请");
	p1->printText("请假申请");

	cout << "打印机使用次数 : " << p1->m_Count << endl;

	Printer * p2 = Printer::getInstance();
	p2->printText("调休申请");

	cout << "打印机使用次数 : " << p1->m_Count << endl;
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}