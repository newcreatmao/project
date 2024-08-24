/**************************************************************************
 * @brief       : STM32 systick定时器
 * @author      : 龚为玮(1461041096)
 * @copyright   : 版权信息
 * @version     : v1.0
 * @note        : 无
 * @history     : 2021年11月19日：创建文件 完成延时函数、获取系统运行实现函数
 *                                对延时函数进行了测试，测试通过
 *                2021年11月20日：修改部分函数和宏名，添加注释
 *                2021年11月22日：将滴答定时器溢出中断声明和定义移入
 *                               my_systick.c中
 ***************************************************************************/
#ifndef __MY_SYSTICK_H
#define __MY_SYSTICK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"
#include "core_cm3.h"
#include "resources.h"

#define delay_ms(n) systick_delay(n * 1000) /*!<延时n毫秒(ms)*/
#define delay_us(n) systick_delay(n)        /*!<延时n微秒(us)*/
#define millis() (systick_micors() / 1000)  /*!<获取系统运行到到调用时的毫秒(ms)数*/
#define micors() systick_micors()           /*!<获取系统运行到到调用时的微秒(us)数*/

void systick_init(void);
void systick_delay(uint64_t time);
uint64_t systick_micors(void);

#ifdef __cplusplus
}
#endif

#endif
