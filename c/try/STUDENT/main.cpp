#include <iostream>
#include"User.hpp"
using namespace std;
int main() {
    system("title student");//设置窗口名
    system("color 70");
    Funtion_select();
    system("pause");
    cout<<"程序运行完毕"<<endl;
    return 0;
}


// system()在头文件stdlib.h中

// system()是C语言中为了调用windows系统命令来设置。

// 例：

// system(“color Xx”);//第一个大叉用来控制背景色，第二个用来控制字体色

// system(“cls”);//清屏

// system(“pause”);//暂停



// system(“start 地址”);//打开某程序

// system(“mode 数字1,数字2”);//控制窗口的大小，数字1控制长，数字2控制高。

// system(“mode con cols=数字1 lines=数字2”);//控制窗口的大小，数字1控制长，数字2控制高。