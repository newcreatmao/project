#include "include.h"                  // Device header
float pitch,roll,yaw;
char buf[1024];
int main(){
	delay_init(168);			//—” ±≥ı ºªØ  
	LCD_Init();
		LCD_Clear(WHITE);
		POINT_COLOR=RED;
	LCD_ShowNum(10,100,mpu_dmp_init(),1,16);
	while (1)
	{
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		sprintf(buf,"pitch=%.2f,roll=%.2f,yaw=%.2f",pitch,roll,yaw);
		LCD_Clear(WHITE);
		POINT_COLOR=RED;	   					 
		LCD_ShowString(30,130,200,12,12,buf);	   
		delay_ms(1000);	
	} 
}

