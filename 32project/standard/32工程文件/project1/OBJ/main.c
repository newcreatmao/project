#include "stm32f10x.h"// Device header
#include"OLED.H"
// #include"usartbao.h"
// #include "INTERR.h"
// #include "timer.h"

// uint8_t Keynum;
// uint16_t num;
// int main()
// {
// //	int a[2]={1,2};int b[2]={1,11};
// //	LED_INIT('A',2,a);
// //	KEY_INIT('B',2,b);
// //	GPIO_SetBits(GPIOA, GPIO_Pin_1);
// //	while(1)
// //	{
// //	Keynum=KEY_GETNUM();
// //	if(Keynum==1)		
// //	{
// //		GPIO_SetBits(GPIOA, GPIO_Pin_1);
// //	}
// //	if(Keynum==2)
// //	{GPIO_ResetBits(GPIOA, GPIO_Pin_1);}
// //}
// 	OLED_Init();
// 	countsensor_init();
// 	OLED_ShowString(1,1,"count:");
// 	while(1)
// 	{
// 		OLED_ShowNum(1,7,countsensor_get(),5);
// 	}
// 	Timer_init();
// //OLED_Init();
// //OLED_ShowString(1,1,"NUM:");
// //while(1)
// //{
// //	OLED_ShowNum(1,5,num,5);
// //	OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
// //}

// //Timer_Init();
// //OLED_Init();
// //OLED_ShowString(1,1,"NUM:");
// //while(1)
// //{
// //	OLED_ShowNum(1,5,num,5);
// //	OLED_ShowNum(2,5,Time_getcount(),5);

// //}
// //	OLED_Init();
// //	PWM_init();
// //	unsigned char angle1;
// //	while(1)
// //	{
// //		for(angle1=0;angle1<=100;angle1++)
// //		{
// //			PWMCCR(angle1);
// //			Delay_ms(10);
// //		}
// //				for(angle1=0;angle1<=100;angle1++)
// //		{
// //			PWMCCR(100-angle1);
// //			Delay_ms(10);
// //		}
// //	}
// //OLED_Init();
// //PWM_init();
// //PWMIC_init();
// //PWMPSC(7200-1);
// //PWMCCR(80);//×¢ÒâË³Ðò
// //while(1)
// //{
// //	OLED_ShowNum(1,1,ICgetHZ(),5);
// //	OLED_ShowNum(2,1,ICgetDUTY(),3);
// //}

// //OLED_Init();
// //USART_INIT_RX();
// //while(1)
// //{
// //	num=revice();
// //	OLED_ShowHexNum(1,1,num,4);
// //}
// /*OLED_Init();
// USART_INIT_baoRX();
// while(1)
// {
// 	if(GETRX_flag1()==1)
// 	{
// 		OLED_ShowNum(2,1,RXPacket[0],2);
// 		OLED_ShowNum(3,4,RXPacket[1],2);
// 		OLED_ShowNum(1,7,RXPacket[2],2);
// 		OLED_ShowNum(4,10,RXPacket[3],2);
// 	}
// };*/
// }
int main()
{
	OLED_Init();
	for(;;)
	{
	OLED_ShowString(1,1,"Ã©ÖÇÈ¨");
}
	}