#pragma once
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
class GPIO_BASIC {
	public:
		GPIO_BASIC(uint32_t RCC_,GPIO_TypeDef* GPIO,\
							 uint32_t GPIO_PIN,FunctionalState flag,GPIOMode_TypeDef M,\
							 GPIOSpeed_TypeDef S,GPIOOType_TypeDef O,GPIOPuPd_TypeDef P=GPIO_PuPd_NOPULL);
		void GPIO_INIT();
		void PIN_HIGH(uint16_t GPIO_PIN);
		void PIN_Low(uint16_t GPIO_PIN);
	protected:
		
	private:
		uint32_t RCC_GROUP;
		GPIO_TypeDef* GPIO_GROUP;
		uint32_t GPIO_PIN_GROUP;
		FunctionalState FLAG;
		GPIOMode_TypeDef Mode;    
		GPIOSpeed_TypeDef Speed;  
		GPIOOType_TypeDef OType;   
		GPIOPuPd_TypeDef PuPd;
};

