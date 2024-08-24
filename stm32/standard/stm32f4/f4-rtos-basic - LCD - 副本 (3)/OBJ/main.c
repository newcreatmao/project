#include "include.h"                  // Device header

int main(){
	delay_init(168);			//—” ±≥ı ºªØ  
	LCD_Init();
	while (1)
	{
		LCD_Clear(WHITE);
		POINT_COLOR=RED;	   					 
		LCD_ShowString(30,130,200,12,12,"2014/5/4");	   
//		Chinese_Show_one(100,20,0,16);
//		Chinese_Show_one(116,20,1,16);
		delay_ms(1000);	
	} 
}
