#ifndef CLABEL_H
#define CLABEL_H
 
//属性 x y w h content
//行为: show()
 
class CLabel   
{
public:
	//默认构造
	CLabel();
	//析构函数
	~CLabel();
	//带参构造
	CLabel(int x,int y,int w,int h,char pcontent[20]);
	//拷贝构造
	//CLabel(CLabel &lab);//因为数据成员中有指针 自己定义拷贝构造
	void show();
private:  
	int startX;
	int startY;
	int width;
	int height;
	char content[20];  //内容  数组 系统开空间
};
 
#endif