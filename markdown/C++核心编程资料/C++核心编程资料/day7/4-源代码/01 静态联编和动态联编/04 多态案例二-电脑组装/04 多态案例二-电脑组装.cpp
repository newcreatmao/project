#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//�����
//�����CPU
class CPU
{
public:
	virtual void calculate() = 0;
};

//������Կ�
class VideoCard
{
public:
	virtual void display() = 0;
};
//������ڴ�
class Memory
{
public:
	virtual void storge() = 0;
};

//������
class computer
{
public:
	computer(CPU * cpu, VideoCard *card, Memory *mem)
	{
		this->cpu = cpu;
		this->card = card;
		this->memory = mem;
	}

	//�õ��Թ���
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


//ʵ�ֲ�
//intel��CPU
class intelCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "intel��CPU��ʼ������" << endl;
	}
};
//intel���Կ�
class intelVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "intel���Կ���ʼ��ʾ��" << endl;
	}
};
//intel���ڴ�
class intelMemory :public Memory
{
public:
	virtual void storge()
	{
		cout << "intel���ڴ�����ʼ�洢��" << endl;
	}

};

//  Lenovo ���̵����
//Lenovo��CPU
class LenovoCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Lenovo��CPU��ʼ������" << endl;
	}
};
//Lenovo���Կ�
class LenovoVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo���Կ���ʼ��ʾ��" << endl;
	}
};
//Lenovo���ڴ�
class LenovoMemory :public Memory
{
public:
	virtual void storge()
	{
		cout << "Lenovo���ڴ�����ʼ�洢��" << endl;
	}
};



void test01()
{
	//��һ̨������װ
	cout << "��һ̨������װ��" << endl;
	CPU * intel= new intelCPU;
	VideoCard * card = new intelVideoCard;
	Memory * mem = new intelMemory;

	computer * computer1 = new computer(intel, card, mem);
	computer1->doWork();

	delete computer1;

	//�ڶ�̨������װ
	cout << "----------------" << endl;
	cout << "�ڶ�̨������װ��" << endl;
	CPU * intel2 = new LenovoCPU;
	VideoCard * card2 = new LenovoVideoCard;
	Memory * mem2 = new LenovoMemory;
	computer * computer2 = new computer(intel2, card2, mem2);
	computer2->doWork();

	delete computer2;

	//����̨����
	cout << "----------------" << endl;
	cout << "����̨������װ��" << endl;
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