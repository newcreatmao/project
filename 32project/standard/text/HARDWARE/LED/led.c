#include "led.h"
//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{ 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
}

void Use_lock_init(void){
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PD端口时钟
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_13|GPIO_Pin_11|GPIO_Pin_12;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化
	 GPIO_SetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_13|GPIO_Pin_11|GPIO_Pin_12);	//输出高
}//电磁锁初始化，使其一开始为上锁状态

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
