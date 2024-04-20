#ifndef CBUTTON_H
#define CBUTTON_H
 
//属性 x y w h content
//行为: show()
 
class CButton   
{
public:
    //构造函数
	CButton();
	//拷贝函数
//	CButton(CButton &button);
    //带参数的构造
	CButton(int x,int y,int w,int h,char pcontent[]);
	//析构函数
	~CButton();
	void show();	
private:  
	int startX;
	int startY;
	int width;
	int height;
	char content[20];  //内容
};
 
#endif