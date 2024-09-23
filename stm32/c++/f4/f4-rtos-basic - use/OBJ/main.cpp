#include "sys.hpp"                  // Device header
TaskHandle_t taskHandler1,taskHandler2;
int i=0;
I2C_basic OLED;
void task1(void * arg){
	 while(1){

		 vTaskDelay(300);
		 GPIO_SetBits(GPIOB,GPIO_Pin_8);
		 vTaskDelay(200);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	 }
}

void task2(void * arg){
	 while(1){
		 GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		 vTaskDelay(500);
		 GPIO_SetBits(GPIOB,GPIO_Pin_9);
		 vTaskDelay(500);
		 i++;
		 if(i>5){
			 vTaskDelete(taskHandler1);
		 }
	 }
}

int main(){
	GROUP SCL,SDA;
	SCL.RCC_GROUP=RCC_AHB1Periph_GPIOB;SCL.GPIO_GROUP=GPIOB;SCL.GPIO_PIN_GROUP=GPIO_Pin_8;
	SDA.RCC_GROUP=RCC_AHB1Periph_GPIOB;SDA.GPIO_GROUP=GPIOB;SDA.GPIO_PIN_GROUP=GPIO_Pin_9;
	OLED.I2C_init(SCL,SDA);
	xTaskCreate(task1,"task1",512,NULL,1,&taskHandler1);
	xTaskCreate(task2,"task2",512,NULL,2,&taskHandler2);
	vTaskStartScheduler();
	while (1)
	{
	}
}