#ifndef CBUTTON_H
#define CBUTTON_H
 
//���� x y w h content
//��Ϊ: show()
 
class CButton   
{
public:
    //���캯��
	CButton();
	//��������
//	CButton(CButton &button);
    //�������Ĺ���
	CButton(int x,int y,int w,int h,char pcontent[]);
	//��������
	~CButton();
	void show();	
private:  
	int startX;
	int startY;
	int width;
	int height;
	char content[20];  //����
};
 
#endif