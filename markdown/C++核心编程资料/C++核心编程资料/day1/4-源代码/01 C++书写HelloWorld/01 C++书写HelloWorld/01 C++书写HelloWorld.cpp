#include <iostream> // 标准输入输出流  i -- input 输入   o  -- output 输出  类似于stdio 
using namespace std; //使用 标准 命名空间     打开一个房间


//#include <math.h>
//#include <cmath>
//
//#include <time.h>
//#include <ctime>

//程序入口函数
int main()
{
	//cout  输出流对象  向屏幕中输出内容
	// <<在C++中可以有新的意义 ，可以在cout后拼接想输出的内容
	// endl 结束输入并且换行
	// 不需要记 %d  %s  %c  %f 格式化
	// 对于换行  \n  \r\n  C++下 只需要记住 endl
	cout << "hello world" << 12345 << endl;

	system("pause"); //阻塞
	return EXIT_SUCCESS; 

}
