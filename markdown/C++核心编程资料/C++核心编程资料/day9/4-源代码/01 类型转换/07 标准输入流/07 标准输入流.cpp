#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
cin.get() //一次只能读取一个字符
cin.get(一个参数) //读一个字符
cin.get(两个参数) //可以读字符串
cin.getline()
cin.ignore()
cin.peek()
cin.putback()
*/


void test01()
{
	//cin.get()一次只能读取一个字符

	// a s 
	char c =  cin.get();
	//第一次输出 a
	cout << "c  = " << c << endl;

	c = cin.get();
	//第二次输出 s
	cout << "c  = " << c << endl;

	c = cin.get();
	//第三次输出 换行
	cout << "c  = " << c << endl;

	c = cin.get();
	//第四次  等待下一次输入
	cout << "c  = " << c << endl;

}


void test02()
{
	//cin.get(两个参数) //可以读字符串
	char buf[1024] = { 0};
	cin.get(buf, 1024); //当利用cin.get读取字符串时候，并不会读走换行符，而是遗留在缓冲区中

	char c = cin.get(); 
	if (c == '\n')
	{
		cout << "换行符遗留在缓冲区了" << endl;
	}
	else
	{
		cout << "换行符不在缓冲区了" << endl;
	}

	cout << "buf = " << buf << endl;

}


void test03()
{
	char buf[1024] = { 0 };

	cin.getline(buf, 1024);//如果利用cin.getline（）读取字符串，函数并不会读取换行符，而是将换行符从缓冲区中扔掉

	char c = cin.get();
	if (c == '\n')
	{
		cout << "换行符遗留在缓冲区了" << endl;
	}
	else
	{
		cout << "换行符不在缓冲区了" << endl;
	}

	cout << "buf = " << buf << endl;

}

//cin.ignore()忽略
void test04()
{
	cin.ignore(); //默认忽略1个字符，如果里面有参数N，代表忽略N个字符

	char c = cin.get();
	//输入是 a s
	//输出是  c = 
	cout << "c = " << c << endl;
}

//cin.peek()偷窥
void test05()
{
	char c = cin.peek();

	//输入  ： as
	//输出  ：
	cout << "c = " << c << endl;

	c = cin.get();

	cout << "c = " << c << endl;
}

//cin.putback() 放回
void test06()
{
	char c = cin.get();

	cin.putback(c); //放回的是原来的位置

	char buf[1024];
	cin.getline(buf, 1024);
	cout << "buf = " << buf << endl;
}

/*
	判断用户输入的内容  是字符串还是数字  1234    abcd    
*/
void test07()
{
	cout << "请输入一个字符串或者数字： " << endl;

	char c =  cin.peek();

	if (c >= '0' && c <= '9')
	{
		int num;
		cin >> num;
		cout << "您输入的是数字：" << num << endl;
	}
	else
	{
		char buf[1024] = { 0 };
		cin >> buf;
		cout << "您输入的是字符串：" << buf<< endl;
	}

}


/*
	让用户输入一个数字，必须在0到10之间的数字，如果输入有误重新输入 
*/
void test08()
{
	cout << "请输入 0 ~ 10 之间的数字" << endl;

	int num;

	while (true)
	{
		cin >> num;

		if (num > 0 && num < 10)
		{
			cout << "输入正确 --- 数字为：" << num << endl;
			break; //输入正确 退出循环
		}

		cout << "输入有误，请重新输入：" << endl;

		//缓冲区中的标志位  0代表正常    1  代表异常
		cin.clear(); 
		cin.sync(); //清空标志位 并且刷新缓冲区
		//cin.ignore(); //VS2015以上 需要做 忽略
		//cout << "cin.fail = " << cin.fail() << endl;
	}

}


int main(){

	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();

	//test07();
	test08();


	system("pause");
	return EXIT_SUCCESS;
}