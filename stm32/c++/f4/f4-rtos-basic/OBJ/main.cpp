#include "sys.hpp"                  // Device header
TaskHandle_t taskHandler1,taskHandler2;
GPIO_BASIC LED(RCC_AHB1Periph_GPIOB,GPIOB,GPIO_Pin_9|GPIO_Pin_8,ENABLE,GPIO_Mode_OUT,GPIO_Medium_Speed,GPIO_OType_PP);
int i=0;
void task1(void * arg){
	 while(1){
		 LED.PIN_HIGH(GPIO_Pin_8);
		 vTaskDelay(500);
		 LED.PIN_Low(GPIO_Pin_9);
		 vTaskDelay(500);
		 
	 }
}

void task2(void * arg){
	 while(1){
		 LED.PIN_HIGH(GPIO_Pin_9);
		 vTaskDelay(500);
		 LED.PIN_Low(GPIO_Pin_8);
		 vTaskDelay(500);
		 i++;
		 if(i>5){
			 vTaskDelete(taskHandler1);
		 }
	 }
}

int main(){
	LED.GPIO_INIT();
	xTaskCreate(task1,"task1",512,NULL,1,&taskHandler1);
	xTaskCreate(task2,"task2",512,NULL,2,&taskHandler2);
	vTaskStartScheduler();
	while (1)
	{
	}
}