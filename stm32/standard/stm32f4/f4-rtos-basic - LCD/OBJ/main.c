#include "include.h"                  // Device header

int main(){
	delay_init(168);			//��ʱ��ʼ��  
	LCD_Init();
	while (1)
	{
		LCD_Clear(WHITE);
		POINT_COLOR=RED;
		
		delay_ms(1000);	
	} 
}
