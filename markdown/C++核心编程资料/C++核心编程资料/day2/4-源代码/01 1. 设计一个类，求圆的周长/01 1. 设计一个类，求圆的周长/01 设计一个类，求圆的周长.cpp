#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

const double PI = 3.14;

//����һ����  �ؼ��� class + ����
class Circle
{
public: //����������

	//���еĺ���  ��Ϊ��Ա���� ��Ա����
	double calculateZC()
	{
		return 2 * PI * m_R;
	}

	//���ð뾶 
	void setR(int r)
	{
		m_R = r;
	}

	//��ȡԲ��ǰ�뾶
	int getR()
	{
		return m_R;
	}

	//���еı��� ���ǳ�Ϊ ��Ա��������Ա����
	int m_R; //�뾶  ����
};

void test01()
{
	Circle c1; //ͨ���� ��������      ʵ��������

	//c1.m_R = 10;
	c1.setR(10);
	//cout << "Բ�İ뾶Ϊ��" << c1.m_R << endl;
	cout << "Բ�İ뾶Ϊ��" << c1.getR() << endl;
	cout << "Բ���ܳ�Ϊ��" << c1.calculateZC() << endl;

}


/*
2.	���һ��ѧ���࣬������������ѧ�ţ����Ը�������ѧ�Ÿ�ֵ��������ʾѧ������   ����ѧ��
*/
class Student
{
public:

	//��������
	void setName(string name)
	{
		m_Name = name;
	}

	//����ѧ��
	void setId(int id)
	{
		m_Id = id;
	}

	//��ʾ������ѧ��
	void showInfo()
	{
		cout << "��Ա����--- ������ " << m_Name << " ѧ�ţ� " << m_Id << endl;
	}


	string m_Name; //����
	int m_Id; //ѧ��

};

void test02()
{
	Student s1; //ʵ����ѧ������
	s1.setName("����");
	s1.setId(1);
	//cout << "������" << s1.m_Name << " ѧ�ţ� " << s1.m_Id << endl;
	s1.showInfo();


	Student s2;
	s2.setName("����");
	s2.setId(2);
	s2.showInfo();

}



int main(){

	//test01();

	test02();

	system("pause");
	return EXIT_SUCCESS;
}