#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//������
class Animal
{
public:
	int m_Age; //����
};

//virtual���Ϻ� �̳з�ʽ ������̳�
// Animal�� ��Ϊ �����
//����
class Sheep : virtual public Animal
{

};

//�� 
class Tuo : virtual public Animal
{

};

//����
class SheepTuo : public Sheep, public Tuo
{

};

void test01()
{
	SheepTuo st;
	st.Sheep::m_Age = 10;
	st.Tuo::m_Age = 20;

	cout << "age = " << st.Sheep::m_Age << endl;
	cout << "age = " << st.Tuo::m_Age << endl;
	cout << "age = " << st.m_Age << endl;
	//m_Ageֻ��Ҫһ�ݼ��ɣ����μ̳е���������һ���˷�

}

//��̳��ڲ�����ԭ��
void test02()
{
	SheepTuo st;
	st.m_Age = 100;


	//ͨ��sheep�ҵ�ƫ����ֵ
	cout << "ͨ��sheep�ҵ���ƫ����Ϊ:" << *(int *)((int*)*(int *)&st + 1) << endl;

	//ͨ��Tuo�ҵ�ƫ����ֵ
	cout << "ͨ��Tuo�ҵ���ƫ����Ϊ��" << *(int *)((int*)*((int *)&st + 1) + 1) << endl;
	
	//ͨ��ƫ���� ���m_Age��ֵ
	cout << "age =  " << ((Animal *)((char *)&st + (*(int *)((int*)*(int *)&st + 1))))->m_Age << endl;

}

int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}