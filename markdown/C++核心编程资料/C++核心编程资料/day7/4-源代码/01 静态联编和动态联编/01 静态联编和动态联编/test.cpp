#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:

	//加上virtual 关键字后   speak函数变为虚函数
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}

	virtual void eat(int a)
	{
		cout << "动物在吃饭" << endl;
	}
};


class Cat :public Animal
{
public:

	void speak()
	{
		cout << "小猫在说话" << endl;
	}

	virtual void eat(int a)
	{
		cout << "小猫在吃饭" << endl;
	}
};

class Dog :public Animal
{
public:

	 void speak()
	{
		cout << "小狗在说话" << endl;
	}
	 virtual void eat(int a)
	 {
		 cout << "小狗在吃饭" << endl;
	 }

};

//对于有父子关系的两个类，c++可以不需要通过类型强转
//静态联编 ---  地址早绑定
//动态联编 ---  地址晚绑定

//多态的满足条件
//1、父类中有虚函数
//2、子类重写父类的虚函数
//3、父类的指针或者引用 指向子类的对象

//重写   子类重新实现父类中的虚函数 ，必须返回值、函数名、参数一致才称为重写
//子类在做重写时候 ，可以不加关键字 virtual

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
	// *(int *)*(int*)animal speak的函数的地址
	((void(*)())  (*(int *)*(int*)animal))();

	//C++默认调用惯例 __stdcall
	// 下面的写法 调用惯例 __cdecl ,我们要指定惯例为 __stdcall
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