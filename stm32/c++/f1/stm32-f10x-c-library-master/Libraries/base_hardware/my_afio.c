/**************************************************************************
  * @brief       : STM32 AFIO(端口复用功能)
  * @author      : 龚为玮(1461041096)  
  * @copyright   : 版权信息
  * @version     : v1.0
  * @note        : 主要作为其他外设函数初始化调用
  * @history     : 2021年11月20日：创建文件，完成基础功能
  *                2021年11月22日：测试，添加注释
***************************************************************************/
#include "my_afio.h"

/*************************************************************************
 * @brief   初始化io口复用
 * @param[in]	pin 要初始化的引脚 (可选择的值在 overall.h Pin_enum枚举中),
 *            此参数可以是以下值之一: 
 *              A0~A15 B0~B15 C0~C15 D0~D15 E0~E15 F0~F15 G0~G15
 * @param[in] mode 初始化引脚模式 (可选择的模式在 my_gpio.h Mode_enum中)
 *            此参数可以是以下值之一: 
 *              INPUT_AF OUT_PP_AF OUT_OD_AF
 * @return 无
 * @note 该函数主要供其他外设初始化函数内部调用
 *       默认设置GPIO速度为50MHZ，可在 my_afio.h 中修改DEFAULT_AFIO_SPEED
 *       宏进行修改
 * @history 2021-11-20：创建，完成功能
 *          2021-11-22：通过设置串口测试通过
 ************************************************************************/
void afio_init(Pin_enum pin, AFIO_mode mode)
{
  uint16_t gpio_pin = GPIO_Pin_0 << (pin & 0x0f);
  uint16_t gpio_port = (pin & 0xf0) >> 4;

  uint32_t RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOA << gpio_port;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);

  GPIO_InitTypeDef gpio;

  gpio.GPIO_Pin = gpio_pin;
  gpio.GPIO_Mode = (GPIOMode_TypeDef)mode;
  gpio.GPIO_Speed = DEFAULT_AFIO_SPEED;

  GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
  GPIO_Init(GPIOx, &gpio);
}

