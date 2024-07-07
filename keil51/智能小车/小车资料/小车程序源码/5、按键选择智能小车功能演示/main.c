/*********************************************************************************
* ����дʱ�䡿�� 2016��12��2��
* ����    �ߡ��� �������:03
* ����    ������ 1.0
* ����    վ���� http://www.qxmcu.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ (ֱ����)
* ��ʵ��ƽ̨���� QX-MCS51 ��Ƭ�������� & QX-A51����С��
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52
* �����뻷������ Keil ��Visio4
* ********************************������˵����********************************
             ����"A_"��ʾ����С���װ�~~~"B_"��ʾ������     
*�����幩����  ��A_J5-VCC~~~B_VCC��5V0    A_J6-GND~~~B_GND ��һ��ʹ��2���Ű��ߣ�
*���������    ��A_J10-P1.2��P1.7 ��Ӧ�ӵ�B_P1.2��P1.7 ��һ��ʹ��6���Ű��ߣ�
*����Ѱ�������ߣ�A_J11-P3.2��P3.5 ��Ӧ�ӵ�B_P3.2��P3.5 ��һ��ʹ��4���Ű��ߣ�
******************************************************************************
* �������ܡ�������ѡ������С��������ʾ  			   			            			    
* ��ʹ��˵�����������������д����򿪵�Դ���ذ���S2��S3����С��ִ����Ӧ���������
* ��ע�����������С��ײ���ϰ����С�����Ӷ�ת��С����ѹ���ܵ���6V
**********************************************************************************/
#include <reg52.h>
#include <..\CONFIG\QXA51.h>

void delay(unsigned int z)//���뼶��ʱ
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}	

/*С��ǰ��*/
void forward()
{
	left_motor_en; //����ʹ��
	right_motor_en;//�ҵ��ʹ��
	left_motor_go; //����ǰ��
	right_motor_go; //�ҵ��ǰ��
}
/*С������*/
void backward()
{
	left_motor_en; //����ʹ��
	right_motor_en;//�ҵ��ʹ��
	left_motor_back; //��������
	right_motor_back; //�ҵ������	
}
/*С����ת*/
void left()
{
	left_motor_stops; //����ֹͣ
	right_motor_en;//�ҵ��ʹ��
	right_motor_go; //�ҵ��ǰ��	
}
/*С����ת*/
void right()
{
	right_motor_stops;//�ҵ��ֹͣ
	left_motor_en;    //����ʹ��
	left_motor_go;    //����ǰ��
}

/*С��ֹͣ*/
void stop()
{
	right_motor_stops;//�ҵ��ֹͣ
	left_motor_stops; //����ֹͣ	
}
/*С��������ת*/
void left_rapidly()
{
	left_motor_en; //����ʹ��
	right_motor_en;//�ҵ��ʹ��
	right_motor_go;
	left_motor_back;	
}
/*С��������ת*/
void right_rapidly()
{
	left_motor_en; //����ʹ��
	right_motor_en;//�ҵ��ʹ��
	left_motor_go;
	right_motor_back;	
}

void main()
{
	unsigned char i;
	while(1)
	{
		if(key_s2 == 0)//�ж�S2�Ƿ���
		{
			delay(5);//�������
			if(key_s2 == 0)
			{
				beep = 0;
				delay(1000); //��������1��
				beep = 1;
	
				forward();//С��ǰ��
				delay(3000);//���뼶��ʱ
			
				stop();//С��ֹͣ
				delay(3000);//���뼶��ʱ
			
				backward();//С������
				delay(3000);//���뼶��ʱ
			
				stop();//С��ֹͣ
				delay(3000);//���뼶��ʱ
			
				left();	// С����ת
				delay(3000);//���뼶��ʱ
				
				stop();//С��ֹͣ
				delay(3000);//���뼶��ʱ
				
				right();// С����ת
				delay(3000);//���뼶��ʱ
			
				stop();//С��ֹͣ
				delay(3000);//���뼶��ʱ
			
				left_rapidly();//С��������ת
				delay(3000);//���뼶��ʱ
			
				stop();//С��ֹͣ
				delay(3000);//���뼶��ʱ
			
				right_rapidly();//С��������ת
				delay(3000);//���뼶��ʱ
				
				stop();//С��ֹͣ		
			}
		}

		if(key_s3 == 0)	//�ж�S3�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s3 == 0)
			{
				beep = 0;
				delay(1000); //��������1��
				beep = 1;
			    for(i=0; i<4; i++)	//ִ��4��
				{
					forward();
					delay(2000); //ǰ��2��
					
					stop();
					delay(500);	 //ֹͣ0.5��
					
					left();
					delay(200);	 //��ת����ʱԽ��ת��Ƕ�Խ��
					
					stop();		 //ͣ0.5��
					delay(500);	
				}
			}
		}
	}	
}
