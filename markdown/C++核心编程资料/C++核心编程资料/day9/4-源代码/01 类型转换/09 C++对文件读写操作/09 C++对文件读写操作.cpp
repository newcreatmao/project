#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//�ļ���д��ͷ�ļ�
#include <fstream>


//1��д�ļ�
void test01()
{
	//����  1  �ļ�·��   ����2  �򿪷�ʽ
	//ofstream ofs("./test.txt", ios::out | ios::trunc);
	ofstream ofs;
	ofs.open("./test.txt", ios::out | ios::trunc);

	//�ж��Ƿ�򿪳ɹ�
	/*if (!ofs.is_open())*/
	if (!ofs)
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	//д�ļ�
	ofs << "��������������" << endl;
	ofs << "���䣺18" << endl;
	ofs << "�Ա���" << endl;

	//�ر�������
	ofs.close();

}


//���ļ�
void test02()
{
	ifstream  ifs;
	ifs.open("./test.txt", ios::in); //���ô򿪷�ʽ

	if (!ifs)
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	//��һ�ַ�ʽ
	//char buf[1024] = { 0 };
	////��ÿ��������뵽��������
	//while (ifs >> buf) //���ж�ȡ��ֱ�������ļ�β
	//{
	//	cout << buf << endl;
	//}

	//�ڶ��ַ�ʽ
	//char buf[1024] = { 0 };
	//while (!ifs.eof())
	//{
	//	ifs.getline(buf, sizeof(buf));
	//	cout << buf << endl;
	//}


	//�����ַ�ʽ �����ַ���ȡ
	char c;
	while ( ( c=ifs.get()) != EOF )
	{
		cout << c;
	}

	//�ر�������
	ifs.close();

}

int main(){

	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}