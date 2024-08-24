#ifndef __I2C_H
#define __I2C_H

/**
  * @brief  include
  * @param  ��
  * @retval ��
  */
#include "sys.h"

/**
  * @brief  define
  * @param  ��
  * @retval ��
  */
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(x))
/**
  * @brief  function
  * @param  ��
  * @retval ��
  */
void OLED_I2C_Init(void);
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_SendByte(uint8_t Byte);

#endif
