#include "IO.hpp"

GPIO_BASIC::GPIO_BASIC(){
	RCC_GROUP=0;
	GPIO_GROUP=0;
	GPIO_PIN_GROUP=0;
	FLAG=DISABLE;
	Mode=GPIO_Mode_IN;
	OType=GPIO_OType_PP;
	Speed=GPIO_Low_Speed;
	PuPd=GPIO_PuPd_NOPULL;
}
void GPIO_BASIC::GPIO_init(uint32_t RCC_,GPIO_TypeDef* GPIO,uint32_t GPIO_PIN,FunctionalState flag,GPIOMode_TypeDef M,GPIOSpeed_TypeDef S,GPIOOType_TypeDef O,GPIOPuPd_TypeDef P){
	RCC_GROUP=RCC_;
	GPIO_GROUP=GPIO;
	GPIO_PIN_GROUP=GPIO_PIN;
	FLAG=flag;
	Mode=M;
	OType=O;
	Speed=S;
	PuPd=P;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_GROUP,FLAG);
	GPIO_InitStruct.GPIO_Mode =	Mode;
	GPIO_InitStruct.GPIO_OType = OType;  
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_GROUP;
	GPIO_InitStruct.GPIO_Speed = Speed;
	GPIO_InitStruct.GPIO_PuPd = PuPd;
  GPIO_Init(GPIO_GROUP,&GPIO_InitStruct);
}



void GPIO_BASIC::PIN_HIGH(uint16_t GPIO_PIN){
	GPIO_SetBits(GPIO_GROUP,GPIO_PIN);
}
void GPIO_BASIC::PIN_Low(uint16_t GPIO_PIN){
	GPIO_ResetBits(GPIO_GROUP,GPIO_PIN);
}