#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

namespace kingGlory
{
	int sunwukongId = 1;
}

void test01()
{
	int sunwukongId = 2;

	//1��using ����
	//���ͽ�ԭ�� �� using����ͬʱ����ʱ�� ����Ҫ���������
	//using kingGlory::sunwukongId;

	//cout << "sunwukongId = " << kingGlory::sunwukongId << endl;
}


namespace LOL
{
	int sunwukongId = 3;
}

void test02()
{
	//int sunwukongId = 2;

	//2��using ����ָ��
	using namespace kingGlory;
	using namespace LOL;

	//����оͽ�ԭ����� ����ô����ʹ�þͽ�ԭ��
	//���using����ָ�� ���ڶ��������ͬ�����֣���Ҫ������������
	cout << "sunwukongId = " << LOL::sunwukongId << endl;
}



int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}