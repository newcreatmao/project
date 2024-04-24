#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
cin.get() //һ��ֻ�ܶ�ȡһ���ַ�
cin.get(һ������) //��һ���ַ�
cin.get(��������) //���Զ��ַ���
cin.getline()
cin.ignore()
cin.peek()
cin.putback()
*/


void test01()
{
	//cin.get()һ��ֻ�ܶ�ȡһ���ַ�

	// a s 
	char c =  cin.get();
	//��һ����� a
	cout << "c  = " << c << endl;

	c = cin.get();
	//�ڶ������ s
	cout << "c  = " << c << endl;

	c = cin.get();
	//��������� ����
	cout << "c  = " << c << endl;

	c = cin.get();
	//���Ĵ�  �ȴ���һ������
	cout << "c  = " << c << endl;

}


void test02()
{
	//cin.get(��������) //���Զ��ַ���
	char buf[1024] = { 0};
	cin.get(buf, 1024); //������cin.get��ȡ�ַ���ʱ�򣬲�������߻��з������������ڻ�������

	char c = cin.get(); 
	if (c == '\n')
	{
		cout << "���з������ڻ�������" << endl;
	}
	else
	{
		cout << "���з����ڻ�������" << endl;
	}

	cout << "buf = " << buf << endl;

}


void test03()
{
	char buf[1024] = { 0 };

	cin.getline(buf, 1024);//�������cin.getline������ȡ�ַ����������������ȡ���з������ǽ����з��ӻ��������ӵ�

	char c = cin.get();
	if (c == '\n')
	{
		cout << "���з������ڻ�������" << endl;
	}
	else
	{
		cout << "���з����ڻ�������" << endl;
	}

	cout << "buf = " << buf << endl;

}

//cin.ignore()����
void test04()
{
	cin.ignore(); //Ĭ�Ϻ���1���ַ�����������в���N���������N���ַ�

	char c = cin.get();
	//������ a s
	//�����  c = 
	cout << "c = " << c << endl;
}

//cin.peek()͵��
void test05()
{
	char c = cin.peek();

	//����  �� as
	//���  ��
	cout << "c = " << c << endl;

	c = cin.get();

	cout << "c = " << c << endl;
}

//cin.putback() �Ż�
void test06()
{
	char c = cin.get();

	cin.putback(c); //�Żص���ԭ����λ��

	char buf[1024];
	cin.getline(buf, 1024);
	cout << "buf = " << buf << endl;
}

/*
	�ж��û����������  ���ַ�����������  1234    abcd    
*/
void test07()
{
	cout << "������һ���ַ����������֣� " << endl;

	char c =  cin.peek();

	if (c >= '0' && c <= '9')
	{
		int num;
		cin >> num;
		cout << "������������֣�" << num << endl;
	}
	else
	{
		char buf[1024] = { 0 };
		cin >> buf;
		cout << "����������ַ�����" << buf<< endl;
	}

}


/*
	���û�����һ�����֣�������0��10֮������֣�������������������� 
*/
void test08()
{
	cout << "������ 0 ~ 10 ֮�������" << endl;

	int num;

	while (true)
	{
		cin >> num;

		if (num > 0 && num < 10)
		{
			cout << "������ȷ --- ����Ϊ��" << num << endl;
			break; //������ȷ �˳�ѭ��
		}

		cout << "�����������������룺" << endl;

		//�������еı�־λ  0��������    1  �����쳣
		cin.clear(); 
		cin.sync(); //��ձ�־λ ����ˢ�»�����
		//cin.ignore(); //VS2015���� ��Ҫ�� ����
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