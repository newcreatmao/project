#include "sys.h"                  // Device header

TaskHandle_t taskHandler1,taskHandler2;
int i=0;
void task1(void * arg){
	 while(1){
		 GPIO_ResetBits(GPIOF,GPIO_Pin_8);
		 delay_ms(300);
		 GPIO_SetBits(GPIOF,GPIO_Pin_8);
		 vTaskDelay(200);
	 }
}

void task2(void * arg){
	 while(1){
		 GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		 vTaskDelay(500);
		 GPIO_SetBits(GPIOF,GPIO_Pin_9);
		 vTaskDelay(500);
		 i++;
		 if(i>5){
			 vTaskDelete(taskHandler1);
		 }
	 }
}

int main(){
	Stm32_Clock_Init(360, 25, 2, 8);
	delay_init(GPIO_Speed_100MHz);
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStruct.GPIO_Mode =	GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType =	GPIO_OType_PP;  
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Medium_Speed;
  GPIO_Init(GPIOF,&GPIO_InitStruct);
	xTaskCreate(task1,"task1",512,NULL,1,&taskHandler1);
	xTaskCreate(task2,"task2",512,NULL,2,&taskHandler2);
	vTaskStartScheduler();
	while (1)
	{
	}
}