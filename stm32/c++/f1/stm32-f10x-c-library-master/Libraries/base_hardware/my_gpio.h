/**************************************************************************
 * @brief       : STM32 GPIO 操作
 * @author      : 龚为玮(1461041096)
 * @copyright   : 版权信息
 * @version     : v1.0
 * @note        : 无
 * @history     : 2021年11月19日：创建文件，完成GPIO口的初始化、读、写翻转，并
 *                               利用输出口E5,B5、输入口A0,E3,E4验证部分功能
 *                               测试通过
 *                2021年11月20日：添加注释
 *                2021年11月20日：修改GPIO输出函数所调用的底层库函数
 *                2021年11月22日：修改注释
 *                2021年11月30日：添加初始化GPIO外部中断，测试通过
 *                2021年12月2日： 修改了外部中断初始化接口，将中断服务函数移到
 *                               上层的库中
 *                2021年1月4日：  优化外部中断初始化接口，优化了代码的封装结构，
 *                                将中断服务函数移了回来。
 ***************************************************************************/
#ifndef __MY_GPIO_H
#define __MY_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "resources.h"

/**
* @brief GPIO初始化模式枚举 \n
* INPUT：浮空输入
* INPUT_PULLUP：上拉输入
* INPUT_PULLDOWN：下拉输入
* OUT_PP：推挽输出
* OUT_OD：开漏输出
*/
typedef enum
{
  INPUT = GPIO_Mode_IN_FLOATING,
  INPUT_PULLUP = GPIO_Mode_IPU,
  INPUT_PULLDOWN = GPIO_Mode_IPD,
  OUT_PP = GPIO_Mode_Out_PP,
  OUT_OD = GPIO_Mode_Out_OD
} GPIO_mode;

typedef enum
{
  Rising = EXTI_Trigger_Rising,
  Falling = EXTI_Trigger_Falling,
  Change = EXTI_Trigger_Rising_Falling
} EXIT_mode;

#define DEFAULT_GPIO_SPEED GPIO_Speed_50MHz //GPIO初始化默认GPIO速度

void gpio_init(Pin_enum pin, GPIO_mode mode);
void gpio_write(Pin_enum pin, uint8_t data);
void gpio_toggle(Pin_enum pin);
void gpio_interrupt_init(Pin_enum pin, void (*callback)(void), EXIT_mode mode);
void gpio_interrupt_deinit(Pin_enum pin);
uint8_t gpio_read(Pin_enum pin);

extern void (*EXTI_Linex_Callback[16])(void);//外部中断回调函数指针

#ifdef __cplusplus
}
#endif

#endif
