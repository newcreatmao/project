#ifndef CLABEL_H
#define CLABEL_H
 
//���� x y w h content
//��Ϊ: show()
 
class CLabel   
{
public:
	//Ĭ�Ϲ���
	CLabel();
	//��������
	~CLabel();
	//���ι���
	CLabel(int x,int y,int w,int h,char pcontent[20]);
	//��������
	//CLabel(CLabel &lab);//��Ϊ���ݳ�Ա����ָ�� �Լ����忽������
	void show();
private:  
	int startX;
	int startY;
	int width;
	int height;
	char content[20];  //����  ���� ϵͳ���ռ�
};
 
#endif