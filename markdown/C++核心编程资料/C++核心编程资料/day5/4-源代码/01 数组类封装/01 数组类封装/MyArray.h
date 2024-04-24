#pragma  once
#include <iostream>
using namespace std;

class MyArray
{
public:
	//Ĭ�Ϲ���
	MyArray();

	//�вι���
	MyArray(int capacity);

	//��������
	MyArray(const MyArray & arr);

	//β��
	void pushBack(int val);

	//����λ����������
	void setData(int index , int val);

	//����λ�û�ȡ����
	int getData(int index);

	//��ȡ�����С
	int getSize();

	//��ȡ��������
	int getCapacity();

	//����[]�����
	int& operator[](int index);


	//��������
	~MyArray();



private:
	//ָ�����������ָ��
	int * pAddress;

	//��������
	int m_Capacity;

	//�����С
	int m_Size;

};