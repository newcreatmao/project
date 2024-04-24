#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//文件读写的头文件
#include <fstream>


//1、写文件
void test01()
{
	//参数  1  文件路径   参数2  打开方式
	//ofstream ofs("./test.txt", ios::out | ios::trunc);
	ofstream ofs;
	ofs.open("./test.txt", ios::out | ios::trunc);

	//判断是否打开成功
	/*if (!ofs.is_open())*/
	if (!ofs)
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//写文件
	ofs << "姓名：德玛西亚" << endl;
	ofs << "年龄：18" << endl;
	ofs << "性别：男" << endl;

	//关闭流对象
	ofs.close();

}


//读文件
void test02()
{
	ifstream  ifs;
	ifs.open("./test.txt", ios::in); //设置打开方式

	if (!ifs)
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//第一种方式
	//char buf[1024] = { 0 };
	////将每行输入读入到缓冲区中
	//while (ifs >> buf) //按行读取，直到读到文件尾
	//{
	//	cout << buf << endl;
	//}

	//第二种方式
	//char buf[1024] = { 0 };
	//while (!ifs.eof())
	//{
	//	ifs.getline(buf, sizeof(buf));
	//	cout << buf << endl;
	//}


	//第三种方式 单个字符读取
	char c;
	while ( ( c=ifs.get()) != EOF )
	{
		cout << c;
	}

	//关闭流对象
	ifs.close();

}

int main(){

	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}