#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//利用选择排序实现 对 int和char数组排序 , 从小到大

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
				min = j; //记录真实最小值下标
			}
		}
		//判断最小值下标和开始认定的i是否相等，如果不等交换 i和 min下标的数据
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

	//打印数组
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