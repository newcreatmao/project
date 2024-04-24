#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//����ѡ������ʵ�� �� int��char�������� , ��С����

template< class T>
void mySwap(T & a, T & b)
{
	T temp = a;
	a = b; 
	b = temp;
}


template< typename T>
void mySort( T arr[] , int len  )
{
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len;j++)
		{
			if (arr[min] > arr[j])
			{
				min = j; //��¼��ʵ��Сֵ�±�
			}
		}
		//�ж���Сֵ�±�Ϳ�ʼ�϶���i�Ƿ���ȣ�������Ƚ��� i�� min�±������
		if (min != i)
		{
			mySwap(arr[i], arr[min]);
		}
	}
}

template<class T>
void printArray(T arr[] , int len)
{
	for (int i = 0; i < len;i++)
	{
		cout << arr[i] << endl;
	}
}

void test01()
{
	int arr[] = { 15, 2, 6, 23, 61 };
	int len = sizeof(arr) / sizeof(int);
	mySort(arr, len);

	//��ӡ����
	printArray(arr, len);


	char charArr[] = "helloworld";
	len = sizeof(charArr) / sizeof(char);
	mySort(charArr, len);
	printArray(charArr, len);

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}