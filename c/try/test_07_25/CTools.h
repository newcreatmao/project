#ifndef CTOOLS_H
#define CTOOLS_H
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
 
void paintWindow(int startX,int startY,int width,int height);//打印窗口
 
void gotoxy(int x,int y);//形参  光标定位
 
/*
函数功能：字符串输入控制
函数参数：
int maxLen 允许输入最大长度
int inputType 允许输入的字符类型  0：数字 1：字母 2：字母+数字
int ips       数据显示格式        0：密文  1：明文
char str[] 存储输入字符
函数返回值：无
char str[]    char str[20]    char*str
*/
void glb_string(int maxLen,int inputType,int ips,char str[]); 
 
/*
函数名：int getkey()
函数功能：获取用户输入的任意键盘值
函数参数：无
函数返回：ascii  
*/
int getkey();
 
#endif