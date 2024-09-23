#ifndef I2C__HPP_
#define I2C__HPP_

#include "sys.hpp"

class IO_init{
	IO_init(uint32_t RCC,GPIO_TypeDef* GPIO,uint32_t GPIO_PIN,FunctionalState flag,GPIOMode_TypeDef M,GPIOSpeed_TypeDef S,GPIOOType_TypeDef O,GPIOPuPd_TypeDef P=GPIO_PuPd_NOPULL);
	public:
		 
	protected:
		uint32_t RCC_GROUP;
		GPIO_TypeDef* GPIO_GROUP;
		uint32_t GPIO_PIN_GROUP;
		FunctionalState FLAG;
		GPIOMode_TypeDef Mode;    
		GPIOSpeed_TypeDef Speed;  
		GPIOOType_TypeDef OType;   
		GPIOPuPd_TypeDef PuPd;
};

class I2C_BASE{
	public:
		int a;
	
	
};



#endif