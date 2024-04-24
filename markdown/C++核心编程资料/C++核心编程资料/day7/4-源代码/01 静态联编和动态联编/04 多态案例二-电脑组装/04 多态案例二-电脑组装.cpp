#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//抽象层
//抽象的CPU
class CPU
{
public:
	virtual void calculate() = 0;
};

//抽象的显卡
class VideoCard
{
public:
	virtual void display() = 0;
};
//抽象的内存
class Memory
{
public:
	virtual void storge() = 0;
};

//电脑类
class computer
{
public:
	computer(CPU * cpu, VideoCard *card, Memory *mem)
	{
		this->cpu = cpu;
		this->card = card;
		this->memory = mem;
	}

	//让电脑工作
	void doWork()
	{
		this->cpu->calculate();
		this->card->display();
		this->memory->storge();
	}

	~computer()
	{
		if (this->cpu != NULL)
		{
			delete this->cpu;
			this->cpu = NULL;
		}
		if (this->card != NULL)
		{
			delete this->card;
			this->card = NULL;
		}
		if (this->memory != NULL)
		{
			delete this->memory;
			this->memory = NULL;
		}
	
	}

	CPU * cpu;
	VideoCard * card;
	Memory * memory;
};


//实现层
//intel的CPU
class intelCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "intel的CPU开始计算了" << endl;
	}
};
//intel的显卡
class intelVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "intel的显卡开始显示了" << endl;
	}
};
//intel的内存
class intelMemory :public Memory
{
public:
	virtual void storge()
	{
		cout << "intel的内存条开始存储了" << endl;
	}

};

//  Lenovo 厂商的零件
//Lenovo的CPU
class LenovoCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Lenovo的CPU开始计算了" << endl;
	}
};
//Lenovo的显卡
class LenovoVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了" << endl;
	}
};
//Lenovo的内存
class LenovoMemory :public Memory
{
public:
	virtual void storge()
	{
		cout << "Lenovo的内存条开始存储了" << endl;
	}
};



void test01()
{
	//第一台电脑组装
	cout << "第一台电脑组装后：" << endl;
	CPU * intel= new intelCPU;
	VideoCard * card = new intelVideoCard;
	Memory * mem = new intelMemory;

	computer * computer1 = new computer(intel, card, mem);
	computer1->doWork();

	delete computer1;

	//第二台电脑组装
	cout << "----------------" << endl;
	cout << "第二台电脑组装后：" << endl;
	CPU * intel2 = new LenovoCPU;
	VideoCard * card2 = new LenovoVideoCard;
	Memory * mem2 = new LenovoMemory;
	computer * computer2 = new computer(intel2, card2, mem2);
	computer2->doWork();

	delete computer2;

	//第三台电脑
	cout << "----------------" << endl;
	cout << "第三台电脑组装后：" << endl;
	CPU * intel3 = new intelCPU;
	VideoCard * card3 = new LenovoVideoCard;
	Memory * mem3 = new LenovoMemory;
	computer * computer3 = new computer(intel3, card3, mem3);
	computer3->doWork();

}



int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}