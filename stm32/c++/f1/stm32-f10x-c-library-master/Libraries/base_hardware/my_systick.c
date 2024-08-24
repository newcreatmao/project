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
#include "my_systick.h"
// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

volatile uint64_t TimingDelay = 0; //滴答定时器溢出中断计数
void SysTick_Handler(void);

#define SYSTICK_START SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk //使能滴答定时器
#define SYSTICK_STOP SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk //关闭滴答定时器

/*************************************************************************
 * @brief   开启滴答定时器
 * @return 无
 * @note 如果初始化失败，将会陷入死循环
 * @history 2021-11-19：创建，完成功能并测试通过
 ************************************************************************/
void systick_init(void)
{
  TimingDelay = 0;
  if (SysTick_Config(SystemCoreClock / 1000000))
  {
    while (1)
      ;
  }
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0)); 
}

/*************************************************************************
 * @brief   延时函数
 * @param[in]	time 延时时间(单位us)
 * @return 无
 * @note 无
 * @example 通过宏调用(或直接调用 systick_delay(1000),延时1000us)
 * @history 2021-11-19：创建，完成功能并测试通过
 ************************************************************************/
void systick_delay(uint64_t time)
{
  uint64_t nowtime = TimingDelay;
  while (TimingDelay < nowtime + time)
    ;
}

/*************************************************************************
 * @brief   获取系统运行开始到调用时的时间
 * @return 系统运行的时间(uint64_t)，单位us
 * @note 无
 * @example 通过宏调用
 * @history 2021-11-19：创建，完成功能并测试通过
 ************************************************************************/
uint64_t systick_micors(void)
{
  return TimingDelay;
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
  TimingDelay++;
  
#if ENABLE_FERRRTOS
 #if (INCLUDE_xTaskGetSchedulerState == 1)
   if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
   {
 #endif /* INCLUDE_xTaskGetSchedulerState */
     xPortSysTickHandler();
 #if (INCLUDE_xTaskGetSchedulerState == 1)
   }
 #endif /* INCLUDE_xTaskGetSchedulerState */
#endif //ENABLE_FERRRTOS
}
