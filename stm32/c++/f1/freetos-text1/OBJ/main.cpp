#include<stm32f10x.h>
#include"freertos.h"
#include"task.h"

TaskHandle_t taskHandler1,taskHandler2;
int i=0;
void task1(void * arg){
	 while(1){
		 GPIO_ResetBits(GPIOC,GPIO_Pin_14);
		 vTaskDelay(300);
		 GPIO_SetBits(GPIOC,GPIO_Pin_14);
		 vTaskDelay(200);
	 }
}

void task2(void * arg){
	 while(1){
		 GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		 vTaskDelay(500);
		 GPIO_SetBits(GPIOC,GPIO_Pin_13);
		 vTaskDelay(500);
		 i++;
		 if(i>5){
			 vTaskDelete(NULL);
		 }
	 }
}

int main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	xTaskCreate(task1,"task1",512,NULL,1,&taskHandler1);
	xTaskCreate(task2,"task2",512,NULL,2,&taskHandler2);
	vTaskStartScheduler();
	while (1)
	{
	}
}
