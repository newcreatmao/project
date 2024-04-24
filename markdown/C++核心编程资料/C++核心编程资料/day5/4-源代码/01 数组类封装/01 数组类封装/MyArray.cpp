#include "MyArray.h"

MyArray::MyArray()
{
	//cout << "默认构造函数调用" << endl;
	this->m_Capacity = 100;

	this->m_Size = 0;

	this->pAddress = new int[this->m_Capacity];

}


MyArray::MyArray(int capacity)
{
	//cout << "有参构造函数调用" << endl;
	this->m_Capacity = capacity;

	this->m_Size = 0;

	this->pAddress = new int[this->m_Capacity];
}

MyArray::MyArray(const MyArray & arr)
{
	//cout << "拷贝构造函数调用" << endl;
	this->m_Size = arr.m_Size;

	this->m_Capacity = arr.m_Capacity;

	this->pAddress = new int[this->m_Capacity];

	for (int i = 0; i < m_Size;i++)
	{
		this->pAddress[i] = arr.pAddress[i];
	}
}


void MyArray::pushBack(int val)
{
	this->pAddress[this->m_Size] = val;
	this->m_Size++;
}

void MyArray::setData(int index, int val)
{
	this->pAddress[index] = val;
}

int MyArray::getData(int index)
{
	return this->pAddress[index];
}

int MyArray::getSize()
{
	return this->m_Size;
}

int MyArray::getCapacity()
{
	return this->m_Capacity;
}

int& MyArray::operator[](int index)
{
	return this->pAddress[index];
}

MyArray::~MyArray()
{
	if (this->pAddress != NULL)
	{
		//cout << "析构函数调用" << endl;
		delete [] this->pAddress;
		this->pAddress = NULL;
	}
}
