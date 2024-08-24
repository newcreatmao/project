/**************************************************************************
  * @brief       : STM32 USART
  * @author      : 龚为玮(1461041096)  
  * @copyright   : 版权信息
  * @version     : v1.0
  * @note        : 无
  * @history     : 2021年11月20日：创建文件
  *                2021年11月22日：完成串口初始化功能、串口基础write功能
  *                               并对UART1进行了输出测试，测试通过
  *                2021年11月22日：添加注释
  *                2021年11月23日：对UART2~UART5进行了输出测试，测试通过
  *                2021年12月 3日：完成了串口接收相关接口，对UART1进行了测试
  *                2021年12月13日：发现UART4和UART5无法接收，原因不明
  *                2021年12月14日：解决了13日发现的问题，目前所有串口经过测试输入输
  *                               出可用
  *                2022年10月23日：增加了UART1~4 DMA输出功能，UART5不支持DMA
***************************************************************************/

#ifndef __MY_USART_H
#define __MY_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_usart.h"
#include "my_afio.h"
#include "my_gpio.h"

/**
* @brief 串口枚举 \n
* UART_1 串口1，以此类推
*/
typedef enum
{
#ifdef HAVE_SERIAL1
  UART_1 = (uint32_t)USART1,
#endif
#ifdef HAVE_SERIAL2
  UART_2 = (uint32_t)USART2,
#endif
#ifdef HAVE_SERIAL3
  UART_3 = (uint32_t)USART3,
#endif
#ifdef HAVE_SERIAL4
  UART_4 = (uint32_t)UART4,
#endif
#ifdef HAVE_SERIAL5
  UART_5 = (uint32_t)UART5,
#endif
  UART_END//占位，没有用
} UART_enum;

#define DEFAULT_UART_WORDLENGTH     USART_WordLength_8b             //默认8位数据位
#define DEFAULT_UART_STOPBITS       USART_StopBits_1                //默认1位停止位
#define DEFAULT_UART_PARITY         USART_Parity_No                 //默认无校验位
#define DEFAULT_UART_FLOWCONTROL    USART_HardwareFlowControl_None  //默认无硬件流控

#ifdef HAVE_SERIAL1
extern __rec_buf UART1_recbuf;
#endif
#ifdef HAVE_SERIAL2
extern __rec_buf UART2_recbuf;
#endif
#ifdef HAVE_SERIAL3
extern __rec_buf UART3_recbuf;
#endif
#ifdef HAVE_SERIAL4
extern __rec_buf UART4_recbuf;
#endif
#ifdef HAVE_SERIAL5
extern __rec_buf UART5_recbuf;
#endif

void uart_init(UART_enum uart, uint32_t baudrate);
void uart_deinit(UART_enum uart);
void uart_write_byte(UART_enum uart, uint8_t data);
void uart_write_buffer(UART_enum uart, const uint8_t *buf, int len);
void uart_write_string(UART_enum uart, const char *str);

uint16_t uart_rec_size(UART_enum uart);
uint8_t uart_read_byte(UART_enum uart);

//********DMA********//
void uart_dma_init(UART_enum uart);
void uart_dma_write_buffer(UART_enum uart, const uint8_t *buf, int len);

#ifdef __cplusplus
 }
#endif

#endif
