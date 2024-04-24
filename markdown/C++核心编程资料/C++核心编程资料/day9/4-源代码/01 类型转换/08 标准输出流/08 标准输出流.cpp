#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <iomanip> //标准输入流 使用控制符方式格式化输出的头文件
/*
cout.put() //向缓冲区写字符
cout.write() //从buffer中写num个字节到当前输出流中。
*/

void test01()
{
	//cout.put('a').put('b').put('c');

	/*char buf[] = "hello world";
	cout.write(buf,strlen(buf));*/

	cout << "hello world" << endl;
}

void test02()
{
//通过流成员函数
	int number = 99;
	cout.width(20); //预留20空间
	cout.fill('*'); //填充
	cout.setf(ios::left); //左对齐
	cout.unsetf(ios::dec); //卸载十进制
	cout.setf(ios::hex);   //安装十六进制
	cout.setf(ios::showbase); //设置显示进制 基数
	cout.unsetf(ios::hex); //卸载十六进制
	cout.setf(ios::oct);  //安装八进制
	cout << number << endl;
}


//使用控制符
void test03(){

	int number = 99;
	cout << setw(20) //设置宽度
		<< setfill('~') //填充
		<< setiosflags(ios::showbase) //显示进制基数
		<< setiosflags(ios::left)  //设置左对齐
		<< hex  //安装十六进制
		<< number
		<< endl;
	
}


int main(){

	//test01();
	//test02();

	test03();
	system("pause");
	return EXIT_SUCCESS;
}