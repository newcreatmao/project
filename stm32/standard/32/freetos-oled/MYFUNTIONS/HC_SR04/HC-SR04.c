#include "HC-SR04.h"

#define HCSR04_PORT     GPIOA
#define HCSR04_CLK      RCC_APB2Periph_GPIOA
#define HCSR04_TRIG     GPIO_Pin_5
#define HCSR04_ECHO     GPIO_Pin_6
 
#define TRIG_Send(x)  GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)(x)) 
#define ECHO_Reci  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)


u16 msHcCount = 0;


void Hcsr04Init()
{      
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	
    RCC_APB2PeriphClockCmd(HCSR04_CLK, ENABLE);
     
    //IO�ڳ�ʼ��
    GPIO_InitStructure.GPIO_Pin =HCSR04_TRIG;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //����IO�����ģʽΪ������� 
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
	
    //IO�ڳ�ʼ��
    GPIO_InitStructure.GPIO_Pin =   HCSR04_ECHO;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //����IO������ģʽ�������� 
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);  
	GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);	
 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //ʹ�ܶ�ʱ��ʱ��

	TIM_TimeBaseStructure.TIM_Period = (1000-1);//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1);   //����������ΪTIM3ʱ��Ƶ�ʳ�����Ԥ��Ƶ         
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;    //����ʱ�ӷָ� 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ָ���Ĳ�����ʼ��TIM3��ʱ�������λ
		
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 	 
		
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    //ʹ��ָ����TIM3�жϣ��򿪸����ж�
		
	 //�ж����ȼ�NVIC����
	 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //���ô����ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);   //��ʼ��NVIC�Ĵ���
		
	TIM_Cmd(TIM3,DISABLE);     
}
 
 

void OpenTimer()       
{
	TIM_SetCounter(TIM3,0); //����TIM3�����Ĵ�����ֵ
	msHcCount = 0;   
	TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ��TIM3
}
 
void CloseTimer()        
{
	TIM_Cmd(TIM3, DISABLE);   //ֹͣʹ�ܶ�ʱ��TIM3
}
 
 
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//���TIM3�ĸ����ж��Ƿ���
	{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIM3�����жϱ�־     
			msHcCount++;
	}
}
 
 

u32 GetEchoTimer(void)
{
	u32 t = 0;
	t = msHcCount*1000;    //��ʱ��ת��Ϊ΢��
	t += TIM_GetCounter(TIM3);//��ȡ��ǰ��������ֵ  
	TIM3->CNT = 0; //���������
	Delay_ms(50);
	return t;
}
 
 

float Hcsr04GetLength(void )
{
	u32 t = 0;
	int i = 0;
	float lengthTemp = 0;
	float sum = 0;
	while(i!=5)
	{
		TRIG_Send(1);      //IO��PA5���һ���ߵ�ƽ
		Delay_us(20);
		TRIG_Send(0);   //IO��PA5���һ���͵�ƽ
		while(ECHO_Reci == 0);     
		OpenTimer();   //��ʼ��ʱ 
		i = i + 1;
		while(ECHO_Reci == 1);
		CloseTimer();  //������ʱ  
		t = GetEchoTimer();        
		lengthTemp = ((float)t/58.0);   //���㵥���������
		sum = lengthTemp + sum ;   
	}
	lengthTemp = sum/5.0;   //����ξ���ƽ��ֵ
	return lengthTemp;
}
 


