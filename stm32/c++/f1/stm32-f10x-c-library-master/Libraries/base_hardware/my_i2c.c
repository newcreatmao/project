/**************************************************************************
 * @brief       : STM32 I2C(包括软件和硬件)
 * @author      : 龚为玮(1461041096)
 * @copyright   : 版权信息
 * @version     : v1.0
 * @note        : 1.硬件I2C暂时不可用;
 *                2.软件I2C发送ACK(i2c_soft_send_ack(Software_I2C *i2c))存在问题，
 *                由于读取多个字节(i2c_soft_reg_receive_bytes(~))需要发送ACK应答,
 *                因此该函数也不可以，目前顶层的库通过多次当此读取来取代该函数。
 * @history     : 忘了啥时候:创建文件
 *                忘了啥时候:完成软件I2C，并进行了测试，除发送ACK不可用外其他正常
 *                忘了啥时候:完成硬件I2C，鸟用也没有
 *                2020年12月15日:添加注释
 *                2022年10月23日:修改函数声明
 ***************************************************************************/
#include "my_i2c.h"
#include "my_systick.h"

///***************************硬件I2C部分*****************************///
#define I2C_ADDR_FOR_WRITE I2C_Direction_Transmitter //硬件I2C发送从机写地址Mask
#define I2C_ADDR_FOR_READ I2C_Direction_Receiver     //硬件I2C发送从机读地址Mask

void i2c_hard_start(Hardware_I2C *i2c);
void i2c_hard_stop(Hardware_I2C *i2c);
uint8_t i2c_hard_send_addr(Hardware_I2C *i2c, uint8_t mode);
uint8_t i2c_hard_send_byte(Hardware_I2C *i2c, uint8_t byte);
uint16_t i2c_hard_receive_byte(Hardware_I2C *i2c);

/**
 * @brief 硬件I2C对应引脚枚举 \n
 * I2C_1_SDA_Pin 硬件I2C1的SDA引脚，以此类推
 */
typedef enum
{
#ifdef HAVE_I2C1
    I2C1_SDA_Pin = B7,
    I2C1_SCL_Pin = B6,
#endif

#ifdef HAVE_I2C2
    I2C2_SDA_Pin = B11,
    I2C2_SCL_Pin = B10,
#endif

    I2C_Pin_END
} Hardware_I2C_Pin;

/*************************************************************************
 * @brief   初始化硬件I2C
 * @param[in] i2c 要初始化的硬件I2C (可选择的值在 my_i2c.h Hardware_I2C_enum枚举中)
 * @param[in] addr 从机设备地址(左对齐)
 * @param[in] speed I2C通信速度，单位：KHz
 * @return Hardware_I2C 硬件I2C设备结构体
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
Hardware_I2C i2c_hard_init(Hardware_I2C_enum i2c, int speed)
{

    Pin_enum SCL_pin, SDA_pin;
    switch (i2c)
    {
#ifdef HAVE_I2C1
    case I2C_1:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
        SCL_pin = (Pin_enum)I2C1_SCL_Pin, SDA_pin = (Pin_enum)I2C1_SDA_Pin;
        break;
#endif
#ifdef HAVE_I2C2
    case I2C_2:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
        SCL_pin = (Pin_enum)I2C2_SCL_Pin, SDA_pin = (Pin_enum)I2C2_SDA_Pin;
        break;
#endif
    default:
        break;
    }

    afio_init(SCL_pin, OUT_OD_AF);
    afio_init(SDA_pin, OUT_OD_AF);

    I2C_InitTypeDef I2C_InitStructure;

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x77;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = (uint32_t)(1000 * (speed > 400 ? 400 : speed));
    I2C_Init((I2C_TypeDef *)i2c, &I2C_InitStructure);
    I2C_Cmd((I2C_TypeDef *)i2c, ENABLE);

    Hardware_I2C hard_i2c;
    hard_i2c.i2c = i2c;
    hard_i2c.speed = speed;

    I2C_GenerateSTOP((I2C_TypeDef *)i2c, ENABLE);

    return hard_i2c;
}

/*************************************************************************
 * @brief   硬件I2C起始信号
 * @param[in] i2c 发送起始信号的硬件I2C设备
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
void i2c_hard_start(Hardware_I2C *i2c)
{
    I2C_GenerateSTART((I2C_TypeDef *)(i2c->i2c), ENABLE);
    // int count = 0;
    while (!I2C_CheckEvent((I2C_TypeDef *)(i2c->i2c), I2C_EVENT_MASTER_MODE_SELECT)) // && (count++) < 1000)
    {
        delay_us(1);
    }
}

/*************************************************************************
 * @brief   硬件I2C停止信号
 * @param[in] i2c 发送起始信号的硬件I2C设备
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
void i2c_hard_stop(Hardware_I2C *i2c)
{
    I2C_GenerateSTOP((I2C_TypeDef *)(i2c->i2c), ENABLE);
}

/*************************************************************************
 * @brief   硬件I2C发送从机地址
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] mode 选择写模式还是读模式
 *          此参数可以是以下值之一:
 *          I2C_ADDR_FOR_WRITE I2C_ADDR_FOR_READ
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
uint8_t i2c_hard_send_addr(Hardware_I2C *i2c, uint8_t mode)
{
    I2C_Send7bitAddress((I2C_TypeDef *)(i2c->i2c), i2c->addr, mode);
    // int count = 0;
    while (!I2C_CheckEvent((I2C_TypeDef *)(i2c->i2c), I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) // && (count++) < 1000)
    {
        delay_us(1);
    }
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C发送一个字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] byte 要发送的字节
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
uint8_t i2c_hard_send_byte(Hardware_I2C *i2c, uint8_t byte)
{
    I2C_SendData((I2C_TypeDef *)(i2c->i2c), byte);
    // int count = 0;
    while (!I2C_CheckEvent((I2C_TypeDef *)(i2c->i2c), I2C_EVENT_MASTER_BYTE_TRANSMITTED)) //&& (count++) < 1000)
    {
        delay_us(1);
    }
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C接收一个字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @return 读取到的字节
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
uint16_t i2c_hard_receive_byte(Hardware_I2C *i2c)
{
    // int count = 0;
    while (!I2C_CheckEvent((I2C_TypeDef *)(i2c->i2c), I2C_EVENT_MASTER_BYTE_RECEIVED)) // && (count++) < 1000)
    {
        delay_us(1);
    }
    return I2C_ReceiveData((I2C_TypeDef *)(i2c->i2c));
}

uint8_t i2c_hard_check(Hardware_I2C *i2c)
{
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C向地址写一个字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] addr 要写入数据的地址
 * @param[in] byte 要发送的字节
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
size_t i2c_hard_reg_write_data(Hardware_I2C *i2c, uint8_t addr, uint8_t byte)
{
    i2c_hard_start(i2c);
    i2c_hard_send_addr(i2c, I2C_ADDR_FOR_WRITE);
    i2c_hard_send_byte(i2c, addr);
    i2c_hard_send_byte(i2c, byte);
    i2c_hard_stop(i2c);
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C向地址写多个字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] addr 要写入数据的地址
 * @param[in] buf 要写入数据的字节数组
 * @param[in] size 要写入的字节数
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
size_t i2c_hard_reg_write_datas(Hardware_I2C *i2c, uint8_t addr, const uint8_t *buf, uint32_t size)
{
    i2c_hard_start(i2c);
    i2c_hard_send_addr(i2c, I2C_ADDR_FOR_WRITE);
    i2c_hard_send_byte(i2c, addr);
    for (int i = 0; i < size; i++)
    {
        i2c_hard_send_byte(i2c, buf[i]);
    }
    i2c_hard_stop(i2c);
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C向地址写多个相同的字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] addr 要写入数据的地址
 * @param[in] byte 要写入的数据
 * @param[in] size 要写入的字节数
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
size_t i2c_hard_reg_fill_datas(Hardware_I2C *i2c, uint8_t addr, const uint8_t byte, uint32_t size)
{
    i2c_hard_start(i2c);
    i2c_hard_send_addr(i2c, I2C_ADDR_FOR_WRITE);
    i2c_hard_send_byte(i2c, addr);
    for (int i = 0; i < size; i++)
    {
        i2c_hard_send_byte(i2c, byte);
    }
    i2c_hard_stop(i2c);
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C向地址读取一个字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] addr 要读取数据的地址
 * @return 读取到的字节
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
uint16_t i2c_hard_reg_receive_data(Hardware_I2C *i2c, uint8_t addr)
{
    i2c_hard_start(i2c);
    i2c_hard_send_addr(i2c, I2C_ADDR_FOR_WRITE);
    i2c_hard_send_byte(i2c, addr);

    i2c_hard_start(i2c);
    i2c_hard_send_addr(i2c, I2C_ADDR_FOR_READ);
    uint16_t res = i2c_hard_receive_byte(i2c);
    i2c_hard_stop(i2c);
    return res;
}

/*************************************************************************
 * @brief   硬件I2C向地址读取多个字节
 * @param[in] i2c 要操作的硬件I2C设备
 * @param[in] addr 要读取数据的地址
 * @param[out] buf 接收读取到数据的数组
 * @param[in] size 要读取的长度
 * @return 无
 * @note  当前不可使用
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
size_t i2c_hard_reg_receive_datas(Hardware_I2C *i2c, uint8_t addr, uint8_t *buf, uint32_t size)
{
    for (int i = 0; i < size; i++)
    {
        i2c_hard_reg_receive_data(i2c, addr + 1);
    }
    return 1;
}

///***************************软件I2C部分*****************************///

void i2c_soft_start(Software_I2C *i2c);
void i2c_soft_stop(Software_I2C *i2c);
uint8_t i2c_soft_wait_ack(Software_I2C *i2c);
void i2c_soft_send_ack(Software_I2C *i2c);
void i2c_soft_send_nack(Software_I2C *i2c);
void i2c_soft_send_byte(Software_I2C *i2c, uint8_t byte);
uint8_t i2c_soft_receive_byte(Software_I2C *i2c);

/*************************************************************************
 * @brief   初始化软件I2C
 * @param[in] SDA_Pin 软件I2C的SDA引脚
 * @param[in] SDA_Pin 软件I2C的SCL引脚
 * @param[in] addr 从机设备地址(左对齐)
 * @param[in] speed I2C通信速度，单位：KHz
 * @return Software_I2C 软件I2C设备结构体
 * @note  无
 * @example i2c_sofr_init(B7,B6,0xA0,400);
 *          初始化软件I2C，SDA引脚为B7，SCL引脚为B6，从机地址为0xA0，通信速度为
 *          400KHz(该速率不准确)
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
Software_I2C i2c_soft_init(Pin_enum SDA_Pin, Pin_enum SCL_Pin, int speed)
{
    Software_I2C s_i2c;
    s_i2c.SDA = SDA_Pin;
    s_i2c.SCL = SCL_Pin;
    s_i2c.delay_time = speed;

    gpio_init(SDA_Pin, OUT_OD);
    gpio_init(SCL_Pin, OUT_PP);

    i2c_soft_stop(&s_i2c);

    return s_i2c;
}

/*************************************************************************
 * @brief   软件I2C起始信号
 * @param[in] i2c 发送起始信号的软件I2C设备
 * @return 无
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_start(&i2c_device);
 *          ...(other code)
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
void i2c_soft_start(Software_I2C *i2c)
{
    /*拉高SCL 和 SDA*/
    gpio_write(i2c->SDA, 1);
    gpio_write(i2c->SCL, 1);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SDA, 0);
    delay_us(i2c->delay_time);
    gpio_write(i2c->SCL, 0);
}

/*************************************************************************
 * @brief   软件I2C停止信号
 * @param[in] i2c 发送停止信号的软件I2C设备
 * @return 无
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_stop(&i2c_device);
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
void i2c_soft_stop(Software_I2C *i2c)
{
    gpio_write(i2c->SCL, 0);
    gpio_write(i2c->SDA, 0);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SCL, 1);
    gpio_write(i2c->SDA, 1);
    delay_ms(i2c->delay_time);
}

/*************************************************************************
 * @brief   等待从机发送ACK应答
 * @param[in] i2c 要操作的软件I2C设备
 * @return 0:收到从机ACK应答;1:超时未收到从机ACK应答。
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_wait_ack(&i2c_device);
 *          ...(other code)
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
uint8_t i2c_soft_wait_ack(Software_I2C *i2c)
{
    gpio_write(i2c->SDA, 1);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SCL, 1);
    delay_us(i2c->delay_time);

    int count = 0;
    while (gpio_read(i2c->SDA))
    {
        count++;
        if (count >= 2000)
            return 1;
        delay_us(1);
    }

    gpio_write(i2c->SCL, 0);
    return 0;
}

/*************************************************************************
 * @brief   发送ACK应答
 * @param[in] i2c 要操作的软件I2C设备
 * @return 无
 * @note  经过测试发现从机无法收到应答(不可用)
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_send_ack(&i2c_device);
 *          ...(other code)
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试发现从机无法收到应答
 ************************************************************************/
void i2c_soft_send_ack(Software_I2C *i2c)
{
    gpio_init(i2c->SCL, OUT_PP);
    gpio_init(i2c->SDA, OUT_PP);

    gpio_write(i2c->SCL, 0);
    gpio_write(i2c->SDA, 0);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SCL, 1);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SCL, 0);

    gpio_init(i2c->SCL, OUT_OD);
    gpio_init(i2c->SDA, OUT_OD);
}

/*************************************************************************
 * @brief   发送ACK应答
 * @param[in] i2c 要操作的软件I2C设备
 * @return 无
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_send_nack(&i2c_device);
 *          ...(other code)
 * @history 忘了啥时候：创建，使用较少，效果未知
 ************************************************************************/
void i2c_soft_send_nack(Software_I2C *i2c)
{
    gpio_write(i2c->SCL, 0);
    gpio_write(i2c->SDA, 1);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SCL, 1);
    delay_us(i2c->delay_time);

    gpio_write(i2c->SCL, 0);
}

/*************************************************************************
 * @brief   软件I2C发送一个字节
 * @param[in] i2c 要操作的软件I2C设备
 * @param[in] byte 要发送的字节
 * @return 无
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_send_byte(&i2c_device, 0xFF);
 *          ...(other code)
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
void i2c_soft_send_byte(Software_I2C *i2c, uint8_t byte)
{
    gpio_write(i2c->SCL, 0);
    for (int i = 0; i < 8; i++)
    {
        if (byte & 0x80)
        {
            gpio_write(i2c->SDA, 1);
        }
        else
        {
            gpio_write(i2c->SDA, 0);
        }

        byte <<= 1;
        delay_us(i2c->delay_time);
        gpio_write(i2c->SCL, 1);
        delay_us(i2c->delay_time);
        gpio_write(i2c->SCL, 0);
        delay_us(i2c->delay_time);
    }
}

/*************************************************************************
 * @brief   软件I2C接收一个字节
 * @param[in] i2c 要操作的软件I2C设备
 * @return 接收到的字节
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          uint8_t rec = i2c_soft_receive_byte(&i2c_device);
 *          ...(other code)
 * @history 忘了啥时候：创建，使用读写AT24C02测试可用
 ************************************************************************/
uint8_t i2c_soft_receive_byte(Software_I2C *i2c)
{
    uint8_t rec = 0;
    for (int i = 0; i < 8; i++)
    {
        gpio_write(i2c->SCL, 0);
        delay_us(i2c->delay_time);
        gpio_write(i2c->SCL, 1);
        delay_us(i2c->delay_time);

        rec <<= 1;
        rec = rec | gpio_read(i2c->SDA);

        delay_us(i2c->delay_time);
    }

    return rec;
}

uint8_t i2c_soft_check(Software_I2C *i2c)
{
    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, i2c->addr);

    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }
    return 1;
}

/*************************************************************************
 * @brief   软件I2C向地址写一个字节
 * @param[in] i2c 要操作的软件I2C设备
 * @param[in] addr 要写入数据的地址
 * @param[in] byte 要发送的字节
 * @return 0:发送失败; 1:发送成功
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_reg_write_byte(&i2c_device, 0x00, 0x0A);
 *          //向0x00写入数据0x0A
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
size_t i2c_soft_reg_write_data(Software_I2C *i2c, uint8_t addr, uint8_t byte)
{
    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, i2c->addr);

    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }
    i2c_soft_send_byte(i2c, addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }
    i2c_soft_send_byte(i2c, byte);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }
    i2c_soft_stop(i2c);
    return 1;
}

/*************************************************************************
 * @brief   软件I2C向地址写多个字节
 * @param[in] i2c 要操作的软件I2C设备
 * @param[in] addr 要写入数据的地址
 * @param[in] buf 要写入数据的字节数组
 * @param[in] size 要写入的字节数
 * @return 0:发送失败; 1:发送成功
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          char *str="hello wrold";
 *          i2c_soft_reg_write_bytes(&i2c_device, 0x00, str, sizeof(str));
 *          //向0x00写入数据
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
size_t i2c_soft_reg_write_datas(Software_I2C *i2c, uint8_t addr, const uint8_t *buf, uint32_t size)
{
    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, i2c->addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }

    i2c_soft_send_byte(i2c, addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        i2c_soft_send_byte(i2c, buf[i]);
        if (i2c_soft_wait_ack(i2c))
        {
            i2c_soft_stop(i2c);
            return i;
        }
    }
    i2c_soft_stop(i2c);
    return 1;
}

/*************************************************************************
 * @brief   硬件I2C向地址写多个相同的字节
 * @param[in] i2c 要操作的软件I2C设备
 * @param[in] addr 要写入数据的地址
 * @param[in] byte 要写入的数据
 * @param[in] size 要写入的字节数
 * @return 0:发送失败; 1:发送成功
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          i2c_soft_reg_fill_bytes(&i2c_device, 0x00, 0xA0, 10);
 *          //向0x00写入10个0xA0数据
 * @history 忘了啥时候：创建，使用读写AT24C02及操作OLED测试可用
 ************************************************************************/
size_t i2c_soft_reg_fill_datas(Software_I2C *i2c, uint8_t addr, const uint8_t byte, uint32_t size)
{
    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, i2c->addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }

    i2c_soft_send_byte(i2c, addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        i2c_soft_send_byte(i2c, byte);
        if (i2c_soft_wait_ack(i2c))
        {
            i2c_soft_stop(i2c);
            return i;
        }
    }
    i2c_soft_stop(i2c);
    return 1;
}

/*************************************************************************
 * @brief   软件I2C向地址读取一个字节
 * @param[in] i2c 要操作的软件I2C设备
 * @param[in] addr 要读取数据的地址
 * @return 0x00~0xff:读取到的字节; 0xfffe:读取失败
 * @note  无
 * @example Software_I2C i2c_device = Software_I2C(B7, B6 ,0xA0, 400);
 *          ...(other code)
 *          uint16_t rec = i2c_soft_reg_receive_byte(&i2c_device, 0x00);
 *          //向0x00读取一个字节
 *          if(rec == 0xfffe)
 *          {
 *              //读取失败
 *          }
 * @history 忘了啥时候：创建，使用读写AT24C02测试可用
 ************************************************************************/
uint16_t i2c_soft_reg_receive_data(Software_I2C *i2c, uint8_t addr)
{
    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, i2c->addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0xfffe;
    }

    i2c_soft_send_byte(i2c, addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0xfffe;
    }

    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, (i2c->addr) + 1);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0xfffe;
    }

    uint16_t res = i2c_soft_receive_byte(i2c);

    i2c_soft_stop(i2c);

    return res;
}

/*************************************************************************
 * @brief   软件I2C向地址读取多个字节
 * @param[in] i2c 要操作的软件I2C设备
 * @param[in] addr 要读取数据的地址
 * @param[out] buf 接收读取到数据的数组
 * @param[in] size 要读取的长度
 * @return 0xfffe:读取失败; other:成功读取到的字节数
 * @note  无法连续读取，仅能成功读取第一位
 * @example 不可使用
 * @history 忘了啥时候：创建，测试不可使用
 ************************************************************************/
size_t i2c_soft_reg_receive_datas(Software_I2C *i2c, uint8_t addr, uint8_t *buf, uint32_t size)
{
    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, i2c->addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0xfffe;
    }

    i2c_soft_send_byte(i2c, addr);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0xfffe;
    }

    i2c_soft_start(i2c);
    i2c_soft_send_byte(i2c, (i2c->addr) + 1);
    if (i2c_soft_wait_ack(i2c))
    {
        i2c_soft_stop(i2c);
        return 0xfffe;
    }

    for (int i = 0; i < size; i++)
    {
        buf[i] = i2c_soft_receive_byte(i2c);
        i2c_soft_send_ack(i2c);
    }

    // uint16_t res = i2c_soft_receive_byte(i2c);

    i2c_soft_stop(i2c);

    return size;
}
