#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//struct Person
//{
//	char m_Name[64];
//	int m_Age;
//	void PersonEat()
//	{
//		cout << m_Name << "�ڳ��˷�" << endl;
//	}
//};
//



class  Person
{
public:
	char m_Name[64];

	void PersonEat()
	{
		cout << m_Name << "�ڳ��˷�" << endl;
	}

private:
	int m_Age;
};


struct Dog
{
	char m_Name[64];
	int m_Age;
	void DogEat()
	{
		cout << m_Name << "�ڳԹ���" << endl;
	}
};


//C++��װ�� �����Ժ���Ϊ��Ϊһ�����壬�����������е��º���
//C++�µ�struct  �� class ���� ��  structĬ��Ȩ��  public ����Ȩ��     classĬ��Ȩ��  private ˽��Ȩ��
//����Щ��Ա  ����Ȩ�޽��п���
// Ȩ�ޣ�  public ����Ȩ��  protected ����Ȩ��  private  ˽��Ȩ��
// public       ���ڿ��Է���  ����Ҳ���Է���
// protected    ���ڿ��Է���  ���ⲻ���Է��ʣ�������Է��ʣ�
// private      ���ڿ��Է���  ���ⲻ���Է��� (����Ҳ�����Է��ʣ�
void test01()
{
	Person p1;
	strcpy(p1.m_Name, "����");

	Dog d1;
	strcpy(d1.m_Name, "����");

	d1.DogEat();

	//p1.DogEat(); �˾Ͳ����Ե��ù����еĳ�Ա����

}





int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}