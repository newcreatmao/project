#include "led.h"
//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{ 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����, �������
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 ����� 
}

void Use_lock_init(void){
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_13|GPIO_Pin_11|GPIO_Pin_12;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��
	 GPIO_SetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_13|GPIO_Pin_11|GPIO_Pin_12);	//�����
}//�������ʼ����ʹ��һ��ʼΪ����״̬

void Open_lock(int num){
	if(num==1)
		 GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	else if(num==2)
		 GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	else if(num==3)
		 GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	else if(num==4)
		 GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	else if(num==5)
		 GPIO_ResetBits(GPIOC,GPIO_Pin_12);
}

void Lock(int num){
	if(num==1)
		 GPIO_SetBits(GPIOC,GPIO_Pin_1);
	else if(num==2)
		 GPIO_SetBits(GPIOC,GPIO_Pin_4);
	else if(num==3)
		 GPIO_SetBits(GPIOC,GPIO_Pin_13);
	else if(num==4)
		 GPIO_SetBits(GPIOC,GPIO_Pin_11);
	else if(num==5)
		 GPIO_SetBits(GPIOC,GPIO_Pin_12);
}
