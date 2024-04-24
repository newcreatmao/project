#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include "MyArray.h"

void test01()
{
	MyArray * arr = new MyArray(10);

	delete arr;


	MyArray arr2;

	for (int i = 0; i < 10; i++)
	{
		arr2.pushBack(i + 100);
	}


	MyArray arr3(arr2);

	//测试 设置数据
	arr3.setData(0, 1000);

	for (int i = 0; i < 10;i++)
	{
		cout << "位置为 " << i + 1 << " 的元素为：" << arr3.getData(i) << endl;
	}

	cout << "数组的容量为：" << arr3.getCapacity() << endl;

	cout << "数组的大小为：" << arr3.getSize() << endl;


	cout << arr3[0] << endl;
	arr3[0] = 100000; // 1000  = 100000
	cout << arr3[0] << endl;
}



int main(){

	

	test01();

	system("pause");
	return EXIT_SUCCESS;
}