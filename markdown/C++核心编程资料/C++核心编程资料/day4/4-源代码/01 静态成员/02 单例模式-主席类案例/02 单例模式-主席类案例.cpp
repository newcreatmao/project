#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class ChairMan
{

public:
	//������ϯָ��
	static ChairMan * getInstance()
	{
		return singleMan;
	}

private:
	//�����캯��˽�л� �������Դ����������
	ChairMan()
	{ 
		//cout << "ChairManĬ�Ϲ��캯������" << endl; 
	};

	//�������캯��Ҳ˽�л�
	ChairMan(const ChairMan & c)
	{
	
	}

	//�����ǹ���ģ�����ֻ���õ�һ����ϯ�Ķ����ָ�뼴��

//public:
private: 
	static ChairMan * singleMan;

};

ChairMan * ChairMan::singleMan = new ChairMan; //Ψһ����ϯ���ָ��

void test01()
{
	//ChairMan c1;
	//ChairMan c2;
	//ChairMan * c3 = new ChairMan;


	/*ChairMan * c1 = ChairMan::singleMan;
	ChairMan * c2 = ChairMan::singleMan;*/

	//if (c1 == c2)
	//{
	//	cout << "c1 �� c2 ���" << endl;
	//}
	//else
	//{
	//	cout << "c1 �� c2 �����" << endl;
	//}


	//ChairMan::singleMan = NULL;

	ChairMan * c1 = ChairMan::getInstance();
	ChairMan * c2 = ChairMan::getInstance();

	if (c1 == c2)
	{
		cout << "c1 �� c2 ���" << endl;
	}
	else
	{
		cout << "c1 �� c2 �����" << endl;
	}

	/*ChairMan * c3 = new ChairMan(*c1);
	if (c1 == c3)
	{
		cout << "c1 �� c3 ���" << endl;
	}
	else
	{
		cout << "c1 �� c3 �����" << endl;
	}*/



}

int main(){

	test01();
	//cout << "main ��������" << endl;

	system("pause");
	return EXIT_SUCCESS;
}