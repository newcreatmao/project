#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <iomanip> //��׼������ ʹ�ÿ��Ʒ���ʽ��ʽ�������ͷ�ļ�
/*
cout.put() //�򻺳���д�ַ�
cout.write() //��buffer��дnum���ֽڵ���ǰ������С�
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
//ͨ������Ա����
	int number = 99;
	cout.width(20); //Ԥ��20�ռ�
	cout.fill('*'); //���
	cout.setf(ios::left); //�����
	cout.unsetf(ios::dec); //ж��ʮ����
	cout.setf(ios::hex);   //��װʮ������
	cout.setf(ios::showbase); //������ʾ���� ����
	cout.unsetf(ios::hex); //ж��ʮ������
	cout.setf(ios::oct);  //��װ�˽���
	cout << number << endl;
}


//ʹ�ÿ��Ʒ�
void test03(){

	int number = 99;
	cout << setw(20) //���ÿ��
		<< setfill('~') //���
		<< setiosflags(ios::showbase) //��ʾ���ƻ���
		<< setiosflags(ios::left)  //���������
		<< hex  //��װʮ������
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