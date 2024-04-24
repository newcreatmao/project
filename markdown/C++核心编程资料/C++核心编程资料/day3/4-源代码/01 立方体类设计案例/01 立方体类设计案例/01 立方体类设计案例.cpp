#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
�����������(Cube)���������������( 2*a*b + 2*a*c + 2*b*c )�����( a * b * c)��
�ֱ���ȫ�ֺ����ͳ�Ա�����ж������������Ƿ���ȡ�
*/

class Cube
{
public:
	//���ó�
	void setL(int L)
	{
		m_L = L;
	}

	//��ȡ��
	int getL()
	{
		return m_L;
	}

	//���ÿ�
	void setW(int W)
	{
		m_W = W;
	}
	//��ȡ��
	int getW()
	{
		return m_W;
	}

	//���ø�
	void setH(int H)
	{
		m_H = H;
	}
	//��ȡ��
	int getH()
	{
		return m_H;
	}

	//�����������
	int calculateS()
	{
		return 2 * m_L*m_W + 2 * m_W *m_H + 2 * m_L *m_H;
	}

	//�����������
	int calculateV()
	{
		return m_L * m_W * m_H;
	}


	//ͨ����Ա���� �ж������������ϵ
	bool compareCubeByClass(Cube & c)
	{
		//if ( m_L == c.getL() && m_W == c.getW() && m_H == c.getH())
		//{
		//	return true;
		//}
		//return false;

		return m_L == c.getL() && m_W == c.getW() && m_H == c.getH();
	}

	//��Ա����
private:
	int m_L; //��
	int m_W; //��
	int m_H; //��

};


//����ȫ�ֺ����ж������������Ƿ����
bool compareCube( Cube &c1 ,Cube &c2 )
{
	if (c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH())
	{
		return true;
	}
	return false;
}


void test01()
{
	Cube c1;
	//���Ը�ֵ
	c1.setL(10);
	c1.setW(10);
	c1.setH(10);

	//��ȡ���
	cout << "c1�����Ϊ�� " << c1.calculateS() << endl;
	//��ȡ���
	cout << "c1�����Ϊ�� " << c1.calculateV() << endl;

	Cube c2;
	//���Ը�ֵ
	c2.setL(10);
	c2.setW(10);
	c2.setH(10);
	
	//����ȫ�ֺ��� �ж� c1��c2��ϵ
	bool ret = compareCube(c1, c2);
	if (ret)
	{
		cout << "c1��c2����ȵ�" << endl;
	}
	else
	{
		cout << "c1��c2�ǲ���ȵ�" << endl;
	}

	//���ó�Ա���� �ж� c1 �� c2 ��ϵ
	ret = c1.compareCubeByClass(c2);
	if (ret)
	{
		cout << "��Ա�����жϽ����c1��c2����ȵ�" << endl;
	}
	else
	{
		cout << "��Ա�����жϽ����c1��c2�ǲ���ȵ�" << endl;
	}


}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}