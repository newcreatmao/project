#ifndef CEDIT_H
#define CEDIT_H
 
class CEdit
{
public :
	CEdit();  
	CEdit(int x,int y,int w ,int h,char *pcontent,int maxLen,int inputType,int ips);
	void show();
private:
	int startX;
	int startY;
	int width;
	int height;
	char content[20];  //内容
 
	int inputType;  //输入的类型
	int maxLen;     //最大长度
	int ips;        //明文密文
};
 
#endif