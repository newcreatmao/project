#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#define MYADD(x,y) ((x)+(y))
//ȱ��1����֤����������  ��Ҫ��С��������
void test01()
{
	int a = 10;
	int b = 20;
	int ret = MYADD(a, b) * 20; //Ԥ��600  չ����  ((10) + (20)) * 20
	cout << "a + b = " << ret << endl;;
}

//ȱ��2����ʹ�����������Σ���Щ�����Ȼ�����ֺ�Ԥ�ڲ����Ľ��
#define  MYCOMPARE(a,b)  (((a) < (b)) ? (a) : (b))

inline int myCompare(int a, int b)
{

	return a < b ? a : b;
}

void test02()
{
	int a = 10;
	int b = 20;

	//int ret = MYCOMPARE(++a, b); // Ԥ�ڽ�� 11   (((++a) < (b)) ? (++a) : (b))   
	int ret = myCompare(++a, b);
	cout << "ret = " << ret << endl;

}

//ȱ��3  �꺯�� ������������



//�������� inline 
// ������������ʵ�ֱ���ͬʱ����inline�ؼ������򲻻ᰴ��������ʽ����
inline void func();
inline void func(){  };

//��Ա����ǰ�� ���صļ����� inline�ؼ���

int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}