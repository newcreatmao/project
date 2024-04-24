#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
	Animal()
	{
		cout << "Animal�Ĺ��캯������" << endl;
	}

	//������ �����������  ���������ж������ݣ��ͷ�ʱ��Ե����ͷŲ��ɾ����ڴ�й¶
	//virtual ~Animal()
	//{
	//	cout << "Animal��������������" << endl;
	//}

	//��������
	//������  Ҳ������ʵ�֣�����ʵ��
	// ���һ������ ���� ����������������ô����� Ҳ���ڳ�����
	virtual ~Animal() = 0;


	virtual void speak()
	{
		cout << "������˵��" << endl;
	}

	

};

Animal::~Animal()
{

	cout << "Animal�Ĵ���������������" << endl;
}


class Cat :public Animal
{
public:

	Cat(char * name)
	{
		cout << "Cat�Ĺ��캯���ĵ���" << endl;
		this->m_Name = new char[strlen(name) + 1];
		strcpy(this->m_Name, name);
	}

	void speak()
	{
		cout << m_Name <<"Сè��˵��" << endl;
	}

	~Cat()
	{
		if (this->m_Name != NULL)
		{
			cout << "Cat�����������ĵ���" << endl;
			delete [] this->m_Name;
			this->m_Name = NULL;
		}
	}

	char * m_Name; //è������
};


void test01()
{
	Animal * animal = new Cat("Tom");

	animal->speak();


	delete animal;
}

int main(){

	test01();


	system("pause");
	return EXIT_SUCCESS;
}