/**************************************************************************
  * @brief       : STM32 AFIO(端口复用功能)
  * @author      : 龚为玮(1461041096)  
  * @copyright   : 版权信息
  * @version     : v1.0
  * @note        : 主要作为其他外设函数初始化调用
  * @history     : 2021年11月20日：创建文件，完成基础功能
  *                2021年11月22日：测试，添加注释
***************************************************************************/

#ifndef __MY_AFIO_H
#define __MY_AFIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "resources.h"

#define DEFAULT_AFIO_SPEED GPIO_Speed_50MHz //GPIO初始化默认GPIO速度

typedef enum
{
  INPUT_AF  = GPIO_Mode_AIN,
  OUT_PP_AF = GPIO_Mode_AF_PP,
  OUT_OD_AF = GPIO_Mode_AF_OD
} AFIO_mode;

void afio_init(Pin_enum pin, AFIO_mode mode);

#ifdef __cplusplus
 }
#endif

#endif
