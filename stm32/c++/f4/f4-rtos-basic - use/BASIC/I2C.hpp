#ifndef I2C__HPP_
#define I2C__HPP_
#include"sys.hpp"


typedef struct GPIO_GROUP{
	uint32_t RCC_GROUP;
	GPIO_TypeDef* GPIO_GROUP;
	uint32_t GPIO_PIN_GROUP;
}GROUP;

class I2C_basic
{
	I2C_basic();
	public:
		void I2C_init(GROUP SCL_init,GROUP SDA_init);
		void I2C_start();
		void I2C_stop();
		void I2C_sendbyte(uint8_t Byte);
	private:
		GPIO_BASIC SCL;
		GPIO_BASIC SDA;
};

#endif