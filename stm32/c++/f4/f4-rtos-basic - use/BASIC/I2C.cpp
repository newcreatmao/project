#include "I2C.hpp"

void I2C_basic::I2C_init(GROUP SCL_init,GROUP SDA_init){
	this->SCL.GPIO_init(SCL_init.RCC_GROUP,SCL_init.GPIO_GROUP,SCL_init.GPIO_PIN_GROUP,ENABLE,GPIO_Mode_OUT,GPIO_Medium_Speed,GPIO_OType_PP);
	this->SDA.GPIO_init(SDA_init.RCC_GROUP,SDA_init.GPIO_GROUP,SDA_init.GPIO_PIN_GROUP,ENABLE,GPIO_Mode_OUT,GPIO_Medium_Speed,GPIO_OType_PP);
	SCL.PIN_HIGH(SCL.GPIO_PIN_GROUP);
	SDA.PIN_HIGH(SDA.GPIO_PIN_GROUP);
}

void I2C_basic::I2C_start(){
	SDA.PIN_HIGH(SDA.GPIO_PIN_GROUP);
	SCL.PIN_HIGH(SCL.GPIO_PIN_GROUP);
	delay_us(4);
	SDA.PIN_Low(SDA.GPIO_PIN_GROUP);
	delay_us(4);
	SCL.PIN_Low(SCL.GPIO_PIN_GROUP);
}

void I2C_basic::I2C_stop(){
	SCL.PIN_Low(SCL.GPIO_PIN_GROUP);	
	SDA.PIN_Low(SDA.GPIO_PIN_GROUP);
	delay_us(4);
	SDA.PIN_HIGH(SDA.GPIO_PIN_GROUP);
	SCL.PIN_HIGH(SCL.GPIO_PIN_GROUP);
	delay_us(4);
}

void I2C_basic::I2C_sendbyte(uint8_t Byte){
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		(Byte & (0x80 >> i))==1?SDA.PIN_HIGH(SDA.GPIO_PIN_GROUP):SDA.PIN_Low(SDA.GPIO_PIN_GROUP);
		SCL.PIN_HIGH(SCL.GPIO_PIN_GROUP);
		SCL.PIN_Low(SCL.GPIO_PIN_GROUP);	
	}
	SCL.PIN_HIGH(SCL.GPIO_PIN_GROUP);	//额外的一个时钟，不处理应答信号
	SCL.PIN_Low(SCL.GPIO_PIN_GROUP);	
}