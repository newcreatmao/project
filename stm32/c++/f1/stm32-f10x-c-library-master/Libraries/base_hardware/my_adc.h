/**************************************************************************
 * @brief       : STM32 ADC功能
 * @author      : 龚为玮(1461041096)
 * @copyright   : 版权信息
 * @version     : v1.0
 * @note        : 无
 * @history     : 2021年11月23日：创建文件
 *                2021年11月26日：完成ADC1基础功能(初始化和读取),并进行了测试
 *                2021年11月28日：添加注释
 ***************************************************************************/
#ifndef __MY_ADC_H
#define __MY_ADC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "resources.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

  /**
   * @brief ADC通道枚举 \n
   * ADC_CH0：ADC通道0，其他以此类推
   */
  typedef enum
  {
    ADC_CH0 = ADC_Channel_0,
    ADC_CH1 = ADC_Channel_1,
    ADC_CH2 = ADC_Channel_2,
    ADC_CH3 = ADC_Channel_3,
    ADC_CH4 = ADC_Channel_4,
    ADC_CH5 = ADC_Channel_5,
    ADC_CH6 = ADC_Channel_6,
    ADC_CH7 = ADC_Channel_7,
    ADC_CH8 = ADC_Channel_8,
    ADC_CH9 = ADC_Channel_9,
    ADC_CH10 = ADC_Channel_10,
    ADC_CH11 = ADC_Channel_11,
    ADC_CH12 = ADC_Channel_12,
    ADC_CH13 = ADC_Channel_13,
    ADC_CH14 = ADC_Channel_14,
    ADC_CH15 = ADC_Channel_15,
    ADC_DEFAULT = 0xff
  } ADC_CH;

  void adc_init(void);
  uint16_t adc_pin_read(Pin_enum pin);
  uint16_t adc_ch_read(ADC_CH ch);

#ifdef __cplusplus
}
#endif

#endif
