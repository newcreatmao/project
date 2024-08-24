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
#include "my_adc.h"
#include "my_gpio.h"
#include "my_afio.h"

/*************************************************************************
 * @brief   初始化ADC
 * @return 无
 * @note 无
 * @example adc_init(); 初始化ADC
 * @history 2021-11-26：创建
 ************************************************************************/
void adc_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    ADC_InitTypeDef ADC_InitStructure;

    ADC_DeInit(ADC1); //复位ADC1，重设为默认缺省值

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 //模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             //顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);                                 //初始化ADC1

    ADC_Cmd(ADC1, ENABLE); //使能ADC1

    ADC_ResetCalibration(ADC1); //使能复位校准
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;                       //等待复位校准结束
    ADC_StartCalibration(ADC1); //开启AD校准
    while (ADC_GetCalibrationStatus(ADC1))
        ;                                   //等待校准结束
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能ADC1的软件转换启动功能
}

/*************************************************************************
 * @brief   通过GPIO引脚获取ADC通道
 * @return ADC通道枚举
 * @note 内部使用
 * @history 2021-11-26：创建
 ************************************************************************/
ADC_CH pin2adcch(Pin_enum pin)
{
    switch (pin)
    {
    case A0:
        return ADC_CH0;
    case A1:
        return ADC_CH1;
    case A2:
        return ADC_CH2;
    case A3:
        return ADC_CH3;
    case A4:
        return ADC_CH4;
    case A5:
        return ADC_CH5;
    case A6:
        return ADC_CH6;
    case A7:
        return ADC_CH7;
    case B0:
        return ADC_CH8;
    case B1:
        return ADC_CH9;
    case C0:
        return ADC_CH10;
    case C1:
        return ADC_CH11;
    case C2:
        return ADC_CH12;
    case C3:
        return ADC_CH13;
    case C4:
        return ADC_CH14;
    case C5:
        return ADC_CH15;
    default:
        return ADC_DEFAULT;
    }
}

/*************************************************************************
 * @brief   通过GPIO引脚号读取ADC值
 * @param[in]	pin 要初始化的引脚 (可选择的值在 overall.h Pin_enum枚举中),
 *            此参数可以是以下值之一: 
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @return 读取到的值(12位)
 * @note 使用前需先初始化(adc_init()),并对ADC引脚初始化为输入模式如果传入的引
 *       脚存在对应的adc通道，则返回adc采集的值，如果不存在对应的adc通道，则返
 *       回电平值(高电平返回0xffff,低电平0x0000)
 * @example adc_pin_read(A0),读取A0引脚的adc值
 * @history 2021-11-26：创建
 ************************************************************************/
uint16_t adc_pin_read(Pin_enum pin)
{
    ADC_CH ch = pin2adcch(pin);
    if (ch == ADC_DEFAULT)
    {
        if (gpio_read(pin) == 1)
        {
            return 0xffff >> 4;
        }
        else
        {
            return 0x0000;
        }
    }
    ADC_RegularChannelConfig(ADC1, (uint8_t)ch, 1, ADC_SampleTime_1Cycles5);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能ADC1的软件转换启动功能
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    {
    }                                    //等待转换结束
    return ADC_GetConversionValue(ADC1); //返回最近一次ADC1规则组的转换结果
}

/*************************************************************************
 * @brief   通过ADC通道读取ADC值
 * @param[in]	ch adc通道 (可选择的值在 my_adc.h ADC_CH枚举中),
 *            此参数可以是以下值之一: 
 *              ADC_CH0~ADC_CH15
 * @return 读取到的值(12位)
 * @note 使用前需先初始化(adc_init()),并对ADC引脚初始化为输入模式如果传入的引
 *       脚存在对应的adc通道，则返回adc采集的值，如果不存在对应的adc通道，则返
 *       回电平值(高电平返回0xffff,低电平0x0000)。
 *       理论上该函数效率高于adc_pin_read();
 * @example adc_ch_read(ADC_CH0),读取adc通道0的adc值
 * @history 2021-11-26：创建
 ************************************************************************/
uint16_t adc_ch_read(ADC_CH ch)
{
    ADC_RegularChannelConfig(ADC1, (uint8_t)ch, 1, ADC_SampleTime_1Cycles5);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能ADC1的软件转换启动功能
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    {
    }                                    //等待转换结束
    return ADC_GetConversionValue(ADC1); //返回最近一次ADC1规则组的转换结果
}
