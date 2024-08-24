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
 *                忘了啥时候:完成硬件I2C，鸟用也没有(STM32官方库的I2C不稳定)
 *                2020年12月15日:添加注释
 *                2022年10月23日:修改函数声明
 ***************************************************************************/
#ifndef __MY_I2C_H
#define __MY_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "resources.h"
#include "stm32f10x_i2c.h"
#include "my_gpio.h"
#include "my_afio.h"
#include <stdio.h>

/**
 * @brief 硬件I2C枚举枚举 \n
 * I2C_1 硬件I2C1，以此类推
 */
typedef enum
{
#ifdef HAVE_I2C1
    I2C_1 = (uint32_t)I2C1,
#endif
#ifdef HAVE_I2C2
    I2C_2 = (uint32_t)I2C2,
#endif
    I2C_END
} Hardware_I2C_enum;

/*
 * @brief 硬件I2C从设备结构体 \n
 * i2c:硬件I2C设备枚举
 * addr:硬件I2C设备地址(字节左对齐)
 * speed:硬件I2C通信数据，单位：Khz
 */
typedef struct
{
    Hardware_I2C_enum i2c;
    uint16_t addr;
    int speed;
} Hardware_I2C;

///***************************硬件I2C部分*****************************///

Hardware_I2C i2c_hard_init(Hardware_I2C_enum i2c, int speed);
uint8_t i2c_hard_check(Hardware_I2C *i2c);
size_t i2c_hard_reg_write_data(Hardware_I2C *i2c, uint8_t addr, uint8_t byte);
size_t i2c_hard_reg_write_datas(Hardware_I2C *i2c, uint8_t addr, const uint8_t *buf, size_t size);
size_t i2c_hard_reg_fill_datas(Hardware_I2C *i2c, uint8_t addr, const uint8_t byte, size_t size);
uint16_t i2c_hard_reg_receive_data(Hardware_I2C *i2c, uint8_t addr);
size_t i2c_hard_reg_receive_datas(Hardware_I2C *i2c, uint8_t addr, uint8_t *buf, size_t size);

///***************************软件I2C部分*****************************///
/*
 * @brief 软件I2C从设备结构体 \n
 * SDA:软件I2C_SDA引脚
 * SCL:软件I2C_SCL引脚
 * addr:软件I2C设备地址(字节左对齐)
 * delay_time:软件I2C的时钟延时(数值越小，速度越快)，单位：us
 */
typedef struct
{
    Pin_enum SDA;
    Pin_enum SCL;
    uint16_t addr;
    int delay_time;
} Software_I2C;

Software_I2C i2c_soft_init(Pin_enum SDA_Pin, Pin_enum SCL_Pin, int speed);
uint8_t i2c_soft_check(Software_I2C *i2c);
size_t i2c_soft_reg_write_data(Software_I2C *i2c, uint8_t addr, uint8_t byte);
size_t i2c_soft_reg_write_datas(Software_I2C *i2c, uint8_t addr, const uint8_t *buf, size_t size);
size_t i2c_soft_reg_fill_datas(Software_I2C *i2c, uint8_t addr, const uint8_t byte, size_t size);
uint16_t i2c_soft_reg_receive_data(Software_I2C *i2c, uint8_t addr);
size_t i2c_soft_reg_receive_datas(Software_I2C *i2c, uint8_t addr, uint8_t *buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif
