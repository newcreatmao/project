#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
设计立方体类(Cube)，求出立方体的面积( 2*a*b + 2*a*c + 2*b*c )和体积( a * b * c)，
分别用全局函数和成员函数判断两个立方体是否相等。
*/

class Cube
{
public:
	//设置长
	void setL(int L)
	{
		m_L = L;
	}

	//获取长
	int getL()
	{
		return m_L;
	}

	//设置宽
	void setW(int W)
	{
		m_W = W;
	}
	//获取宽
	int getW()
	{
		return m_W;
	}

	//设置高
	void setH(int H)
	{
		m_H = H;
	}
	//获取高
	int getH()
	{
		return m_H;
	}

	//求立方体面积
	int calculateS()
	{
		return 2 * m_L*m_W + 2 * m_W *m_H + 2 * m_L *m_H;
	}

	//求立方体体积
	int calculateV()
	{
		return m_L * m_W * m_H;
	}


	//通过成员函数 判断两个立方体关系
	bool compareCubeByClass(Cube & c)
	{
		//if ( m_L == c.getL() && m_W == c.getW() && m_H == c.getH())
		//{
		//	return true;
		//}
		//return false;

		return m_L == c.getL() && m_W == c.getW() && m_H == c.getH();
	}

	//成员属性
private:
	int m_L; //长
	int m_W; //宽
	int m_H; //高

};


//利用全局函数判断两个立方体是否相等
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
	//属性赋值
	c1.setL(10);
	c1.setW(10);
	c1.setH(10);

	//获取面积
	cout << "c1的面积为： " << c1.calculateS() << endl;
	//获取体积
	cout << "c1的体积为： " << c1.calculateV() << endl;

	Cube c2;
	//属性赋值
	c2.setL(10);
	c2.setW(10);
	c2.setH(10);
	
	//利用全局函数 判断 c1和c2关系
	bool ret = compareCube(c1, c2);
	if (ret)
	{
		cout << "c1和c2是相等的" << endl;
	}
	else
	{
		cout << "c1和c2是不相等的" << endl;
	}

	//利用成员函数 判断 c1 和 c2 关系
	ret = c1.compareCubeByClass(c2);
	if (ret)
	{
		cout << "成员函数判断结果：c1和c2是相等的" << endl;
	}
	else
	{
		cout << "成员函数判断结果：c1和c2是不相等的" << endl;
	}


}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}