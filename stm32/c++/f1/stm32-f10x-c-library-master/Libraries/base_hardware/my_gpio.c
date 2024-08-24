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
#include "my_gpio.h"

/**************************************************************************
 *    GPIO读写接口
 **************************************************************************/
/*************************************************************************
 * @brief   初始化gpio口
 * @param[in]	pin 要初始化的引脚 (可选择的值在 overall.h Pin_enum枚举中),
 *            此参数可以是以下值之一:
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @param[in] mode 初始化引脚模式 (可选择的模式在 my_gpio.h Mode_enum中)
 *            此参数可以是以下值之一:
 *              INPUT INPUT_PULLUP INPUT_PULLDOWN OUT_PP OUT_OD
 * @return 无
 * @note 默认设置GPIO速度为50MHZ，可在 my_gpio.h 中修改DEFAULT_GPIO_SPEED
 *       宏进行修改
 * @example gpio_init(A0,OUT_PP)设置A0口为推挽输出
 * @example gpio_init(A0,INPUT_PULLUP)设置A0口上拉输入
 * @history 2021-11-19：创建，完成功能并测试通过
 ************************************************************************/
void gpio_init(Pin_enum pin, GPIO_mode mode)
{
  uint16_t gpio_pin = GPIO_Pin_0 << (pin & 0x0f);
  uint16_t gpio_port = (pin & 0xf0) >> 4;

  uint32_t RCC_APB2Periph_GPIO = RCC_APB2Periph_GPIOA << gpio_port;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO, ENABLE);

  GPIO_InitTypeDef gpio;

  gpio.GPIO_Pin = gpio_pin;
  gpio.GPIO_Mode = (GPIOMode_TypeDef)mode;
  gpio.GPIO_Speed = DEFAULT_GPIO_SPEED;

  GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
  GPIO_Init(GPIOx, &gpio);
}

void gpio_deinit(Pin_enum pin)
{
  uint16_t gpio_pin = GPIO_Pin_0 << (pin & 0x0f);
  uint16_t gpio_port = (pin & 0xf0) >> 4;
}

/*************************************************************************
 * @brief   更改gpio输出状态
 * @param[in]	pin 要更改的引脚 (可选择的值在 overall.h Pin_enum枚举中)
 *            此参数可以是以下值之一:
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @param[in] data 输出的电平
 *             此参数可以是以下值之一:
 *              1高电平，0低电平
 * @return 无
 * @note  使用该函数前，应先将gpio口设置为输出模式
 * @example gpio_write(A0,1)设置A0口为高电平
 * @history 2021-11-19：创建，完成功能并测试通过
 *          2021-11-20：将GPIO_SetBits(~)和GPIO_ResetBits(~)统一为GPIO_WriteBit(),
 *                      测试通过
 ************************************************************************/
void gpio_write(Pin_enum pin, uint8_t data)
{
  uint16_t gpio_pin = GPIO_Pin_0 << (pin & 0x0f);
  uint16_t gpio_port = (pin & 0xf0) >> 4;
  GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);

  GPIO_WriteBit(GPIOx, gpio_pin, (BitAction)data);
}

/*************************************************************************
 * @brief   翻转gpio输出状态
 * @param[in]	pin 要翻转的引脚 (可选择的值在 overall.h Pin_enum枚举中)
 *            此参数可以是以下值之一:
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @return 无
 * @note  使用该函数前，应先将gpio口设置为输出模式
 * @example gpio_toggle(A0)翻转A0电平
 * @history 2021-11-19：创建，完成功能并测试通过
 *          2021-11-20：将GPIO_SetBits(~)和GPIO_ResetBits(~)统一为GPIO_WriteBit(),
 *                      测试通过
 ************************************************************************/
void gpio_toggle(Pin_enum pin)
{
  uint16_t gpio_pin = GPIO_Pin_0 << (pin & 0x0f);
  uint16_t gpio_port = (pin & 0xf0) >> 4;
  GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);

  uint8_t data = GPIO_ReadOutputDataBit(GPIOx, gpio_pin);

  GPIO_WriteBit(GPIOx, gpio_pin, (BitAction)!data);
}

/*************************************************************************
 * @brief   读取gpio输入状态
 * @param[in]	pin 要读取的引脚 (可选择的值在 overall.h Pin_enum枚举中)
 *            此参数可以是以下值之一:
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @return 无
 * @note  使用该函数前，应先将gpio口设置为输入模式
 * @example gpio_read(A0)读取A0电平
 * @history 2021-11-19：创建，完成功能并测试通过
 ************************************************************************/
uint8_t gpio_read(Pin_enum pin)
{
  uint16_t gpio_pin = GPIO_Pin_0 << (pin & 0x0f);
  uint16_t gpio_port = (pin & 0xf0) >> 4;
  GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);

  return GPIO_ReadInputDataBit(GPIOx, gpio_pin);
}

/**************************************************************************
 *    GPIO中断接口
 **************************************************************************/
/*************************************************************************
 * @brief   通过引脚标号获取外部中断向量
 * @param[in]	pin 引脚标号 (可选择的值在 overall.h Pin_enum枚举中)
 *            此参数可以是以下值之一:
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @return 对应的外部中断向量
 * @note  内部使用
 * @history 2021-11-30：创建，完成功能并测试通过
 ************************************************************************/
uint8_t get_exit_irqchannel(Pin_enum pin)
{
  uint8_t pin_num = pin & 0x0f;
  if (pin_num <= 4)
  {
    return EXTI0_IRQn + pin_num;
  }
  else if (pin <= 9)
  {
    return EXTI9_5_IRQn;
  }
  else if (pin <= 15)
  {
    return EXTI15_10_IRQn;
  }
  else
  {
    return 0;
  }
}

/*************************************************************************
 * @brief   gpio外部中断初始化
 * @param[in]	pin 要初始化的引脚标号 (可选择的值在 overall.h Pin_enum枚举中)
 *            此参数可以是以下值之一:
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @param[in] callback 自定义的中断服务函数的函数指针，该函数必须为无返回值，无
 *            参数
 * @param[in]	mode 外部中断触发方式
 *            此参数可以是以下值之一:
 *              Rising:上升沿 Faling:下降沿 Change:上升&下降沿
 * @return 无
 * @example gpio_interrupt_init(A0, Rising)配置A0上升沿中断
 * @history 2021-11-30：创建，完成功能并测试通过
 ************************************************************************/
void gpio_interrupt_init(Pin_enum pin, void (*callback)(void), EXIT_mode mode)
{
  uint8_t GPIO_PinSourcex = (pin & 0x0f);
  uint8_t GPIO_PortSourceGPIOx = (pin & 0xf0) >> 4;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //开启AFIO时钟

  switch (mode)
  {
  case Rising:
    gpio_init(pin, INPUT_PULLDOWN); //上升沿选择下拉输入
    break;
  case Falling:
    gpio_init(pin, INPUT_PULLUP); //下降沿选择上拉输入
    break;
  case Change:
    gpio_init(pin, INPUT); //上升&下降沿选择浮空输入
    break;
  default:
    return;
  }
  //初始化IO

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOx, GPIO_PinSourcex); //引脚中断号配置

  EXTI_InitTypeDef EXTI_InitStructure; //外部中断结构体初始化
  NVIC_InitTypeDef NVIC_InitStructure; //中断分组结构体初始化

  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;          //中断模式
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                    //使能中断线
  EXTI_InitStructure.EXTI_Line = EXTI_Line0 << (pin & 0x0f);   //中断线标号
  EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)mode; //触发方式

  EXTI_Init(&EXTI_InitStructure);

  //以下为中断优先级的配置
  NVIC_InitStructure.NVIC_IRQChannel = get_exit_irqchannel(pin); //声明使用的中断是哪一个
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;   //设置抢占优先级为2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;          //设置子优先级为3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //使能中断

  NVIC_Init(&NVIC_InitStructure);

  EXTI_Linex_Callback[GPIO_PinSourcex] = callback;
}

void gpio_interrupt_deinit(Pin_enum pin)
{
  uint8_t GPIO_PinSourcex = (pin & 0x0f);
  uint8_t GPIO_PortSourceGPIOx = (pin & 0xf0) >> 4;

  EXTI_InitTypeDef EXTI_InitStructure; //外部中断结构体初始化
  NVIC_InitTypeDef NVIC_InitStructure; //中断分组结构体初始化

  EXTI_InitStructure.EXTI_LineCmd = DISABLE;                   //关闭中断线
  EXTI_InitStructure.EXTI_Line = EXTI_Line0 << (pin & 0x0f);   //中断线标号

  EXTI_Init(&EXTI_InitStructure);

  //以下为中断优先级的配置
  NVIC_InitStructure.NVIC_IRQChannel = get_exit_irqchannel(pin); //声明使用的中断是哪一个
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;               //使能中断

  NVIC_Init(&NVIC_InitStructure);

  EXTI_Linex_Callback[GPIO_PinSourcex] = 0;
}

/*************中断服务函数********************/

void (*EXTI_Linex_Callback[16])(void); //外部中断回调函数指针

void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0) == SET)
  {
    EXTI_Linex_Callback[0]();
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line1) == SET)
  {
    EXTI_Linex_Callback[1]();
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

void EXTI2_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line2) == SET)
  {
    EXTI_Linex_Callback[2]();
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

void EXTI3_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line3) == SET)
  {
    EXTI_Linex_Callback[3]();
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}

void EXTI4_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line4) == SET)
  {
    EXTI_Linex_Callback[4]();
    EXTI_ClearITPendingBit(EXTI_Line4);
  }
}

void EXTI9_5_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line5) == SET)
  {
    EXTI_Linex_Callback[5]();
    EXTI_ClearITPendingBit(EXTI_Line5);
  }
  if (EXTI_GetITStatus(EXTI_Line6) == SET)
  {
    EXTI_Linex_Callback[6]();
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
  if (EXTI_GetITStatus(EXTI_Line7) == SET)
  {
    EXTI_Linex_Callback[7]();
    EXTI_ClearITPendingBit(EXTI_Line7);
  }
  if (EXTI_GetITStatus(EXTI_Line8) == SET)
  {
    EXTI_Linex_Callback[8]();
    EXTI_ClearITPendingBit(EXTI_Line8);
  }
  if (EXTI_GetITStatus(EXTI_Line9) == SET)
  {
    EXTI_Linex_Callback[9]();
    EXTI_ClearITPendingBit(EXTI_Line9);
  }
}

void EXTI15_10_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line10) == SET)
  {
    EXTI_Linex_Callback[10]();
    EXTI_ClearITPendingBit(EXTI_Line10);
  }
  if (EXTI_GetITStatus(EXTI_Line11) == SET)
  {
    EXTI_Linex_Callback[11]();
    EXTI_ClearITPendingBit(EXTI_Line11);
  }
  if (EXTI_GetITStatus(EXTI_Line12) == SET)
  {
    EXTI_Linex_Callback[12]();
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
  if (EXTI_GetITStatus(EXTI_Line13) == SET)
  {
    EXTI_Linex_Callback[13]();
    EXTI_ClearITPendingBit(EXTI_Line13);
  }
  if (EXTI_GetITStatus(EXTI_Line14) == SET)
  {
    EXTI_Linex_Callback[14]();
    EXTI_ClearITPendingBit(EXTI_Line14);
  }
  if (EXTI_GetITStatus(EXTI_Line15) == SET)
  {
    EXTI_Linex_Callback[15]();
    EXTI_ClearITPendingBit(EXTI_Line15);
  }
}
