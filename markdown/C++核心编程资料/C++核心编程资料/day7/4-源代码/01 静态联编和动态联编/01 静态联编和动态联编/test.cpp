#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:

	//����virtual �ؼ��ֺ�   speak������Ϊ�麯��
	virtual void speak()
	{
		cout << "������˵��" << endl;
	}

	virtual void eat(int a)
	{
		cout << "�����ڳԷ�" << endl;
	}
};


class Cat :public Animal
{
public:

	void speak()
	{
		cout << "Сè��˵��" << endl;
	}

	virtual void eat(int a)
	{
		cout << "Сè�ڳԷ�" << endl;
	}
};

class Dog :public Animal
{
public:

	 void speak()
	{
		cout << "С����˵��" << endl;
	}
	 virtual void eat(int a)
	 {
		 cout << "С���ڳԷ�" << endl;
	 }

};

//�����и��ӹ�ϵ�������࣬c++���Բ���Ҫͨ������ǿת
//��̬���� ---  ��ַ���
//��̬���� ---  ��ַ���

//��̬����������
//1�����������麯��
//2��������д������麯��
//3�������ָ��������� ָ������Ķ���

//��д   ��������ʵ�ָ����е��麯�� �����뷵��ֵ��������������һ�²ų�Ϊ��д
//����������дʱ�� �����Բ��ӹؼ��� virtual

void doSpeak( Animal & animal ) // Animal & animal  = cat
{
	animal.speak();
}

void test01()
{
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);
}

void test02()
{
	Animal * animal = new Cat;
	//animal->speak();
	// *(int *)*(int*)animal speak�ĺ����ĵ�ַ
	((void(*)())  (*(int *)*(int*)animal))();

	//C++Ĭ�ϵ��ù��� __stdcall
	// �����д�� ���ù��� __cdecl ,����Ҫָ������Ϊ __stdcall
	typedef void( __stdcall *FUNC)(int);

	(FUNC(*((int*)*(int*)animal + 1)))(10);

}

int main(){
	//test01();

	test02();
	//cout << sizeof(Animal) << endl;


	system("pause");
	return EXIT_SUCCESS;
}